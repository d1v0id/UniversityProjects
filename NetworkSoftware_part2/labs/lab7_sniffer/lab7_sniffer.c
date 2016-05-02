/*
 * lab7_sniffer.c
 *
 *      Author: dmitry
 */
#include <pcap.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SNAP_LEN 1518 // default snap length (maximum bytes per packet to capture)
#define SIZE_ETHERNET 14 // ethernet headers are always exactly 14 bytes
#define ETHER_ADDR_LEN 6 // ethernet addresses are 6 bytes

struct sniff_ethernet { // ethernet header
	u_char ether_dhost[ETHER_ADDR_LEN]; // destination host address
	u_char ether_shost[ETHER_ADDR_LEN]; // source host address
	u_short ether_type; // IP? ARP? RARP? etc
};

struct sniff_ip { // IP header
	u_char ip_vhl; // version << 4 | header length >> 2
	u_char ip_tos; // type of service
	u_short ip_len; // total length
	u_short ip_id; // identification
	u_short ip_off; // fragment offset field
	u_char ip_ttl; // time to live
	u_char ip_p; // protocol
	u_short ip_sum; // checksum
	struct in_addr ip_src; // source address
	struct in_addr ip_dst; // dest address
};

typedef u_int tcp_seq; // TCP header

struct sniff_tcp {
	u_short th_sport; // source port
	u_short th_dport; // destination port
	tcp_seq th_seq; // sequence number
	tcp_seq th_ack; // acknowledgement number
	u_char th_offx2; // data offset, rsvd
	u_char th_flags;
	u_short th_win; // window
	u_short th_sum; // checksum
	u_short th_urp; // urgent pointer
};

/* print data in rows of 16 bytes: offset   hex   ascii
 * 00000   47 45 54 20 2f 20 48 54  54 50 2f 31 2e 31 0d 0a   GET / HTTP/1.1.. */
void print_hex_ascii_line(const u_char *payload, int len, int offset)
{
	int i;
	int gap;
	const u_char *ch;

	printf("%05d   ", offset);

	ch = payload;
	for (i = 0; i < len; i++) { // hex
		printf("%02x ", *ch);
		ch++;
		if (i == 7) { // print extra space after 8th byte for visual aid
			printf(" ");
		}
	}

	if (len < 8) { // print space to handle line less than 8 bytes
		printf(" ");
	}

	if (len < 16) { // fill hex gap with spaces if not full line
		gap = 16 - len;
		for (i = 0; i < gap; i++) {
			printf("   ");
		}
	}

	printf("   ");
	ch = payload; // ascii (if printable)

	for (i = 0; i < len; i++) {
		if (isprint(*ch)) {
			printf("%c", *ch);
		}
		else {
			printf(".");
		}

		ch++;
	}

	printf("\n");
}

// print packet payload data (avoid printing binary data)
void print_payload(const u_char *payload, int len)
{
	int len_rem = len;
	int line_width = 16; // number of bytes per line
	int line_len;
	int offset = 0; // zero-based offset counter
	const u_char *ch = payload;

	if (len <= 0) {
		return;
	}

	if (len <= line_width) { // data fits on one line
		print_hex_ascii_line(ch, len, offset);
		return;
	}

	while (1) { // data spans multiple lines
		line_len = line_width % len_rem; // compute current line length
		print_hex_ascii_line(ch, line_len, offset); // print line
		len_rem = len_rem - line_len; // compute total remaining
		ch = ch + line_len; // shift pointer to remaining bytes to print
		offset = offset + line_width; // add offset
		if (len_rem <= line_width) { // check if we have line width chars or less
			print_hex_ascii_line(ch, len_rem, offset); // print last line and get out
			break;
		}
	}
}

// dissect/print packet
void got_packet(u_char *args, const struct pcap_pkthdr *header, const u_char *packet)
{
	static int count = 1; // packet counter

	const struct sniff_ip *ip; // The IP header
	const struct sniff_tcp *tcp; // The TCP header
	const char *payload; // Packet payload

	int size_ip;
	int size_tcp;
	int size_payload;

	printf("\nPacket number %d:\n", count);
	count++;

	ip = (struct sniff_ip *)(packet + SIZE_ETHERNET); // define/compute ip header offset
	size_ip = (((ip)->ip_vhl) & 0x0f) * 4;

	if (size_ip < 20) {
		printf("   * Invalid IP header length: %u bytes\n", size_ip);
		return;
	}

	// print source and destination IP addresses
	printf("       From: %s\n", inet_ntoa(ip->ip_src));
	printf("         To: %s\n", inet_ntoa(ip->ip_dst));

	// determine protocol
	switch(ip->ip_p) {
	case IPPROTO_TCP:
		printf("   Protocol: TCP\n");
		tcp = (struct sniff_tcp *)(packet + SIZE_ETHERNET + size_ip); // define/compute tcp header offset
		size_tcp = (((tcp)->th_offx2 & 0xf0) >> 4) * 4;
		if (size_tcp < 20) {
			printf("   * Invalid TCP header length: %u bytes\n", size_tcp);
			return;
		}

		printf("   Src port: %d\n", ntohs(tcp->th_sport));
		printf("   Dst port: %d\n", ntohs(tcp->th_dport));

		payload = (u_char *)(packet + SIZE_ETHERNET + size_ip + size_tcp); // define/compute tcp payload (segment) offset
		size_payload = ntohs(ip->ip_len) - (size_ip + size_tcp); // compute tcp payload (segment) size

		if (size_payload > 0) { // Print payload data; it might be binary, so don't just treat it as a string.
			printf("   Payload (%d bytes):\n", size_payload);
			print_payload(payload, size_payload);
		}
		break;

	case IPPROTO_UDP:
		printf("   Protocol: UDP\n");
		break;

	case IPPROTO_ICMP:
		printf("   Protocol: ICMP\n");
		break;

	case IPPROTO_IP:
		printf("   Protocol: IP\n");
		break;

	default:
		printf("   Protocol: unknown\n");
		break;
	}
}

int main(int argc, char *argv[])
{
	if ((argc < 2) || (argc > 3)) {
		printf("Usage: lab7_sniffer <FILTER_EXP> [interface]\n");
		return 1;
	}

	char *dev = NULL; // capture device name
	char errbuf[PCAP_ERRBUF_SIZE]; // error buffer
	pcap_t *handle; // packet capture handle

	//char filter_exp[] = "ip proto TCP and port 21"; // filter expression
	char *filter_exp = argv[1]; // filter expression
	struct bpf_program fp; // compiled filter program (expression)
	bpf_u_int32 mask; // subnet mask
	bpf_u_int32 net; // ip

	if (argc == 3) { // check for capture device name on command-line
		dev = argv[2];
	}
	else {
		dev = pcap_lookupdev(errbuf); // find a capture device if not specified on command-line
		if (dev == NULL) {
			printf("Couldn't find default device: %s\n", errbuf);
			return 1;
		}
	}

	if (pcap_lookupnet(dev, &net, &mask, errbuf) == -1) { // get network number and mask associated with capture device
		printf("Couldn't get netmask for device %s: %s\n", dev, errbuf);
		net = 0;
		mask = 0;
	}

	// print capture info
	printf("Device: %s\n", dev);
	printf("Filter expression: %s\n", filter_exp);

	handle = pcap_open_live(dev, SNAP_LEN, 1, 1000, errbuf); // open capture device
	if (handle == NULL) {
		printf("Couldn't open device %s: %s\n", dev, errbuf);
		return 1;
	}

	if (pcap_datalink(handle) != DLT_EN10MB) { // make sure we're capturing on an Ethernet device
		printf("%s is not an Ethernet\n", dev);
		return 1;
	}

	if (pcap_compile(handle, &fp, filter_exp, 0, net) == -1) { // compile the filter expression
		printf("Couldn't parse filter %s: %s\n", filter_exp, pcap_geterr(handle));
		return 1;
	}

	if (pcap_setfilter(handle, &fp) == -1) { // apply the compiled filter
		printf("Couldn't install filter %s: %s\n", filter_exp, pcap_geterr(handle));
		return 1;
	}

	pcap_loop(handle, 0, got_packet, NULL); // now we can set our callback function

	pcap_freecode(&fp);
	pcap_close(handle);
	printf("\nCapture complete.\n");

	return 0;
}

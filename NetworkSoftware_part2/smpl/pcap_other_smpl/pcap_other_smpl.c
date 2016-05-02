/*
 * pcap_other_smpl.c
 *
 *      Author: dmitry
 */

#include <stdio.h>
#include <pcap.h>

#define MAXLEN 1500
#define TIMEOUT 500
#define IP_H sizeof(struct ip)
#define ETH_H 14
#define TCP_H sizeof(struct tcphdr)

pcap_t *fd;

int main(int argc, char *argv[])
{
	struct bpf_program bpf_fil;
	char err[PCAP_ERRBUF_SIZE];
	char *device;
	bpf_u_int32 net;
	bpf_u_int32 mask;
	pcap_handler process;

	device = pcap_lookupdev(err);
	printf("Using device: %s\n", device);

	if ((fd = pcap_open_live(device, MAXLEN, 1, TIMEOUT, err)) == NULL) {
		printf("Can't open device %s\n", err);
		exit(0);
	}

	if ((pcap_lookupnet(device, &net, &mask, err)) < 0) {
		printf("pcap_lookupnet error: %s\n", err);
		pcap_close(fd);
		exit(0);
	}

	printf("Net number: %s\n", inet_ntoa(net));
	printf("Mask %s\n", inet_ntoa(mask));

	return 0;
}

/*
 * sctp_server_smpl.c
 *
 *      Author: dmitry
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/sctp.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#define RECVBUFSIZE 4096
#define PPID 1234

int main(int argc, char *argv[])
{
	int SctpScocket;
	int n;
	int flags;
	socklen_t from_len;

	struct sockaddr_in addr = { 0 };
	struct sctp_sndrcvinfo sinfo = { 0 };
	struct sctp_event_subscribe event = { 0 };
	char pRecvBuffer[RECVBUFSIZE + 1] = { 0 };

	char *szAddress;
	int iPort;
	char *szMsg;
	int iMsgSize;

	// get the arguments
	szAddress = "127.0.0.1";
	iPort = 5001;
	szMsg = "Hello Client";
	iMsgSize = strlen(szMsg);

	if (iMsgSize > 1024) {
		printf("Message is too big for this test\n");
		return 0;
	}

	// here we may fail if sctp is not supported
	SctpScocket = socket(AF_INET, SOCK_SEQPACKET, IPPROTO_SCTP);
	printf("socket created...\n");

	// make sure we receive MSG_NOTIFICATION
	setsockopt(SctpScocket, IPPROTO_SCTP, SCTP_EVENTS, &event, sizeof(struct sctp_event_subscribe));
	printf("setsockopt succeeded...\n");

	addr.sin_family = AF_INET;
	addr.sin_port = htons(iPort);
	addr.sin_addr.s_addr = inet_addr(szAddress);

	// bind to specific server address and port
	bind(SctpScocket, (struct sockaddr *) &addr, sizeof(struct sockaddr_in));
	printf("bind succeeded...\n");

	// wait for connections
	listen(SctpScocket, 1);
	printf("listen succeeded...\n");

	int count = 0;
	int i;
	char a[20][10];
	char d[20][10];
	char send_data[1024];

	strcpy(a[0],"Abraham");
	strcpy(a[1],"Buck");
	strcpy(a[2],"Casper");
	strcpy(a[3],"Dammy");

	strcpy(d[0],"1");
	strcpy(d[1],"2");
	strcpy(d[2],"3");
	strcpy(d[3],"4");

	while(1) {
		// each time erase the stuff
		flags = 0;
		memset((void *) &addr, 0, sizeof(struct sockaddr_in));
		from_len = (socklen_t) sizeof(struct sockaddr_in);
		memset((void *) &sinfo, 0, sizeof(struct sctp_sndrcvinfo));

		n = sctp_recvmsg(SctpScocket, (void*) pRecvBuffer, RECVBUFSIZE, (struct sockaddr *) &addr, &from_len, &sinfo, &flags);
		if (n == -1) {
			printf("Error with sctp_recvmsg: -1... waiting\n");
			printf("errno: %d\n", errno);
			perror("Description: ");
			sleep(1);
			continue;
		}

		if (flags & MSG_NOTIFICATION) {
			printf("Notification received!\n");
			printf("From %s:%u\n", inet_ntoa(addr.sin_addr), ntohs(addr.sin_port));
		}
		else {
			printf("Received from %s:%u on stream %d, PPID %d.: %s\n",
				inet_ntoa(addr.sin_addr),
				ntohs(addr.sin_port),
				sinfo.sinfo_stream,
				ntohl(sinfo.sinfo_ppid),
				pRecvBuffer
			);

			int p = 0;
			for (i = 0; i < 4; i++) {
				if (strcmp(pRecvBuffer, d[i]) == 0) {
					strcpy(send_data, a[i]);
					p = 1;
				}
			}

			if (p == 0) {
				strcpy(send_data, "No one on that role.");
			}
		}

		// send message to client
		printf("Sending to client: %s\n", send_data);
		sctp_sendmsg(SctpScocket, (const void *) send_data, strlen(send_data), (struct sockaddr *) &addr, from_len, htonl(PPID), 0, 0 /*stream 0*/, 0, 0);

		// close server when exit is received
		if (strcmp(pRecvBuffer, "exit") == 0) {
			break;
		}
	}

	printf("exiting...\n");
	close(SctpScocket);

	return 0;
}

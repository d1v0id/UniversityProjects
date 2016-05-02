/*
 * lab6_server.c
 *
 *      Author: dmitry
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/sctp.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#define BUFFER_SIZE 64
#define TEXT_MESSAGE_STREAM 0
#define IMAGE_STREAM 1

int main(int argc, char *argv[])
{
	int fd;
	int connSock;
	int n;
	int flags;
	struct sockaddr_in addr;
	socklen_t from_len;
	struct sctp_sndrcvinfo sinfo;
	char buffer[BUFFER_SIZE];
	struct sctp_event_subscribe event;
	FILE *f;

	if ((fd = socket(AF_INET, SOCK_STREAM, IPPROTO_SCTP)) < 0) {
		perror("socket");
	}

	memset((void *)&event, 1, sizeof(struct sctp_event_subscribe));

	if (setsockopt(fd, IPPROTO_SCTP, SCTP_EVENTS, &event, sizeof(struct sctp_event_subscribe)) < 0) {
		perror("setsockopt");
	}

	bzero((void *)&addr, sizeof(struct sockaddr_in));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = 0;

	if (bind(fd, (struct sockaddr *)&addr, sizeof(struct sockaddr_in)) < 0) {
		perror("bind");
	}

	socklen_t len = sizeof(addr);
	getsockname(fd, (struct sockaddr_in *) &addr, &len);
	printf("Listen on port: %d\n", ntohs(addr.sin_port));

	if (listen(fd, 5) < 0) {
		perror("listen");
	}

	while (1) {
		connSock = accept(fd, (struct sockaddr *)NULL, (int *)NULL);

		switch(fork()) {
		case -1:
			perror("fork");
			close(connSock);
			close(fd);
			exit(1);

		case 0:
			close(fd);
			char fileName[512];
			strcpy(fileName, "/tmp/lab6_server.XXXXXX");
			mkstemp(fileName);
			f = fopen(fileName, "wb");

			while (1) {
				flags = 0;
				bzero((void *)&addr, sizeof(struct sockaddr_in));
				from_len = (socklen_t)sizeof(struct sockaddr_in);
				bzero((void *)&sinfo, sizeof(struct sctp_sndrcvinfo));

				bzero((void *)&buffer, sizeof(buffer));
				n = sctp_recvmsg(connSock, (void*)buffer, BUFFER_SIZE, (struct sockaddr *)&addr, &from_len, &sinfo, &flags);

				if (!(flags & MSG_NOTIFICATION)) {
					if (sinfo.sinfo_stream == TEXT_MESSAGE_STREAM) {
						printf("%s\n", buffer);

						if (strcmp(buffer, "eof") == 0) {
							break;
						}
					}
					else if (sinfo.sinfo_stream == IMAGE_STREAM) {
						fwrite(buffer, n, 1, f);
					}
				}
			}

			fcloseall();
			close(connSock);
			exit(0);

		default:
			close(connSock);
			continue;
		}
	}

	if (close(fd) < 0) {
		perror("close");
	}

	return (0);
}

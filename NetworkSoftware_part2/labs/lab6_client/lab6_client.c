/*
 * lab6_client.c
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
#include <fcntl.h>
#include <netdb.h>

#define BUFFER_SIZE 64
#define PPID 1234
#define TEXT_MESSAGE_STREAM 0
#define IMAGE_STREAM 1

int main(int argc, char *argv[])
{
	if (argc != 4) {
		printf("Usage: lab6_client <ADDRESS> <PORT> <FILE NAME>");
		exit(1);
	}

	int fd;
	struct sockaddr_in addr;
	char buffer[BUFFER_SIZE];
	struct sctp_status status;
	struct sctp_initmsg init;
	socklen_t opt_len;
	struct hostent *hp;
	FILE *f;
	size_t size;

	if ((fd = socket(AF_INET, SOCK_STREAM, IPPROTO_SCTP)) < 0) {
		perror("socket");
	}

	bzero((void *)&init, sizeof(struct sctp_initmsg));
	init.sinit_num_ostreams = 5;
	init.sinit_max_instreams = 5;
	init.sinit_max_attempts = 4;
	if (setsockopt(fd, IPPROTO_SCTP, SCTP_INITMSG, &init, (socklen_t)sizeof(struct sctp_initmsg)) < 0) {
		perror("setsockopt");
	}

	bzero((void *)&addr, sizeof(struct sockaddr_in));
	if ((hp = gethostbyname(argv[1])) == 0) {
		perror("gethostbyname");
		exit(3);
	}

	bcopy(hp->h_addr, &addr.sin_addr, hp->h_length);
	addr.sin_family = hp->h_addrtype;
	int portNum = atoi(argv[2]);
	addr.sin_port = htons(portNum);

	if (connect(fd, (struct sockaddr *)&addr, sizeof(struct sockaddr_in)) < 0) {
		perror("connect");
	}

	bzero((void *)&status, sizeof(struct sctp_status));
	opt_len = (socklen_t)sizeof(struct sctp_status);
	if (getsockopt(fd, IPPROTO_SCTP, SCTP_STATUS, &status, &opt_len) < 0) {
		perror("getsockopt");
	}

	bzero((void *)&buffer, sizeof(buffer));
	snprintf(buffer, 13, "%s", "Hello World!");
	if (sctp_sendmsg(fd, (const void *)buffer, 13, NULL, 0, htonl(PPID), 0, TEXT_MESSAGE_STREAM, 0, 0) < 0) {
		perror("send");
	}

	f = fopen(argv[3], "rb");

	if (f != NULL) {
		while (size = fread(buffer, 1, sizeof(buffer), f)) {
			if (sctp_sendmsg(fd, (const void *)buffer, size, NULL, 0, htonl(PPID), 0, IMAGE_STREAM, 0, 0) < 0) {
				perror("send");
			}
			bzero((void *)&buffer, sizeof(buffer));
		}

		snprintf(buffer, 4, "%s", "eof");
		if (sctp_sendmsg(fd, (const void *)buffer, 4, NULL, 0, htonl(PPID), 0, TEXT_MESSAGE_STREAM, 0, 0) < 0) {
			perror("send");
		}

		fcloseall();
	}

	if (close(fd) < 0) {
		perror("close");
	}

	return(0);
}

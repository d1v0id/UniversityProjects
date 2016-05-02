/*
 * lab5_client_tcp.c
 *
 *      Author: dmitry
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <netdb.h>

int main(int argc, char *argv[])
{
	if (argc != 4) {
		printf("Usage: lab5_client_tcp <ADDRESS> <PORT> <FILE NAME>");
		exit(1);
	}

	int s;
	struct sockaddr_in serv_addr;
	struct hostent *hp;
	char buffer[64];
	FILE *f;
	size_t size;

	if ((hp = gethostbyname(argv[1])) == 0) {
		perror("gethostbyname() error");
		exit(3);
	}

	bzero(&serv_addr, sizeof(serv_addr));
	bcopy(hp->h_addr, &serv_addr.sin_addr, hp->h_length);
	serv_addr.sin_family = hp->h_addrtype;
	int portNum = atoi(argv[2]);
	serv_addr.sin_port = htons(portNum);

	if ((s = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("socket() error");
		exit(1);
	}

	fprintf(stderr, "Server address: %s\n", inet_ntoa(serv_addr.sin_addr));

	if (connect(s, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) == -1) {
		perror("connect() error");
		exit(1);
	}

	f = fopen(argv[3], "rb");

	if (f != NULL) {
		while (size = fread(buffer, sizeof(buffer), 1, f)) {
			send(s, buffer, sizeof(buffer), 0);
		}

		fcloseall();
	}

	close(s);

	return 0;
}

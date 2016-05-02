/*
 * lab4_server.c
 *
 *      Author: dmitry
 */

#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

int handler(int t)
{
	int rb = 0;
	char buf[2];
	rb = recv(t, buf, sizeof(buf), 0);

	if (rb == -1) {
		return 0;
	}

	if (rb > 0) {
		printf("%s\n", buf);
	}

	return rb;
}

int main(int argc, char *argv[])
{
	int msock; // ведущий сокет сервера
	fd_set rfds; // набор дескрипторов, готовых к чтению
	fd_set afds; // набор активных дескрипторов
	int fd;
	int nfds;
	int ssock;
	struct sockaddr_in fsin;

	bzero(&fsin, sizeof(struct sockaddr_in));
	fsin.sin_family = AF_INET;
	fsin.sin_addr.s_addr = INADDR_ANY;
	fsin.sin_port = 0;

	msock = socket(AF_INET, SOCK_STREAM, 0);
	bind(msock, (struct sockaddr *) &fsin, sizeof(struct sockaddr_in));
	printf("Ready to answer querys on %s\n", inet_ntoa(fsin.sin_addr));

	socklen_t len = sizeof(fsin);
	getsockname(msock, (struct sockaddr_in *) &fsin, &len);
	printf("Listen on port: %d\n", ntohs(fsin.sin_port));

	listen(msock, 3);

	// инициализация пассивного сокета msock
	nfds = getdtablesize();
	FD_ZERO(&afds);
	FD_SET(msock, &afds);

	while (1) {
		memcpy(&rfds, &afds, sizeof(rfds));

		if (select(nfds, &rfds, (fd_set *) 0, (fd_set *) 0, (struct timeval *) 0) < 0) {
			printf("select() error");
		}

		if (FD_ISSET(msock, &rfds)) {
			int alen = sizeof(fsin);
			ssock = accept(msock, (struct sockaddr *) &fsin, &alen);
			printf("Got connection from %s\n", inet_ntoa(fsin.sin_addr));

			if (ssock < 0) {
				printf("ssock < 0");
			}

			FD_SET(ssock, &afds);
		}

		for (fd = 0; fd < 10 /*nfds*/; fd++) { // ???
			if (fd != msock && FD_ISSET(fd, &rfds)) {
				if (handler(fd) == 0) { // число полученных байт
					close(fd);
				}
			}
		}

		FD_CLR(fd, &afds);
	}

	return 0;
}

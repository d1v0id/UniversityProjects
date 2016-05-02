/*
 * lab5_server.c
 *
 *      Author: dmitry
 */

#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/param.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/wait.h>

void handler(char *buf, int size, char *fileName)
{
	FILE *f;

	f = fopen(fileName, "a+b");
	fseek(f, 0, SEEK_END);
	fwrite(buf, size, 1, f);
	fclose(f);
}

int main(int argc, char *argv[])
{
	int tsock; // ведущий сокет TCP
	int usock; // сокет UDP
	int ssock; // ведомый сокет TCP
	fd_set rfds; // дескрипторы, готовые к чтению
	int len;
	int rb;
	struct sockaddr_in fsin;
	char buf[100];
	char *fileNameTcp = "/tmp/lab5_server_tcp.txt";
	char *fileNameUdp = "/tmp/lab5_server_udp.txt";

	bzero(&fsin, sizeof(struct sockaddr_in));
	fsin.sin_family = AF_INET;
	fsin.sin_addr.s_addr = INADDR_ANY;
	fsin.sin_port = 0;

	tsock = socket(AF_INET, SOCK_STREAM, 0);
	bind(tsock, (struct sockaddr *) &fsin, sizeof(struct sockaddr_in));
	socklen_t slen = sizeof(fsin);
	getsockname(tsock, (struct sockaddr_in *) &fsin, &slen);
	printf("Listen on port: %d\n", ntohs(fsin.sin_port));
	listen(tsock, 3);

	usock = socket(AF_INET, SOCK_DGRAM, 0);
	bind(usock, (struct sockaddr *) &fsin, sizeof(struct sockaddr_in));

	int nfds = MAX(tsock, usock) + 1; // длина битовой маски для набора дескрипторов
	FD_ZERO(&rfds);

	while (1) {
		FD_SET(tsock, &rfds);
		FD_SET(usock, &rfds);

		if (select(nfds, &rfds, (fd_set *) 0, (fd_set *) 0, (struct timeval *) 0) < 0) {
			printf("select() error");
		}

		if (FD_ISSET(tsock, &rfds)) {
			len = sizeof(fsin);
			ssock = accept(tsock, (struct sockaddr *) &fsin, &len);

			while ((rb = recv(ssock, buf, sizeof(buf), 0)) != 0) {
					handler(buf, rb, fileNameTcp);
			}

			close(ssock);
		}

		if (FD_ISSET(usock, &rfds)) {
			len = sizeof(fsin);

			if ((rb = recvfrom(usock, buf, sizeof(buf), 0, (struct sockaddr *) &fsin, &len)) < 0) {
				printf("rervfrom() error");
			}

			handler(buf, rb, fileNameUdp);
		}
	}

	return 0;
}

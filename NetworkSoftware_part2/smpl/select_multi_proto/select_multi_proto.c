/*
 * select_multi_proto.c
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

void handler(char *buf)
{
	printf("%s", buf);
}

int main(int argc, char *argv[])
{
	int tsock; // ведущий сокет TCP
	int usock; // сокет UDP
	int ssock; // ведомый сокет TCP
	fd_set rfds; // дескрипторы, готовые к чтению
	int len;
	struct sockaddr_in fsin;
	char buf[100];

	bzero(&fsin, sizeof(struct sockaddr_in));
	fsin.sin_family = AF_INET;
	fsin.sin_addr.s_addr = INADDR_ANY;
	fsin.sin_port = htons(1984);

	tsock = socket(AF_INET, SOCK_STREAM, 0);
	bind(tsock, (struct sockaddr *) &fsin, sizeof(struct sockaddr_in));
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
			printf("Got connection from %s\n", inet_ntoa(fsin.sin_addr));

			if (ssock < 0) {
				printf("ssock < 0");
			}

			handler(buf);

			if (send(ssock, buf, sizeof(buf), NULL) < 0) {
				printf("send() error");
			}

			close(ssock);
		}

		if (FD_ISSET(usock, &rfds)) {
			len = sizeof(fsin);

			if (recvfrom(usock, buf, sizeof(buf), 0, (struct sockaddr *) &fsin, &len) < 0) {
				printf("rervfrom() error");
			}

			handler(buf);

			if (sendto(usock, buf, strlen(buf), 0, (struct sockaddr *) &fsin, sizeof(fsin)) < 0) {
				printf("sendto() error");
			}
		}
	}

	return 0;
}

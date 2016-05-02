/*
 * select_multi_service.c
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

#define TCP_SERV 1
#define UDP_SERV 0
#define NOSOCK -1
#define QLEN 1024 // ?

struct service {
	char *sv_name;
	char sv_useTCP;
	int sv_sock;
	void (*sv_func) (int);
};

void TCPservice1(int param)
{
}

void TCPservice2(int param)
{
}

void TCPservice3(int param)
{
}

void TCPservice4(int param)
{
}

struct service svent[5] = {
		{ "srv1", TCP_SERV, NOSOCK, TCPservice1 },
		{ "srv2", TCP_SERV, NOSOCK, TCPservice2 },
		{ "srv3", TCP_SERV, NOSOCK, TCPservice3 },
		{ "srv4", TCP_SERV, NOSOCK, TCPservice4 },
		{ 0, 0, 0, 0 }
};

int passiveTCP(const char *service, int qlen)
{
	return 0;
}

int passiveUDP(const char *service)
{
	return 0;
}

void reaper(int sig)
{
}

void doTCP(struct service *psv)
{
	int ssock;
	int fd;
	struct sockaddr_in fsin;
	int alen = sizeof(fsin);

	ssock = accept(psv->sv_sock, (struct sockaddr *) &fsin, &alen);

	if (ssock < 0) {
		printf("error");
	}

	switch (fork()) {
	case 0:
		break;
	case -1:
		return;
	default:
		close(ssock);
		return;
	}

	for (fd = NOFILE; fd >= 0; --fd) {
		if (fd != ssock) {
			close(fd);
		}
	}

	psv->sv_func(ssock);
	exit(0);
}

int main(int argc, char *argv[])
{
	struct service *psv; // указатель таблицы service
	struct service *fd2sv[NOFILE]; // отображение дескриптора файла на указатель таблицы служб
	int fd;
	int nfds;
	fd_set afds; // дескрипторы, готовые к чтению
	fd_set rfds;

	nfds = 0;
	FD_ZERO(&afds);

	for (psv = &svent[0]; psv->sv_name; ++psv) {
		if (psv->sv_useTCP) {
			psv->sv_sock = passiveTCP(psv->sv_name, QLEN);
		}
		else {
			psv->sv_sock = passiveUDP(psv->sv_name);
		}

		fd2sv[psv->sv_sock] = psv;
		nfds = MAX(psv->sv_sock + 1, nfds);
		FD_SET(psv->sv_sock, &afds);
	}

	signal(SIGCHLD, reaper);

	while (1) {
		memcpy(&rfds, &afds, sizeof(rfds));

		if (select(nfds, &rfds, (fd_set *) 0, (fd_set *) 0, (struct timeval *) 0) < 0) {
			/*if (errno == EINTR) {
				printf("error");
				continue;
			}*/

			for (fd = 0; fd < nfds; ++fd) {
				if (FD_ISSET(fd, &rfds)) {
					psv = fd2sv[fd];

					if (psv->sv_useTCP) {
						doTCP(psv);
					}
					else {
						psv->sv_func(psv->sv_sock);
					}
				}
			}
		}
	}

	return 0;
}

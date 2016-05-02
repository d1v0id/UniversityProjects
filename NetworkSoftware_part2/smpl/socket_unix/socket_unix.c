/*
 * socket_unix.c
 *
 *      Author: dmitry
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <signal.h>

char buffer[256];
struct sockaddr_un sa; // адрес серверного сокета
int ssock; // дескриптор серверного сокета

/* этот обработчик закрывает, а потом уничтожает
 * серверный сокет, когда серверный процесс прерывается
 * по комбинации Ctrl+C (сигнал SIGINT) */
void siginth(int sig)
{
	close(ssock);
	unlink(sa.sun_path);
	exit(0);
}

int main(int argc, char *argv[])
{
	struct sockaddr_un ca; // адрес клиента
	int csock; // сокет-клиент
	int salen, calen; // размеры адресов

	// создаем серверный сокет
	if ((ssock = socket(AF_UNIX, SOCK_DGRAM, 0)) < 0) {
		perror("socket");
		exit(1);
	}

	// определяем его адрес
	bzero(&sa, sizeof(sa));
	sa.sun_family = AF_UNIX;
	strcpy(sa.sun_path, "/tmp/my_srvsocket");
	salen = sizeof(sa.sun_family) + sizeof(sa.sun_path);

	/* пробуем привязать, если вышло, то сервер еще не был
	 * создан, а значит мы становимся серверным процессом */
	if (bind(ssock, (struct sockaddr *) &sa, salen) >= 0) {
		printf("Starting server...\nIncoming messages:\n");
		signal(SIGINT, siginth);

		for (;;) {
			recvfrom(ssock, buffer, 256, 0, (struct sockaddr *) &ca, &calen);
			printf("%s\n", buffer);
		}
	}
	else { // если не вышло, то сервер уже есть, отправляем ему сообщение
		/* убьем дескриптор сервеного сокета в клиенте,
		 * т.к. он здесь не используется */
		close(ssock);
		bzero(&ca, sizeof(sa)); // сформируем адрес клиентского сокета
		ca.sun_family = AF_UNIX;
		strcpy(ca.sun_path, "/tmp/my_clnt.XXXXXX");
		mkstemp(ca.sun_path);
		calen = sizeof(ca.sun_family) + sizeof(ca.sun_path);

		// создадим клиентский сокет и свяжем его с адресом
		csock = socket(AF_UNIX, SOCK_DGRAM, 0);
		bind(csock, (struct sockaddr *) &ca, calen);

		// отправим через него данные серверному
		sendto(csock, argv[1], strlen(argv[1]), 0, (struct sockaddr *) &sa, salen);

		close(csock);
		unlink(ca.sun_path);
	}

	return 0;
}

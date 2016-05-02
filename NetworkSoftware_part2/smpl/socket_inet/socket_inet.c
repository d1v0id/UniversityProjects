/*
 * socket_inet.c
 *
 *      Author: dmitry
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>

#define NPORT 1984

/* ф-ция отлова зомби */
void zombiehunter(int sig)
{
	while (waitpid(-1, NULL, WNOHANG) > 0);
}

int main(int argc, char *argv[])
{
	int s, t, addrl;
	struct sockaddr_in sa, ca;

	// готовим сервер
	// заполняем поля локального адреса
	bzero(&sa, sizeof(struct sockaddr_in));
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = INADDR_ANY;

	// перед присвоением номера порта его необходимо
	// перевести в сетевой порядок байт
	sa.sin_port = NPORT;
	sa.sin_port = htons(sa.sin_port);

	// процедура создания и связывания
	s = socket(AF_INET, SOCK_STREAM, 0);
	//s = socket(AF_INET, SOCK_DGRAM, 0);
	bind(s, (struct sockaddr *) &sa, sizeof(struct sockaddr_in));
	printf("Ready to answer querys on %s\n", inet_ntoa(sa.sin_addr));

	// устанавливаем очередь размером 3 запроса
	listen(s, 3);

	// обработка сигнала SIGCHLD
	signal(SIGCHLD, zombiehunter);

	for (;;) {
		// ждем клиентские запросы
		bzero(&ca, sizeof(ca));
		addrl = sizeof(ca);

		// принимаем запрос и дублируем сокет s в t для
		// дальнейшей обработки
		t = accept(s, (struct sockaddr *) &ca, &addrl);
		printf("Got connection from %s\n", inet_ntoa(ca.sin_addr));

		switch(fork()) {
		case -1:
			perror("fork");
			close(s);
			close(t);
			exit(1);

		case 0:
			// внутри процесса-обработчика
			// в клиенте не нужен основной сокет
			close(s);
			int rb;
			char buf[100];

			while ((rb = recv(t, buf, sizeof(buf), 0)) != 0) {
				send(t, buf, rb, 0);
			}

			exit(0);

		default:
			// в родителе не нужнен сокет-бубликат
			close(t);
			continue;
		}
	}

	close(s);
	return 0;
}

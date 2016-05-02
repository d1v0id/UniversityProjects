/*
 * server.c
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

/* ф-ция отлова зомби */
void zombiehunter(int sig)
{
	while (waitpid(-1, NULL, WNOHANG) > 0);
}

int main(int argc, char *argv[])
{
	int s;
	int t;
	int addrl;
	struct sockaddr_in sa;
	struct sockaddr_in ca;
	FILE *f;

	// готовим сервер
	// заполняем поля локального адреса
	bzero(&sa, sizeof(struct sockaddr_in));
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = INADDR_ANY;
	sa.sin_port = 0;

	// процедура создания и связывания
	s = socket(AF_INET, SOCK_STREAM, 0);
	bind(s, (struct sockaddr *) &sa, sizeof(struct sockaddr_in));
	printf("Ready to answer querys on %s\n", inet_ntoa(sa.sin_addr));

	socklen_t len = sizeof(sa);
	getsockname(s, (struct sockaddr_in *) &sa, &len);
	printf("Listen on port: %d\n", ntohs(sa.sin_port));

	// устанавливаем очередь размером 35767 запросов
	listen(s, 35767);

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
			char buffer[64];
			char fileName[512];
			strcpy(fileName, "/tmp/lab2_server.XXXXXX");
			mkstemp(fileName);

			f = fopen(fileName, "wb");

			while ((rb = recv(t, buffer, sizeof(buffer), 0)) != 0) {
				fwrite(buffer, rb, 1, f);
			}

			fcloseall();
			exit(0);

		default:
			// в родителе не нужнен сокет-дубликат
			close(t);
			continue;
		}
	}

	close(s);
	return 0;
}

/*
 * socket_inet_client.c
 *
 *      Author: dmitry
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <fcntl.h>
#include <netdb.h>

#define PORTNUM 1984

int main(int arc, char *argv[])
{
	int s;
	int pid;
	int i, j;
	struct sockaddr_in serv_addr;
	struct hostent *hp;
	char buf[80] = "Hello AF_INET";

	// в качестве аргумента клиенту передается доменное
	// имя хоста, на котором запущен сервер
	if ((hp = gethostbyname(argv[1])) == 0) {
		perror("Ошибка вызова gethostbyname()");
		exit(3);
	}

	bzero(&serv_addr, sizeof(serv_addr));
	bcopy(hp->h_addr, &serv_addr.sin_addr, hp->h_length);
	serv_addr.sin_family = hp->h_addrtype;
	serv_addr.sin_port = htons(PORTNUM);

	//if ((s = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
	if ((s = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
		perror("Ошибка вызова socket()");
		exit(1);
	}

	fprintf(stderr, "Адрес сервера: %s\n", inet_ntoa(serv_addr.sin_addr));

	if (connect(s, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) == -1) {
		perror("Ошибка вызова connect()");
		exit(1);
	}

	send(s, buf, sizeof(buf), 0);

	if (recv(s, buf, sizeof(buf), 0) < 0) {
		perror("Ошибка вызова recv()");
		exit(1);
	}

	printf("Получено от сервера: %s\n", buf);
	close(s);

	return 0;
}

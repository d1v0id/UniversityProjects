/*
 * lab4_client.c
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
#include <stdlib.h>

int main(int argc, char *argv[])
{
	if (argc != 4) {
		printf("Usage: client <ADDRESS> <PORT> <TIMEOUT>");
		exit(1);
	}

	int s;
	struct sockaddr_in serv_addr;
	struct hostent *hp;
	char buffer[2];
	int seconds = atoi(argv[3]);

	if ((seconds < 1) || (seconds > 10)) {
		printf("Invalid timeout! (1 - 10)");
		exit(1);
	}

	// в качестве аргумента клиенту передается доменное
	// имя хоста, на котором запущен сервер
	if ((hp = gethostbyname(argv[1])) == 0) {
		perror("gethostbyname() error!");
		exit(3);
	}

	bzero(&serv_addr, sizeof(serv_addr));
	bcopy(hp->h_addr, &serv_addr.sin_addr, hp->h_length);
	serv_addr.sin_family = hp->h_addrtype;
	int portNum = atoi(argv[2]);
	serv_addr.sin_port = htons(portNum);

	if ((s = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("socket() error!");
		exit(1);
	}

	fprintf(stderr, "Server address: %s\n", inet_ntoa(serv_addr.sin_addr));

	if (connect(s, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) == -1) {
		perror("connect() error!");
		exit(1);
	}


	while (1) {
		sleep(seconds);
		sprintf(buffer, "%d", seconds);
		send(s, buffer, sizeof(buffer), 0);
	}

	close(s);
	return 0;
}

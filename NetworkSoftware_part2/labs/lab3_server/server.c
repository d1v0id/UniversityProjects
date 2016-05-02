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
#include <pthread.h>

int s;
char fileName[512];
FILE *f;
pthread_mutex_t mutexfile;

void *WriteToFile(void *t)
{
	int rb;
	char buffer[64];
	int localT = (int) t;
	pthread_mutex_lock(&mutexfile);

	f = fopen(fileName, "a+b");
	fseek(f, 0, SEEK_END);

	while ((rb = recv(localT, buffer, sizeof(buffer), 0)) != 0) {
		fwrite(buffer, rb, 1, f);
	}

	fclose(f);

	pthread_mutex_unlock(&mutexfile);
	close(localT);
}

void siginth(int sig)
{
	close(s);
	pthread_mutex_destroy(&mutexfile);
	exit(0);
}

int main(int argc, char *argv[])
{
	int t;
	int addrl;
	struct sockaddr_in sa;
	struct sockaddr_in ca;

	bzero(&sa, sizeof(struct sockaddr_in));
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = INADDR_ANY;
	sa.sin_port = 0;

	s = socket(AF_INET, SOCK_STREAM, 0);
	bind(s, (struct sockaddr *) &sa, sizeof(struct sockaddr_in));
	printf("Ready to answer querys on %s\n", inet_ntoa(sa.sin_addr));

	socklen_t len = sizeof(sa);
	getsockname(s, (struct sockaddr_in *) &sa, &len);
	printf("Listen on port: %d\n", ntohs(sa.sin_port));

	listen(s, 3);
	pthread_t thrds[3];
	int thrdNum = 0;

	strcpy(fileName, "/tmp/lab3_server.XXXXXX");
	mkstemp(fileName);

	signal(SIGINT, siginth);
	pthread_mutex_init(&mutexfile, NULL);

	for (;;) {
		bzero(&ca, sizeof(ca));
		addrl = sizeof(ca);
		t = accept(s, (struct sockaddr *) &ca, &addrl);
		printf("Got connection from %s\n", inet_ntoa(ca.sin_addr));

		pthread_create(&thrds[thrdNum], NULL, WriteToFile, (void *) t);
		pthread_join(thrds[thrdNum], NULL);

		close(t);
		thrdNum++;

		if (thrdNum > 2) {
			break;
		}
	}

	close(s);
	pthread_mutex_destroy(&mutexfile);

	return 0;
}

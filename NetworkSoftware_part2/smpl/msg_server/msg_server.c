/*
 * msg_server.c
 *
 *      Author: dmitry
 */

#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>

// структура-буфер сообщения
typedef struct messg {
	long messg_type;
	char messg_str[100];
} Messageq;

int msg_id; // дескриптор очереди сообщений

void hndl_term(int signo)
{
	printf("Exiting...\n");
	msgctl(msg_id, IPC_RMID, 0);
	exit(0);
}

int main(int argc, char *argv[])
{
	key_t key;
	Messageq messageq;
	int msgLen;

	key = ftok("./msg_server", 'a');
	msg_id = msgget(key, IPC_CREAT | 0666);

	if (msg_id < 0) {
		perror("msgget");
		exit(1);
	}

	signal(SIGTERM, hndl_term);
	signal(SIGINT, hndl_term);

	while (1) {
		// читаем сообщение в буфер из группы 1
		msgLen = msgrcv(msg_id, &messageq, sizeof(messageq), 1L, 0);

		if (msgLen > 0) {
			write(1, messageq.messg_str, msgLen);
		}
	}

	return 0;
}

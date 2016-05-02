/*
 * msg_client.c
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

	msgLen = sprintf(messageq.messg_str, "Very useful info :)\n");
	messageq.messg_type = 1L;
	msgsnd(msg_id, (void *) &messageq, msgLen, 0);

	return 0;
}

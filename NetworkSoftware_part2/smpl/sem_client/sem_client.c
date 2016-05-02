/*
 * sem_client.c
 *
 *      Author: dmitry
 */

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include "lib/semshmex.h"

int main(int argc, char *argv[])
{
	Messg *msgptr;
	key_t key;
	int shmId, semId;

	// получим ключ
	key = ftok("sem_server", 'A');

	if (key < 0) {
		printf("get key error");
		exit(1);
	}

	// получим доступ к разделяемой памяти
	shmId = shmget(key, sizeof(Messg), 0);

	if (shmId < 0) {
		printf("access error");
		exit(1);
	}

	// присоединим разделяемую память
	msgptr = (Messg *) shmat(shmId, 0, 0);

	if (msgptr < 0) {
		printf("attach error");
		exit(1);
	}

	// получим доступ к семафору
	semId = semget(key, 2, 0666);

	if (semId < 0) {
		printf("get error");
		exit(1);
	}

	// заблокируем разделяемую память
	if (semop(semId, &sem_wait_lock[0], 2) < 0) {
		printf("execute operation error");
		exit(1);
	}

	// уведомим сервер о начале работы
	if (semop(semId, &proc_run[0], 1) < 0) {
		printf("execute operation error");
		exit(1);
	}

	// запишем в разделяемую память сообщение
	sprintf(msgptr->data1, "123");

	// освободим разделяемую память
	if (semop(semId, &sem_unlock[0], 1) < 0) {
		printf("execute operation error");
		exit(1);
	}

	// ждем пока сервер не освободит разделяемую память
	if (semop(semId, &sem_wait_lock[0], 2) < 0) {
		printf("execute operation error");
		exit(1);
	}

	// отключимся от области
	if (shmdt(msgptr) < 0) {
		printf("detach error");
		exit(1);
	}

	// удалим созданные объекты IPC
	if (shmctl(shmId, IPC_RMID, 0) < 0) {
		printf("delete area error");
		exit(1);
	}

	if (semctl(semId, 0, IPC_RMID) < 0) {
		printf("delete semaphore error");
		exit(1);
	}

	return 0;
}

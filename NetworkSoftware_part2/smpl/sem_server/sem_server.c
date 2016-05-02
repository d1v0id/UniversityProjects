/*
 * sem_server.c
 *
 *      Author: dmitry
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include "lib/semshmex.h"

int main(int argc, char *argv[])
{
	key_t key = ftok("sem_server", 'A');

	// выделяем разделяемую память
	int shmId = shmget(key, sizeof(Messg), IPC_CREAT | 0666);

	// присоединяем разделяемую память
	Messg *mymsg = (Messg *) shmat(shmId, 0, 0);

	/* создаем группу для двух семафоров:
	 * одну - для синхронизации выполнения программ,
	 * другую - для синхронизации доступа к разделяемой памяти */
	int semId = semget(key, 2, IPC_CREAT | 0666);

	// ждем начала работы клиента
	semop(semId, &proc_wait[0], 1);

	/* ждем пока клиент запишет данные в разделяемую
	 * область памяти и потом заблокируем ее */
	semop(semId, &sem_wait_lock[0], 2);

	/* теперь через mymsg можно получить
	 * доступ к этой памяти */
	printf("Got data: %s\n", mymsg->data1);

	// разблокируем разделяемую память
	semop(semId, &sem_unlock[0], 1);

	// отсоединим разделяемую память
	shmdt(mymsg);

	// освобождаем разделяемую память
	/*shmctl(shmId, IPC_RMID, 0);

	// освобождаем группу семафоров
	semctl(semId, IPC_RMID, 0);*/

	return 0;
}

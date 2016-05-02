/*
 * pthreads.c
 *
 *      Author: dmitry
 */
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <crypt.h>

#define NTHRDS 4

// к этим ресурсам можно получить доступ из потока
char words[8000][20]; // словарь
int current, maxw;
char foundpass; // флажок ?

// блокировки
pthread_mutex_t mutexpass, mutexfound;

void *passhack(void *hash)
{
	char salt[13], s[20];
	char *enc;
	strncpy(salt, (char *) hash, 12);
	salt[12] = 0;

	while (foundpass != 1) {
		pthread_mutex_lock(&mutexpass);

		if (current >= maxw) {
			pthread_mutex_unlock(&mutexpass);
			pthread_exit((void *) 0);
		}

		strcpy(s, words[current++]);
		pthread_mutex_unlock(&mutexpass);
		s[strlen(s) - 1] = 0;
		enc = (char *) crypt(s, salt);

		if (!strcmp(enc, (char *) hash)) {
			printf("Thread %d found password: %s\n", getpid(), s);
			pthread_mutex_lock(&mutexfound);
			foundpass = 1;
			pthread_mutex_unlock(&mutexfound);
			pthread_exit((void *) 0);
		}
	}

	pthread_exit((void *) 0);
}

int main(int argc, char *argv[])
{
	char i, *pass;
	FILE *passfile;
	pthread_t thrds[NTHRDS];
	pass = (char *) malloc(35);
	pthread_mutex_init(&mutexpass, NULL);
	pthread_mutex_init(&mutexfound, NULL);
	strcpy(pass, argv[1]);

	// чтение словаря в память
	passfile = fopen(argv[2], "r");
	maxw = 0;

	while (!feof(passfile)) {
		fgets(words[maxw++], 20, passfile);
	}

	fclose(passfile);

	foundpass = 0;

	for (i = 0; i < NTHRDS; i++) {
		pthread_create(&thrds[i], NULL, passhack, (void *) pass);
	}

	for (i = 0; i < NTHRDS; i++) {
		pthread_join(thrds[i], NULL);
	}

	pthread_mutex_destroy(&mutexpass);
	pthread_mutex_destroy(&mutexfound);

	return 0;
}

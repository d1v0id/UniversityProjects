/*
 * semshmex.h
 *
 *      Author: dmitry
 */

#ifndef SEMSHMEX_H_
#define SEMSHMEX_H_

typedef struct Msg_buf {
	int seg;
	char data1[80];
} Messg;

// ждем когда значение семафора №1 станет 1 и обнулим его
static struct sembuf proc_wait[1] = { 1, -1, 0 };

// установим значение семафора №1 в 1
static struct sembuf proc_run[1] = { 1, 1, 0 };

static struct sembuf sem_wait_lock[2] = {
		{ 0, 0, 0 }, // ждем, когда семафор №0 обнулится
		{ 0, 1, 0 }  // установим его значение в 1
};

// обнулим семафор
static struct sembuf sem_unlock[1] = { 0, -1, 0 };

#endif /* SEMSHMEX_H_ */

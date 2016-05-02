/*
 * select.c
 *
 *      Author: dmitry
 */

#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	fd_set rfds;
	struct timeval tv;
	int retval;
	// ждем, пока на стандартном вводе (fd0) что-нибудь появится
	FD_ZERO(&rfds);
	FD_SET(0, &rfds);

	// ждем не больше пяти секунд
	tv.tv_sec = 5;
	tv.tv_usec = 0;

	retval = select(1, &rfds, NULL, NULL, &tv); // не полагаемся на значение tv!

	if (retval) { // теперь FS_ISSET(0, &rfds) вернет значение истина
		printf("Данные доступны.\n");
	}
	else {
		printf("Данные не появились в течение пяти секунд.\n");
	}

	return 0;
}

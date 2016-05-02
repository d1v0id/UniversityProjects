/*
 * sigusr.c
 *
 *      Author: dmitry
 */

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

int a;

static void handle_usr1(int signo)
{
	FILE *f;
	f = fopen("/tmp/sigex.out", "w");
	fprintf(f, "Signal SIGUSR1 caught!\n");
	fprintf(f, "Variable a = %d\n", a);
	fclose(f);
}

int main(int argc, char *argv[])
{
	a = 1;
	signal(SIGUSR1, handle_usr1);
	signal(SIGUSR2, SIG_IGN);

	while (1) {
		sleep(10);
		a++;
	}

	return 0;
}

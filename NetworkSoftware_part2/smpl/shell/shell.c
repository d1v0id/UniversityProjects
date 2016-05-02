/*
 * shell.c
 *
 *      Author: dmitry
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

int main(int argc, char *argv[])
{
	char cmd[80];
	pid_t pid;
	int stat_lock;

	while (1) {
		printf("shell # ");
		gets(cmd);

		if (strcmp("exit", cmd) == 0) {
			fprintf(stdout, "exiting...\n");
			break;
		}
		else {
			pid = fork();
			if (pid < 0) {
				fprintf(stderr, "fork() failed\n");
			}
			else if (pid == 0) {
				execlp(cmd, cmd, NULL);

				fprintf(stderr, "exec() failed\n");
				break;
			}
			else {
				wait(&stat_lock);
			}
		}
	}

	return 0;
}

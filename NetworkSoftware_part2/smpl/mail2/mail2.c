/*
 * mail2.c
 *
 *      Author: dmitry
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int fd[2], rSize;
	pid_t childPid;
	char buffer[80];

	pipe(fd);
	childPid = fork();

	if (childPid == -1) {
		perror("fork");
		exit(1);
	}

	if (childPid == 0) {
		close(fd[1]);
		close(0);
		dup(fd[0]);
		//dup2(fd[0], 0); // Linux Programmers Guide
		execlp("mail", "mail", "dmitry", "-s\"Hi to myself.\"", NULL);
		exit(0);
	}
	else {
		close(fd[0]);
		rSize = read(0, buffer, 80);

		while (rSize > 0) {
			write(fd[1], buffer, rSize);
		}
	}

	return 0;
}

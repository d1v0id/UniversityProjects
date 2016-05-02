/*
 * fifo.c
 *
 *      Author: dmitry
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define FIFO_FILE "MYFIFO"

int main(int argc, char *argv[])
{
	FILE *fp_s, *fp_c;
	char readBuf[80];
	pid_t pid;

	umask(0);
	mknod(FIFO_FILE, S_IFIFO | 0666, 0);

	switch (fork()) {
	case -1:
		perror("fork");
		break;

	case 0:
		fp_c = fopen(FIFO_FILE, "w");
		fputs("Hello parent!", fp_c);
		fclose(fp_c);
		exit(0);

	default:
		fp_s = fopen(FIFO_FILE, "r");
		fgets(readBuf, 80, fp_s);
		printf("Received string: %s\n", readBuf);
		fclose(fp_s);
	}

	unlink(FIFO_FILE);

	return 0;
}

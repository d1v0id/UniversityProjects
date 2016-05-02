/*
 * mail.c
 *
 *      Author: dmitry
 */

#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int rSize;
	char to[10];
	char subj[100];
	char buffer[80];
	char cmdLine[100];

	printf("    To: ");
	scanf("%s", to);

	write(1, "Subject: ", sizeof("Subject: "));
	subj[read(0, subj, 100) - 1] = '\0';

	sprintf(cmdLine, "mail %s -s\"%s\"", to, subj);

	FILE *file = popen(cmdLine, "w");

	while ((rSize = read(0, buffer, 80)) > 0) {
		buffer[rSize] = '\0';
		fputs(buffer, file);
	}

	pclose(file);
	printf("Mail to %s send.\n", to);

	return 0;
}

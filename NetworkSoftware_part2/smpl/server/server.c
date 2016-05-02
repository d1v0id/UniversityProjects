/*
 * server.c
 *
 *      Author: dmitry
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include "lib/client_server.h"
#include <sys/socket.h>
#include <netdb.h>

int split_to_array(char *string, char *delim, char **array)
{
    int arrayLen = 0;
    array[arrayLen] = strtok(strdup(string), delim);
    while(array[arrayLen] != NULL) {
        array[++arrayLen] = strtok(NULL, delim);
    }

    return arrayLen;
}

int reverse_string(char *str)
{
    int i;
    int strLen = strlen(str);
    char tmp[BUFFER_SIZE];
    bzero(tmp, BUFFER_SIZE);

    for (i = 0; i < strLen; i++) {
        tmp[i] = str[strLen - i - 1];
    }
    strcpy(str, tmp);

    return strLen;
}

int main(int argc, char *argv[])
{
    int i;
    int socketFd;
    int newSocketFd;
    int result;
    int arrayLen;
    char buffer[BUFFER_SIZE];
    char tmp[BUFFER_SIZE];
    char *array[BUFFER_SIZE];
    struct sockaddr_in serverAddr;
    struct sockaddr_in clientAddr;
    socklen_t clientLength;

    if ((socketFd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        exit_with_msg(1, SOCKET_OPEN_ERR_MSG);
    }

    bzero((char *)&serverAddr, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = 0;

    if (bind(socketFd, (struct sockaddr_in *) &serverAddr, sizeof(serverAddr)) < 0) {
        exit_with_msg(1, BIND_ERR_MSG);
    }

    listen(socketFd, 5);
    clientLength = sizeof(clientAddr);

    printf("Server application.\n");

    socklen_t len = sizeof(serverAddr);
    if (getsockname(socketFd, (struct sockaddr_in *)&serverAddr, &len) < 0) {
        exit_with_msg(1, BIND_ERR_MSG);
    }

    printf("Listen on port: %d\n", ntohs(serverAddr.sin_port));

    if ((newSocketFd = accept(socketFd, (struct sockaddr *)&clientAddr, &clientLength)) < 0) {
        exit_with_msg(1, ACCEPT_ERR_MSG);
    }

    while (1) {
        bzero(buffer, BUFFER_SIZE);
        result = read(newSocketFd, buffer, BUFFER_SIZE - 1);

        if (result < 0) {
            exit_with_msg(1, SOCKET_READ_ERR_MSG);
        }
        else if (result == 0) {
            close(newSocketFd);

            if ((newSocketFd = accept(socketFd, (struct sockaddr *)&clientAddr, &clientLength)) < 0) {
                exit_with_msg(1, ACCEPT_ERR_MSG);
            }
        }
        else {
            if (strcmp(buffer, "") != 0) {
                printf("> %s\n", buffer);
            }

            arrayLen = split_to_array(buffer, " ", array);

            bzero(tmp, BUFFER_SIZE);
            for (i = 0; i < arrayLen; i++) {
                reverse_string(array[i]);
                strcat(tmp, array[i]);
                if (i != arrayLen - 1) {
                    strcat(tmp, " ");
                }
            }

            if (write(newSocketFd, tmp, strlen(tmp)) < 0) {
                exit_with_msg(1, SOCKET_WRITE_ERR_MSG);
            }
        }
    }

    close(newSocketFd);
    close(socketFd);

    return 0;
}

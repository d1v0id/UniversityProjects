/*
 * client.c
 *
 *      Author: dmitry
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include "lib/client_server.h"

const char* USAGE_MSG = "Usage: client ADDRESS PORT";

int main(int argc, char *argv[])
{
    int socketFd;
    int portNum;
    char buffer[BUFFER_SIZE];
    struct sockaddr_in serverAddr;
    struct hostent *server;

    if (argc < 3) {
       exit_with_msg(0, USAGE_MSG);
    }

    portNum = atoi(argv[2]);
    if ((socketFd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        exit_with_msg(1, SOCKET_OPEN_ERR_MSG);
    }

    if ((server = gethostbyname(argv[1])) == NULL) {
        exit_with_msg(1, NO_HOST_MSG);
    }

    bzero((char *)&serverAddr, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serverAddr.sin_addr.s_addr, server->h_length);
    serverAddr.sin_port = htons(portNum);

    if (connect(socketFd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        exit_with_msg(1, CONN_ERR_MSG);
    }

    printf("Client application.\n");
    printf("Please enter your message. Enter %s for quit.\n", EXIT_CMD);

    while (1) {
        printf("> ");
        bzero(buffer, BUFFER_SIZE);
        fgets(buffer, BUFFER_SIZE - 1, stdin);
        buffer[strlen(buffer) - 1] = 0;

        if (strcmp(buffer, EXIT_CMD) == 0) {
            close(socketFd);
            exit_with_msg(0, "Bye.");
        }

        if (strcmp(buffer, "") != 0) {
            if (write(socketFd, buffer, strlen(buffer)) < 0) {
                exit_with_msg(1, SOCKET_WRITE_ERR_MSG);
            }

            bzero(buffer, BUFFER_SIZE);
            if (read(socketFd, buffer, BUFFER_SIZE - 1) < 0) {
                exit_with_msg(1, SOCKET_READ_ERR_MSG);
            }

            printf("< %s\n\n", buffer);
        }
    }

    return 0;
}

/*
 * web_server.c
 *      Author: Dmitry Konnov
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <signal.h>
#include <fcntl.h>
#include <linux/limits.h>

#define CONNECTIONS_MAX 1000000
#define QUEUED_REQUESTS_MAX 1000000
#define DATA_MAX 1024
#define MSG_MAX 99999
#define HTTP_VER_LEN 8

const char* GET_REQ = "GET\0";
const char* HTTP_1_0 = "HTTP/1.0";
const char* HTTP_1_1 = "HTTP/1.1";
const char* BAD_REQ_MSG = "400 Bad Request\n\n";
const char* OK_MSG = "200 OK\n\n";
const char* NOT_FOUND_MSG = "404 Not Found\n\n";
const char* NOT_FOUND_BODY = "<!DOCTYPE html><html><head><title>404 Not Found</title></head><body><h3>404 Not Found</h3></body></html>\n";
const char* INDEX_FILE_NAME = "/index.html";

char *documentRoot;
int listenFd;
int clients[CONNECTIONS_MAX];

void exit_with_msg(int code, const char *msg)
{
	(code == 0) ? printf("%s\n", msg) : perror(msg);
	exit(code);
}

void start_server(char *port)
{
	struct addrinfo hints;
	struct addrinfo *res;
	struct addrinfo *p;

	// getaddrinfo for host
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	if (getaddrinfo(NULL, port, &hints, &res) != 0) {
		exit_with_msg(1, "getaddrinfo() error");
	}

	// socket and bind
	for (p = res; p != NULL; p = p->ai_next) {
		listenFd = socket(p->ai_family, p->ai_socktype, 0);

		if (listenFd == -1) {
			continue;
		}

		if (bind(listenFd, p->ai_addr, p->ai_addrlen) == 0) {
			break;
		}
	}

	if (p == NULL) {
		exit_with_msg(1, "socket() or bind() error");
	}

	freeaddrinfo(res);

	// listen for incoming connections
	if (listen(listenFd, QUEUED_REQUESTS_MAX) != 0) {
		exit_with_msg(1, "listen() error");
	}
}

void create_header(char *header, const char *http_ver, const char *msg_text)
{
	strcpy(header, http_ver);
	strcat(header, " ");
	strcat(header, msg_text);
}

// client connection
void respond(int id)
{
	int fd;
	int received;
	int bytesRead;
	char path[PATH_MAX];
	char msg[MSG_MAX];
	char dataToSend[DATA_MAX];
	char prefix[HTTP_VER_LEN];
	char header_msg[MSG_MAX];
	char *reqLine[3];

	memset((void*) msg, (int) '\0', MSG_MAX);
	received = recv(clients[id], msg, MSG_MAX, 0);

	if (received < 0) { // receive error
		exit_with_msg(1, "recv() error");
	}
	else if (received == 0) { // receive socket closed
		exit_with_msg(1, "client disconnected upexpectedly");
	}
	else { // message received
		//printf("%s", msg); // debug only
		reqLine[0] = strtok(msg, " \t\n");

		if (strncmp(reqLine[0], GET_REQ, strlen(GET_REQ)) == 0) {
			reqLine[1] = strtok(NULL, " \t");
			reqLine[2] = strtok(NULL, " \t\n");

			if (strncmp(reqLine[2], HTTP_1_0, strlen(HTTP_1_0)) != 0 &&
				strncmp(reqLine[2], HTTP_1_1, strlen(HTTP_1_1)) != 0) {

				create_header(header_msg, HTTP_1_0, BAD_REQ_MSG);
				send(clients[id], header_msg, strlen(header_msg), 0);
			}
			else {
				if (strncmp(reqLine[2], HTTP_1_0, strlen(HTTP_1_0)) == 0) {
					strncpy(prefix, HTTP_1_0, strlen(HTTP_1_0));
				}
				else {
					strncpy(prefix, HTTP_1_1, strlen(HTTP_1_0));
				}

				if (strncmp(reqLine[1], "/\0", 2) == 0) {
					reqLine[1] = (char *) INDEX_FILE_NAME; // if no file is specified, index.html will be opened by default
				}

				strcpy(path, documentRoot);
				strcpy(&path[strlen(documentRoot)], reqLine[1]);

				if ((fd = open(path, O_RDONLY)) != -1) { // file found
					printf("file: %s\n", path);

					create_header(header_msg, prefix, OK_MSG);
					send(clients[id], header_msg, strlen(header_msg), 0);
					while ((bytesRead = read(fd, dataToSend, DATA_MAX)) > 0) {
						write(clients[id], dataToSend, bytesRead);
					}
				}
				else {
					create_header(header_msg, prefix, NOT_FOUND_MSG);
					send(clients[id], header_msg, strlen(header_msg), 0);
					write(clients[id], NOT_FOUND_BODY, strlen(NOT_FOUND_BODY));
				}
			}
		}
	}

	// closing socket
	shutdown(clients[id], SHUT_RDWR); // all further send and recieve operations are DISABLED
	close(clients[id]);
	clients[id] = -1;
}

int main(int argc, char* argv[])
{
	int id;
	char port[6];
	struct sockaddr_in clientAddr;
	socklen_t addrLen;

	// default values
	documentRoot = getenv("PWD");
	strcpy(port, "8080");

	// parsing the command line arguments
	char arg;
	while ((arg = getopt(argc, argv, "p:r:h")) != -1) {
		switch (arg) {
		case 'r':
			documentRoot = malloc(strlen(optarg));
			strcpy(documentRoot, optarg);
			break;

		case 'p':
			strcpy(port, optarg);
			break;

		case 'h':
			exit_with_msg(0, "Usage: web_server -p <port> -r <document_root>");
			break;

		case '?':
			exit_with_msg(1, "Wrong arguments given");
			break;

		default:
			exit(1);
		}
	}

	// setting all elements to -1: signifies there is no client connected
	int i;
	for (i = 0; i < CONNECTIONS_MAX; i++) {
		clients[i] = -1;
	}

	start_server(port);

	printf("Web Server started at port %s with root directory as %s\n", port, documentRoot);

	// accept connections
	id = 0;
	while (1) {
		addrLen = sizeof(clientAddr);
		clients[id] = accept(listenFd, (struct sockaddr *) &clientAddr, &addrLen);

		if (clients[id] < 0) {
			exit_with_msg(1, "accept() error");
		}
		else {
			if (fork() == 0) {
				respond(id);
				exit(0);
			}
		}

		while (clients[id] != -1) {
			id = (id + 1) % CONNECTIONS_MAX;
		}
	}

	return 0;
}

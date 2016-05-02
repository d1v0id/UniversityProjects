/*
 * client_server.h
 *
 *      Author: dmitry
 */

#ifndef CLIENT_SERVER_H_
#define CLIENT_SERVER_H_

#include <stdio.h>

const int BUFFER_SIZE = 256;
const char* NO_HOST_MSG = "No such host";
const char* BIND_ERR_MSG = "Binding error";
const char* CONN_ERR_MSG = "Connection error";
const char* ACCEPT_ERR_MSG = "Accepting error";
const char* SOCKET_OPEN_ERR_MSG = "Opening socket error";
const char* SOCKET_WRITE_ERR_MSG = "Writing to socket error";
const char* SOCKET_READ_ERR_MSG = "Reading from socket error";
const char* EXIT_CMD = "exit";

void exit_with_msg(int code, const char *msg);

#endif /* CLIENT_SERVER_H_ */

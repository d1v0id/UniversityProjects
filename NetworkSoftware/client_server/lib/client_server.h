#ifndef CLIENT_SERVER
#define CLIENT_SERVER

#include <stdio.h>

const int BUFFER_SIZE = 256;
const char* NO_HOST_MSG = "No such host";
const char* BIND_ERR_MSG = "Binding error";
const char* CONN_ERR_MSG = "Connection error";
const char* ACCEPT_ERR_MSG = "Acception error";
const char* SOCKET_OPEN_ERR_MSG = "Opening socket error";
const char* SOCKET_WRITE_ERR_MSG = "Writing to socket error";
const char* SOCKET_READ_ERR_MSG = "Reading from socket error";
const char* EXIT_CMD = "exit";

void exit_with_msg(int code, const char *msg);

#endif

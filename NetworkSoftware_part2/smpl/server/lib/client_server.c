/*
 * client_server.c
 *
 *      Author: dmitry
 */

#include <stdio.h>
#include <stdlib.h>

void exit_with_msg(int code, const char *msg)
{
  (code == 0) ? printf("%s\n", msg) : perror(msg);
  exit(code);
}

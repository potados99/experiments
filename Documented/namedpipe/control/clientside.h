#ifndef write_h
#define write_h

#include "ipc.h"
#include "strutils.h"

#include <signal.h>

#define REQ_PIPE_NAME "req"

void on_response(char *recieved);

void sig_handler(int sig);
void done(void);

#endif /* write_h */

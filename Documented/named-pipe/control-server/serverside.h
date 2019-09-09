#ifndef read_h
#define read_h

#include "ipc.h"
#include "strutils.h"
#include "serial.h"

#define REQ_PIPE_NAME "req"

#define PIDBUF_SIZE 16
#define CMDBUF_SIZE 32

void action(char *recieved);

int open_res_pipe(const char *pid);

#endif /* read_h */

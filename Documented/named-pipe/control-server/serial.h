#ifndef serial_h
#define serial_h

#include "includes.h"
#include "ipc.h"

#include <termios.h>
#include <fcntl.h>
#include <time.h>

#define ARGS_MAX 3
#define CMDBUFF_MAX 64
#define SERIAL_TIMEOUT 2

int serial_open(const char *port, int baudrate);
bool serial_send(int fd, char delim, char *wbuf, char *rbuf, int rbufSize);

void _set_interface_attribs(int fd, int speed, int parity);
void _set_blocking(int fd, int should_block);

#endif

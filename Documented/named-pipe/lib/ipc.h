#ifndef ipc_h
#define ipc_h

#include "includes.h"

#include <fcntl.h>
#include <sys/unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/poll.h>

typedef void (*lcallback_t)(char *);

typedef enum bool {
	FALSE = 0,
	TRUE = 1
} bool;

struct listenparam {
	int 		fd;
	char 		delim;
	char 		behavior;
	lcallback_t	callback;
};

#define TERMINATE '\n'
#define DIVIDER '/'

#define IPC_WBUF_SIZE 32

#define L_KEEP 0x10 // keep listening
#define L_CLBCK 0x01 // launch callback

void ipc_listen(struct listenparam param);
int ipc_read(int fd, char delim, char *rbuf, unsigned int rbufSize);
int ipc_write(int fd, char delim, const char *wbuf);

int open_pipe(const char *name, int mode);
void make_pipe(const char *name);
void remove_pipe(const char *name);

#endif /* ipc_h */

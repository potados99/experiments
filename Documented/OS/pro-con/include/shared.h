#ifndef _shared_h
#define _shared_h

#include "ringbuf.h"
#include <semaphore.h>

extern sem_t 	empty;
extern sem_t 	occupied;

extern rbuf_t	shrd_buf;

#endif /* _shared_h */

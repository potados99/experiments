#ifndef _fork_h
#define _fork_h

#include <semaphore.h>

struct fork {
	sem_t	lock;
};

typedef struct fork fork_t;

int fork_init(fork_t *fork);
int fork_destroy(fork_t *fork);

int fork_up(fork_t *fork);
int fork_down(fork_t *fork);

#endif /* _fork_h */

#include "fork.h"

#include <semaphore.h>
#include <stdio.h>

/*
struct fork {
	sem_t	lock;
};

typedef struct fork fork_t;
*/

int fork_init(fork_t *fork) {
	if (sem_init(&(fork->lock), 0, 1)) {
		perror("error while sem_init()");
		return -1;
	}

	return 0;
}

int fork_destroy(fork_t *fork) {

}

int fork_up(fork_t *fork) {

}

int fork_down(fork_t *fork) {

}

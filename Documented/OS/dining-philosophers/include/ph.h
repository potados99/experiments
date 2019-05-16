#ifndef _phil_h
#define _phil_h

#include <semaphore.h>

enum dining_state {
	EATING = 1,
	THINKING
};

struct phil {
	int state;
	sem_t shrd_sem; /* all philosophers will have same semaphore. */
};

typedef struct phil phil_t;

int phil_init(phil_t *phil);
int phil_destory(phil_t *phil);

// eat, think, loop, etc...

#endif /* _phil_h */

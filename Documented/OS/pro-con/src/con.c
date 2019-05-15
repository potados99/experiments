#include "con.h"
#include "ringbuf.h"
#include "shared.h"

#include <stdio.h>
#include <semaphore.h>
#include <unistd.h>

void *consume_loop(void *arg) {
	printf("consume_loop is working! :)\n");
	
	int val;

	while(1) {
		if (sem_wait(&occupied)) {
			perror("error while sem_wait() by consumer");
		}

		while (!rb_is_empty(&shrd_buf)) {
			usleep(120000);
			val = rb_pop(&shrd_buf);
			printf("consumer got %d.\n", val);	
		}
	
		if (sem_post(&empty)) {
			perror("error while sem_post() by consumer");
		}
	}
	
	return NULL;
}

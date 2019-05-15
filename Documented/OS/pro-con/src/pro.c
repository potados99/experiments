#include "pro.h"
#include "ringbuf.h"
#include "shared.h"

#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

void *produce_loop(void *arg) {
	printf("produce_loop works :)\n");
	
	int value = 0;
	int count = 0;

	srand(time(NULL));

	while(1) {
		if (sem_wait(&empty)) {
			perror("error while sem_wait() by producer");
		}

		count = (rand() % 10) + 1;	
		puts("");
		for (int i = 0; i < count; ++i) {
			usleep(300000);
			rb_push(&shrd_buf, ++value);
			printf("producer added %d to buffer.\n", value);
		}

		if (sem_post(&occupied)) {
			perror("error while sem_post() by producer");
		}
	}
	
	return NULL;
}

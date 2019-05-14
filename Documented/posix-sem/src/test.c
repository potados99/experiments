#include "test.h"

#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

sem_t sem;
int count = 0;

void *thread_func(void *arg) {
	srand(time(NULL));

	int t_num = *(int *)arg;

	while(1) {
		usleep(rand() % 100000);

		/**
		  * trying to get semaphore.
		  */
		if (sem_trywait(&sem)) {
			if (errno == EAGAIN) {
				printf("Thread %d is waiting...\n", t_num);
				continue; /* semaphore already taken. */
			} else {
				perror("error while sem_trywait()");
				exit(1);
			}
		}

		///////// CRITICAL AREA START //////////

		printf("\nThread %d entered critical area.\n", t_num);

		if (count >= 10) {
			printf("Thread %d is done.\n\n", t_num);

			if (sem_post(&sem)) {
				perror("error while sem_post()");
			}
			break;
		}
	
		printf("	count: %d -> %d.\n", count, count + 1);
		++count;

		printf("Thread %d is to leave critical area.\n\n", t_num);

		///////// CRITICAL AREA END ////////////


		if (sem_post(&sem)) {
			perror("error while sem_post()");
		}
	}

	return NULL;
}

void test() {

	/* not share between processes, initial value is 1. */
	if (sem_init(&sem, 0, 1)) {
		perror("error while sem_init()");
		exit(1);
	}

	pthread_t thread1;
	pthread_t thread2;

	int num_t1 = 1;
	int num_t2 = 2;
	
	pthread_create(&thread1, NULL, thread_func, &num_t1);
	pthread_create(&thread2, NULL, thread_func, &num_t2);

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

	return ;
}

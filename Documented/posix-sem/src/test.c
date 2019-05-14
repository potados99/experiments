#include "test.h"

#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>

sem_t sem;

void *thread_func(void *arg) {
	int t_num = *(int *)arg;

	while(1) {
		/**
		  * trying to get semaphore.
		  */
		if (sem_trywait(&sem)) {
			if (errno == EAGAIN)
				continue; /* semaphore already taken. */
			else {
				perror("error while sem_trywait()");
				exit(1);
			}
		}

		///////// CRITICAL AREA START //////////

		printf("Thread %d entered critical area.\n", t_num);


		printf("Thread %d is to leave critical area.\n", t_num);

		///////// CRITICAL AREA END ////////////


		if (sem_post(&sem)) {
			perror("error while sem_post()");
		}
	}
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

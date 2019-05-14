#include "sem_test.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#include "sem.h"

#define SEM_KEY		981633
#define SEM_SIZE	1

#define UP		1
#define DOWN		-1

int global_count = 0;
int semid = 0;

void *t1(void *arg);
void *t2(void *arg);


/**
  * Entry.
  */
void sem_wrap_test() {
	semid = sem_get(SEM_KEY, SEM_SIZE);

	pthread_t thread1;
	pthread_t thread2;

	pthread_create(&thread1, NULL, t1, NULL);
	pthread_create(&thread2, NULL, t2, NULL);
	
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
}


void *t1(void *arg) {
	while(1) {
		usleep(100);

		if (sem_down(semid, 0, 99) == 99) {
			puts("t1 waiting");
			continue;
		}

		/**/

		printf("t1 entered ciritical section.\n");
		fflush(stdout);

		if (global_count < 5) {
			++global_count;
			printf("t1 increase counter: now %d.\n", global_count);
			fflush(stdout);
		}
		else {
			sem_up(semid);
			break;
		}

		printf("t1 to leave critical section.\n");
		fflush(stdout);

		/**/

		sem_up(semid);
	}

	return NULL;
}

void *t2(void *arg) {
	while(1) {
		usleep(100);

		if (sem_down(semid, 0, 99) == 99) {
			puts("t2 waiting");
			continue;
		}

		/**/

		printf("t2 entered critical section.\n");
		fflush(stdout);

		if (global_count < 5) {
			++global_count;
			printf("t2 increase counter: now %d.\n", global_count);
			fflush(stdout);
		}
		else {
			sem_up(semid);
			break;
		}

		printf("t2 to leave critical section.\n");
		fflush(stdout);

		/**/

		sem_up(semid);
	}

	return NULL;
}



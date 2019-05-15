#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <pthread.h>


/**
  * thread functions
  */
void *thread_fun1(void *arg);
void *thread_fun2(void *arg);

pthread_t thread_one;
pthread_t thread_two;

pthread_mutex_t mutex_one;
pthread_mutex_t mutex_two;

int main(int argc, const char * argv[]) {
	
	pthread_mutex_init(&mutex_one, NULL);
	pthread_mutex_init(&mutex_two, NULL);

	pthread_create(&thread_one, NULL, thread_fun1, NULL);
	pthread_create(&thread_two, NULL, thread_fun2, NULL);

	pthread_join(thread_one, NULL);
	pthread_join(thread_two, NULL);

	return 0;
}

void *thread_fun1(void *arg) {
	pthread_mutex_lock(&mutex_one);
	
	printf("thread1 got mutex one. now trying to get mutex_two.\n");

	pthread_mutex_lock(&mutex_two);

	/**
	  * IMPOSSIBLE AREA
	  */

	pthread_mutex_unlock(&mutex_two);

	pthread_mutex_unlock(&mutex_one);
	printf("thead1 released mutex one.");

	return NULL;
}

void *thread_fun2(void *arg) {
	pthread_mutex_lock(&mutex_two);
	
	printf("thread2 got mutex two. now trying to get mutex_one.\n");

	pthread_mutex_lock(&mutex_one);

	/**
	  * IMPOSSIBLE AREA
	  */

	pthread_mutex_unlock(&mutex_one);

	pthread_mutex_unlock(&mutex_two);
	printf("thead1 released mutex one.");

	return NULL;
}

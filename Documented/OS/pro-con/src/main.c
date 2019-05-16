#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <error.h>

#include "pro.h"
#include "con.h"

#include "ringbuf.h"

/**
  * shared
  */
sem_t	empty;
sem_t	occupied;

rbuf_t	shrd_buf;

int main(int argc, const char * argv[]) {

	pthread_t	thread_pro;
	pthread_t	thread_con;
	int		errno_local;

	/**
	  * Init buffer
	  */
	if ((errno_local = rb_init(&shrd_buf, 10))) { 
		/* init shared ring buffer with capacity 10. */
		error(1, errno_local, "error while rb_init()");
	}
	
	/**
	  * Init semaphore
	  */
	if (sem_init(&empty, 0, 1)) {
		perror("error while sem_init() with &empty");
		exit(1);
	}

	if (sem_init(&occupied, 0, 0)) {
		perror("error while sem_init() with &occupied");
	}


	/**
	  * Create
	  */
	if ((errno_local = pthread_create(&thread_pro, NULL, produce_loop, NULL))) {
		error(1, errno_local, "error while pthread_create() with &thread_pro");
	}
	
	if ((errno_local = pthread_create(&thread_con, NULL, consume_loop, NULL))) {
		error(1, errno_local, "error while pthread_create() with &thread_con");
	}	

	/**
	  * Join
	  */
	if ((errno_local = pthread_join(thread_pro, NULL))) {
		error(1, errno_local, "error while pthrea_join() with thread_pro");
	}

	if ((errno_local = pthread_join(thread_con, NULL))) {
		error(1, errno_local, "error while pthrea_join() with thread_con");
	}

	
	printf("\nboth producer and comsumer did their jobs. now will exit.\n");

	/**
	  * Finish
	  */
	sem_destroy(&empty);
	sem_destroy(&occupied);
	rb_free(&shrd_buf);

	return 0;
}

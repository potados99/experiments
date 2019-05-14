#include "sem_test.h"

#include <stdio.h>
#include <stdlib.h>

#define SEM_KEY		981633
#define SEM_SIZE	1

#define UP		1
#define DOWN		-1


void sem_test() {

	/**
	  * Getting semaphore.
	  */
	int key = SEM_KEY;
	int size = SEM_SIZE;
	int flags = IPC_CREAT | SEM_A | SEM_R | (SEM_A >> 3) | (SEM_R >> 3);
	int id;

	if ((id = semget(key, size, flags)) == -1) {
		perror("error while semget()");
		exit(-1);
	}
	
	printf("semaphore of size %d succesfully optained with id %d.\n", size, id);



	struct sembuf aquire = {
		.sem_num = 0,
		.sem_op = DOWN,
		.sem_flg = IPC_NOWAIT | SEM_UNDO /* no wait, undo semaphore when process finished without returning it. */
	};

	struct sembuf release = {
		.sem_num = 0,
		.sem_op = UP,
		.sem_flg = IPC_NOWAIT | SEM_UNDO /* no wait, undo semaphore when process finished without returning it. */
	};

	



}

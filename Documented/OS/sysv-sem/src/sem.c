#include "sem.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/sem.h>

int sem_get(int key, int size) {
	int flags;
	int id;
	
	flags = IPC_CREAT | SEM_A | SEM_R | (SEM_A >> 3) | (SEM_R >> 3);

	if ((id = semget(key, size, flags)) == -1) {
		perror("error while semget()");
		exit(-1);
	}

	return id;
}

static inline int sem_op(int id, int op, int block, int ret) {
	struct sembuf op_arg = {
		.sem_num = 0,
		.sem_op = op,
		.sem_flg = SEM_UNDO
	};

	int to_return = 0;

	if (!block) {
		op_arg.sem_flg |= IPC_NOWAIT;
	}

	if (semop(id, &op_arg, 0)) {
		/**
		  * error or semaphore under zero.
		  */
		int e = errno; /* save errno. */

		if (!block) {
			printf("sem_op non-block return.\n");
			fflush(stdout);
			return to_return;
		}
		else {
			errno = e;
			perror("error while semop()");
			return -1;
		}
	}
	else {
		/**
		  * operation successful.
		  */
		printf("sem_op with %d successful.\n", op);
		fflush(stdout);
		
		return 0;
	}
}

int sem_down(int id, int block, ...) {
	int to_return = 0;

	if (!block) {
		va_list vlist;
		va_start(vlist, block);
		to_return = va_arg(vlist, int);
		va_end(vlist);
	}

	return sem_op(id, -1, block, to_return);
}

int sem_up(int id) {
	return sem_op(id, 1, 0, 0); /* non-block */
}

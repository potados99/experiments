#ifndef proc_h
#define proc_h

#include<sys/types.h>

#define MAX_PROCESS 16

/**
  * Mini proc.
  */
struct mproc {
	struct mproc *forw;
	struct mproc *back;

	char	**argv;
	pid_t 	pid;
	int 	flag;
};

struct mproc_list {
	struct mproc *head;
	struct mproc *tail;
	int size;
};

struct mproc	*mproc_insert(struct mproc **node, struct mproc data);
struct mproc	*mproc_append(struct mproc **node, struct mproc data);
struct mproc 	*mproc_remove(struct mproc **node); /* get next available node. */


#endif /* proc_h */

#ifndef proc_h
#define proc_h

#include <sys/types.h>

#define MAX_PROCESS 16

#define PRFL_FG 0x01
#define PRFL_BG 0x02

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

/**
  * Add item to the left side of the node.
  */
struct mproc	*mproc_put_l(struct mproc *node, struct mproc data);

/**
  * Add item to the right side of the node.
  */
struct mproc	*mproc_put_r(struct mproc *node, struct mproc data);

/**
  * Add item to the start of the list where the node is.
  */
struct mproc	*mproc_insert(struct mproc *node, struct mproc data);

/**
  * Add item to the end of the list where the node is.
  */
struct mproc	*mproc_append(struct mproc *node, struct mproc data);


/**
  * Remove node.
  * @return	available neighbor node is selected. 
  		if both back and forward are available, forward is prefered.
  */
struct mproc 	*mproc_remove(struct mproc *node); 

/**
  * Find start node of the list where the node is.
  */
struct mproc 	*mproc_seek_bgn(struct mproc *node);

/**
  * Find last node of the list where the node is.
  */
struct mproc	*mproc_seek_end(struct mproc *node);

#endif /* proc_h */

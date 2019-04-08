#include "mproc.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
struct mproc {
	struct mproc *forw;
	struct mproc *back;

	char 	**argv;
	pid_t 	pid;
	int 	flag;
};

struct mproc_list {
	struct mproc *head;
	struct mproc *tail;
	int size;
}
*/


struct mproc *mproc_insert(struct mproc **node, struct mproc data) {
	//if (node == NULL) return NULL;

	struct mproc *origin = *node;
	struct mproc *new = (struct mproc *)malloc(sizeof(struct mproc) + 1);
	memset(new, 0, sizeof(struct mproc) + 1); /* clear */
	*new = data; /* value copy here! */
	new->forw = NULL;
	new->back = NULL;

	if (origin) {
		origin->back = new;
		new->back = NULL;
		new->forw = origin;
	}
	else {
		*node = new;
	}
	/*
	 New head stands at the begining of the list, leaving the original head behind.  
	 */

	return new;
}

struct mproc *mproc_append(struct mproc **node, struct mproc data) {
	//if (node == NULL) return NULL;

	struct mproc *origin = *node;
	struct mproc *new = (struct mproc *)malloc(sizeof(struct mproc) + 1);
	memset(new, 0, sizeof(struct mproc) + 1); /* clear */
	*new = data; /* value copy here! */
	new->forw = NULL;
	new->back = NULL;
	
	if (origin) {
		origin->forw = new;
		new->back = origin;
		new->forw = NULL;
	}
	else {
		*node = new;
	}

	return new;
}


struct mproc *mproc_remove(struct mproc **node) {
	if (node == NULL) return NULL;
	
	struct mproc *origin = *node;
	struct mproc *next = (*node)->forw;
	struct mproc *before = (*node)->back;

	if (before && next) {
		before->forw = next;
		next->back = before;
	}
	else if (next) {
		next->back = NULL;
	}
	else if (before) {
		before->forw = NULL;
	}

	free(origin);

	return next;
}




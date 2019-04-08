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

struct mproc *mproc_put_l(struct mproc *node, struct mproc data) {
	//if (node == NULL) return NULL;

	struct mproc *origin_center = node;
	struct mproc *new = (struct mproc *)malloc(sizeof(struct mproc) + 1);
	memset(new, 0, sizeof(struct mproc) + 1); /* clear */
	*new = data; /* value copy here! */
	new->forw = NULL;
	new->back = NULL;

	if (origin_center) {
		struct mproc *origin_left = origin_center->back;

		origin_center->back = new;
		new->back = origin_left;
		new->forw = origin_center;
	}
	/*
	 New head stands at the begining of the list, leaving the original head behind.  
	 */

	return new;
}

struct mproc *mproc_put_r(struct mproc *node, struct mproc data) {
	//if (node == NULL) return NULL;

	struct mproc *origin_center = node;
	
	struct mproc *new = (struct mproc *)malloc(sizeof(struct mproc) + 1);
	memset(new, 0, sizeof(struct mproc) + 1); /* clear */
	*new = data; /* value copy here! */
	new->forw = NULL;
	new->back = NULL;
	
	if (origin_center) {
		struct mproc *origin_right = origin_center->forw;
			
		origin_center->forw = new;
		new->back = origin_center;
		new->forw = origin_right; 
	}

	return new;
}


struct mproc *mproc_insert(struct mproc *node, struct mproc data) {
	if (node) node = mproc_seek_bgn(node);

	return mproc_put_l(node, data);
}

struct mproc *mproc_append(struct mproc *node, struct mproc data) {
	/*
	 Expected behavior:
	 
	 case 1: when node is null ->
	 	wish to create one and propagate that to the node.

	 case 2: when node is not null ->
	 	two choices: to modify original pointer, or not!
	 
	 
	 */


	
	if (node) node = mproc_seek_end(node);

	return mproc_put_r(node, data);
}

struct mproc *mproc_remove(struct mproc *node) {
	if (node == NULL) return NULL;
	
	puts("hello");
	struct mproc *origin = node;
	struct mproc *next = node->forw;
	struct mproc *before = node->back;
	
	free(origin);
	puts("freed.");

	if (before && next) {
		before->forw = next;
		next->back = before;
		puts("both is selected.");	
		
		return next;
	}
	else if (next) {
		next->back = NULL;
		puts("next is selected.");	
		return next;
	}
	else /*before*/ {
		before->forw = NULL;
		puts("before is selected.");	
		return before;
	}
}

struct mproc *mproc_seek_bgn(struct mproc *node) {
	if (node == NULL) return NULL;

	struct mproc *current = node;

	while(current->back) {
		current = current->back;
	}
	return current;
}

struct mproc *mproc_seek_end(struct mproc *node) {
	if (node == NULL) return NULL;

	struct mproc *current = node;

	while(current->forw) {
		current = current->forw;
	}
	return current;
}


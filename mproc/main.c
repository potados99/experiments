#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mproc.h"


struct mproc *procs = NULL; /* a single node. */

void print_list(struct mproc *list) {
	struct mproc *current = list;
	while (current) { 
		printf("%d ", current->pid);

		current = current->forw;
	}
	puts("");
}



int main(int argc, char **argv) {
/*
	struct mproc *procs = NULL;
	mproc_insert(&procs, processes[0]);
	struct mproc *start = mproc_insert(&procs, processes[1]);
	mproc_append(&procs, processes[2]);

	struct mproc *iter = start;
	while (iter) {
		printf("pid %d.\n", iter->pid);
		iter = iter->forw;
	}

	return 0;
*/

	struct mproc ps[5] = {
		{ .pid = 1, .flag = 5, .argv = NULL, .forw = NULL, .back = NULL},
		{ .pid = 2, .flag = 4, .argv = NULL, .forw = NULL, .back = NULL},
		{ .pid = 3, .flag = 3, .argv = NULL, .forw = NULL, .back = NULL},
		{ .pid = 4, .flag = 2, .argv = NULL, .forw = NULL, .back = NULL},
		{ .pid = 5, .flag = 1, .argv = NULL, .forw = NULL, .back = NULL}

	};


	procs = mproc_append(procs, ps[0]); 
	procs = mproc_append(procs, ps[3]);
	printf("added ps[0](pid 1) and ps[3](pid 4).\n");
	printf("so it looks like: \n");

	print_list(procs);
	
	puts("iteration through two elements is done.");

	puts("then how will procs look like?");

	printf("procs is standing for node of pid %d\n", procs->pid);

	puts("lets add one more to the procs.");

	procs = mproc_insert(procs, ps[4]);

	puts("then I guess it is 1 ,4 and 5. right?");

	print_list(procs);

	puts("in fact NO! we did not append it. we inserted it.");
	puts("so we have to the start of the list.");

	procs = mproc_seek_bgn(procs);

	puts("moved procs to begin.");

	print_list(procs);

	puts("good right?");


	puts("then.. how about deletion?");

	puts("im gonna remove the process with pid 4!");

	struct mproc *st = procs;
	while (st) {
		if (st->pid == 4) {
			st = mproc_remove(st);
		}

		st = st->forw;
	}

	puts("hmm...");
	print_list(mproc_seek_bgn(procs));

	puts("add some !!");

	struct mproc *ns = mproc_seek_end(procs);

	mproc_append(ns, ps[2]);
	mproc_append(ns, ps[3]);

	ns = mproc_seek_bgn(procs);

	print_list(ns);

	struct mproc *survd = ns;
	
	puts("removing 5, left what?");

	survd = mproc_remove(survd);

	print_list(survd);

	puts("now removing the 3 in the middle!");

	survd = mproc_remove(survd->forw);

	print_list(mproc_seek_bgn(survd));

	return 0;
}


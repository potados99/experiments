#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "launch.h"
#include "str.h"
#include "userio.h"

#include <signal.h>
#include <sys/wait.h>
#include <sys/resource.h>

int bg_pid = 0;
int fg_pid = 0;

int last = 0;

uint8_t ioflags = 0;

void proc_exit() {
	int status;
	int pid;

	if (!bg_pid && !fg_pid) return;

	if (fg_pid)
		do {
			if ((pid = waitpid(fg_pid, &status, WNOHANG)) == -1) {
				perror("waitpid() failed.");
			}
			else if (pid == 0) {
				// child still running.
				sleep(1);
			}
			else {
				last = WEXITSTATUS(status);

				fg_pid = 0;

				ioflags = ADD(ioflags, IOFL_IN);

				show_prompt();
			}
		} while (pid == 0);
	
	else if (bg_pid)
		do {
			if ((pid = waitpid(bg_pid, &status, WNOHANG)) == -1) {
				perror("waitpid() failed.");
			}
			else if (pid == 0) {
				// child still running.
				sleep(1);
			}
			else {
				last = WEXITSTATUS(status);

				char buf[64] = {0, };
				sprintf(buf, "[background] %d done", bg_pid);
				say_prompt(buf);
				
				bg_pid = 0;
			}
		} while (pid == 0);		
}

void sig_handler(int sig) {
	switch (sig) {
		case SIGSEGV:
			
			exit(0);
			break;
	}
}

#include "mproc.h" 

int main(int argc, char *const argv[]) {
	

	struct mproc processes[5] = {
		{ .pid = 1, .flag = 5, .argv = NULL, .forw = NULL, .back = NULL},
		{ .pid = 2, .flag = 4, .argv = NULL, .forw = NULL, .back = NULL},
		{ .pid = 3, .flag = 3, .argv = NULL, .forw = NULL, .back = NULL},
		{ .pid = 4, .flag = 2, .argv = NULL, .forw = NULL, .back = NULL},
		{ .pid = 5, .flag = 1, .argv = NULL, .forw = NULL, .back = NULL}

	};

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

	signal(SIGCHLD, proc_exit);

	signal(SIGINT, sig_handler);
	signal(SIGSEGV, sig_handler);
	
	char **cmd;
	int result;

	ioflags = ADD(IOFL_IN, IOFL_OUT);

	clear();
	show_prompt();

	for (;;) {
		if (!HAS(ioflags, IOFL_IN)) continue;
		if (!HAS(ioflags, IOFL_OUT)) continue; /* both IOFL_IN and IOFL_OUT required. */

		cmd = get_strings(stdin, 128, " \t\n"); /* get strings tokenized by space character, from stdin. */
		result = launch(cmd);
	
		if (NEED_TO_SHOW_PROMPT(result)) {
			show_prompt();
		}

		free_strs(cmd);
	}

	return 0;
}

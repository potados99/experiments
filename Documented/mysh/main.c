#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "launch.h"
#include "str.h"
#include "userio.h"
#include "mproc.h" 

#include <signal.h>
#include <sys/wait.h>
#include <sys/resource.h>

struct mproc *procs = NULL;
int last = 0;
int ioflags = 0;

void proc_exit() {
	int status;
	int result;
	
	int flag;
	int pid;

	if (procs == NULL) return;

	for (;;) {
        
		struct mproc *current = mproc_seek_bgn(procs);

		while (current) {
            /* at least one process to handle. */

			result = waitpid(current->pid, &status, WNOHANG);
			flag = current->flag;
			pid = current->pid;

			if (result == -1) {
				perror("waitpid() failed.");
			}
			else if (result == 0) {
				/* still running */
			}
			else {
				/* done! */
				
				last = WEXITSTATUS(status);
				ioflags = ADD(ioflags, IOFL_IN); /* restore input. whatever foreground or background */

				if (HAS(flag, PRFL_BG)) {
                    say_prompt("[background] %d done", pid);
				}
				else if (HAS(flag, PRFL_FG)) {
					show_prompt();
				}
				else {
					fprintf(stderr, "THIS CANNOT HAPPEN.\n");
				}
				
				current = mproc_remove(current);
                procs = current;
                
                if (current == NULL) return;
                else continue;
			}

			current = current->forw;
            
		} /* end of while */
	} /* end of endless for */
} /* end of proc_exit() */

void sig_handler(int sig) {
	switch (sig) {
		case SIGSEGV:
			exit(0);
			break;
            
        default:
            break;
	}
}


int main(int argc, char *const argv[]) {

	signal(SIGCHLD, proc_exit);

	signal(SIGINT, sig_handler);
	signal(SIGSEGV, sig_handler);
	
	char **cmd;
	int result;

	ioflags = ADD(IOFL_IN, IOFL_OUT);

	clear_prompt();
	show_prompt();

	for (;;) {
        /* both IOFL_IN and IOFL_OUT required. */
		if (!HAS(ioflags, IOFL_IN)) continue;
		if (!HAS(ioflags, IOFL_OUT)) continue;

        /* get strings tokenized by space character, from stdin. */
		cmd = get_strings(stdin, 128, " \t\n");
		result = launch(cmd);
	
		if (NEED_TO_SHOW_PROMPT(result)) {
			show_prompt();
			free_strs(cmd);
		}
	}

	return 0;
}

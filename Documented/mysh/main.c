#include "launch.h"
#include "str.h"
#include "userio.h"
#include "mproc.h" 

#include <signal.h>
#include <sys/wait.h>
#include <sys/resource.h>

struct mproc        *procs = NULL;
int                 last = 0;
int                 ioflags = 0;

void sig_handler(int sig) {
	switch (sig) {
        case SIGCHLD:
            handle();
            break;
            
        case SIGINT:
            // nothing :)
            break;
            
		case SIGSEGV:
			exit(0);
			break;
            
        default:
            break;
	}
}

int main(int argc, char *const argv[]) {
    
    char **cmd;
    int result;
    
	signal(SIGCHLD, sig_handler);
	signal(SIGINT, sig_handler);
	signal(SIGSEGV, sig_handler);

	ioflags = ADD(IOFL_IN, IOFL_OUT);

	clear_prompt();
	show_prompt();

	for (;;) {
        /* both IOFL_IN and IOFL_OUT required. */
		if (!HAS(ioflags, IOFL_IN)) continue;
		if (!HAS(ioflags, IOFL_OUT)) continue;

        /* get tokenized strings from stdin. */
		cmd = get_strings(stdin, 128, " \t\n");
		result = launch(cmd);
	
		if (NEED_TO_SHOW_PROMPT(result)) {
            /*
             In case like:
             1) Returned just after spawning background process. (RET_BG)
             2) Command is a builtin function. (RET_BUILTIN)
             3) User typed nothing. (RET_NONE)
             
             See launch() for more information.
             */
            
			show_prompt();
			free_strs(cmd);
		}
	}

	return 0;
}

#include "launch.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>

#include "builtin.h"
#include "str.h"
#include "flags.h"
#include "userio.h"
#include "mproc.h"

#include <signal.h>
#include <sys/wait.h>
#include <sys/resource.h>

extern struct mproc     *procs;
extern int              last;
extern int              ioflags;

int launch(char **argv) {
	if (argv == NULL) return -1;

	int argc = -1;
	while (argv[++argc]);
	
	if (argc == 0) return RET_NONE;
	
	int background = 0;

	if (argv[argc - 1][0] == '&') {
		argv[argc - 1] = NULL;
		background = 1;
	}

	if (is_builtin(argv[0])) {
		last = launch_builtin(argv[0], argv[1]);
		
		return RET_BUILTIN;
	}
		
	int null_fd;
	
	int pid = fork();
	if (pid < 0) {
		/* fork error. */
		perror("fork() failed");
		return -1;
	}
	else if(pid == 0) {
		/* child. */
		
		if (background) {
			// kill background process output.
			null_fd = open("/dev/null", O_WRONLY);

			dup2(null_fd, 1);
			dup2(null_fd, 2);

			close(null_fd);
		}
		
		if (execvp(argv[0], argv) == -1) {
			fprintf(stderr, "command not found.\n");
			
			free_strs(argv);
			exit(99);
		}
		
	}
	else {
		/* parent. */

		struct mproc child = {
			.argv = argv,
			.pid = pid,
			.flag = (background ? PRFL_BG : PRFL_FG)
		};

		procs = mproc_append(procs, child);

		if (background) {
			printf("[background] %d\n", pid);
			
			return RET_BG;
		}
		else {
			ioflags = SUB(ioflags, IOFL_IN); /* temporarily disable input of parent. */

			return RET_FG;
		}
			
		return 0;
	}

	return -99;
}

void handle(void) {
    /* wait processes */
    int             status;
    int             result;
    
    /* save mproc status */
    struct mproc    *current;
    int             flag;
    int             pid;
    
    if (procs == NULL)
        return;
    
    for (;;) {
        
        current = mproc_seek_bgn(procs);
        
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
                
                if (HAS(flag, PRFL_BG))
                    say_prompt("[background] %d done", pid);
                
                else if (HAS(flag, PRFL_FG))
                    show_prompt();
                
                else
                    fprintf(stderr, "THIS CANNOT HAPPEN.\n");
                
                if ((procs = current = mproc_remove(current)) == NULL)
                    return;
                else
                    continue;
            }
            
            current = current->forw;
            
        } /* end of while */
    } /* end of endless for */
} /* end of proc_exit() */

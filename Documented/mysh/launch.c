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

#include <signal.h>
#include <sys/wait.h>
#include <sys/resource.h>


extern int bg_pid;
extern int fg_pid;
extern int last;

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
			int null = open("/dev/null", O_WRONLY);

			dup2(null, 1);
			dup2(null, 2);

			close(null);
		}
		
		if (execvp(argv[0], argv) == -1) {
			fprintf(stderr, "command not found.\n");

			free_strs(argv);
			exit(99);
		}
		
	}
	else {
		/* parent. */

		if (background) {
			bg_pid = pid;
			printf("[background] %d\n", pid);
			
			return RET_BG;
		}
		else {
			//printf("Y!\n");
			fg_pid = pid;
			
			int null = open("/dev/null", O_RDONLY);

			dup2(null, 3);
			// dup2(null, 3);

			close(null);
			
			return RET_FG;
		}
			
		return 0;
	}
	return -99;
}

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

int launch(char **argv) {
	if (argv == NULL) return -1;

	int background = 0;
	int argc = -1;
	while (argv[++argc]);
	
	if (argc == 0) return 0;

	if (argv[argc - 1][0] == '&') {
		argv[argc - 1] = NULL;
		background = 1;
	}

	if (is_builtin(argv[0])) return launch_builtin(argv[0], argv[1]);

	int pid = fork();
	if (pid < 0) {
		/* fork error. */
		fprintf(stderr, "fork error.\n");
		return -1;
	}
	else if(pid == 0) {
		/* child. */
		
	//	int original_stdout = dup(1);
	//	int original_stderr = dup(2);

		if (background) {
			// signal(SIGCHLD, NULL);
			
			int null = open("/dev/null", O_WRONLY);

			dup2(null, 1);
			dup2(null, 2);
			
		}

		if (execvp(argv[0], argv) == -1) {
	//		fprintf(stderr, "%s\n", strerror(errno));
			
			free_strs(argv);
			exit(99);
		}

	//	dup2(original_stdout, 1);
	//	dup2(original_stderr, 2);

	}
	else {
		/* parent. */
		int status = 0;
	
		if (background) {
			printf("[background] %d\n", pid);
			// fflush(stdout);
			bg_pid = pid;

			return 0;
		}
		if (waitpid(pid, &status, 0) == -1) {
			fprintf(stderr, "wait fail.\n");
			return -1;
		}
	}

	/*
	printf("going to launch %s ", argv[0]);
	
	if (argv[1]) printf("with arg: ");
	for (int i = 1; argv[i]; ++i) {
		printf("%s ", argv[i]);
	}

	printf("\n");
	*/
	return 0;
}

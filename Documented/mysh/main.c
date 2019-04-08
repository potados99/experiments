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

int main(int argc, char *const argv[]) {
	
	signal (SIGCHLD, proc_exit);
	
	char **cmd;
	int result;

	clear();
	show_prompt();

	for (;;) {
		cmd = get_strings(stdin, 128, " \t\n"); /* get strings tokenized by space character, from stdin. */
		result = launch(cmd);
	
		if (NEED_TO_SHOW_PROMPT(result)) {
			show_prompt();
		}

		free_strs(cmd);
	}

	return 0;
}

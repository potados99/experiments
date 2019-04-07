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

void proc_exit() {
	int state;
	int pid;

	while (wait(NULL) > 0) {
		if (bg_pid) {
			pid = waitpid(bg_pid, &state, 0);
		
			char buf[64] = {0, };
			sprintf(buf, "[background] %d done", pid);
			say_prompt(buf);
			bg_pid = 0;
			
			return;
		}
			
	}
}

int main(int argc, char *const argv[]) {
	
	signal (SIGCHLD, proc_exit);
	
	char **cmd;

	clear();
	show_prompt();

	for (;;) {
	
		cmd = get_strings(stdin, 128, " "); /* get strings tokenized by space character, from stdin. */
		launch(cmd);
		free_strs(cmd);

		show_prompt();
	}

	return 0;
}

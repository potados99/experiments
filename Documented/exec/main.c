#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/*
   Under are from man page.

SYNOPSIS
     #include <unistd.h>

     extern char **environ;

     int
     execl(const char *path, const char *arg0, ...); // , (char *)0

     int
     execle(const char *path, const char *arg0, ...); //, (char *)0, char *const envp[]

     int
     execlp(const char *file, const char *arg0, ...); //, (char *)0;

     int
     execv(const char *path, char *const argv[]);

     int
     execvp(const char *file, char *const argv[]);

     int
     execvP(const char *file, const char *search_path, char *const argv[]);
*/

int main(int argc, char *const argv[]) {
	
	if (argc == 1) {
		puts("No arguments.");
		puts("Usage: runner command args...");
		exit(0);
	}
	

	int pid;
	if ((pid = fork())) {
		/**
		 * parent. wait until child process done.
		 */
		wait(NULL) /* no state check. */;
		printf("execution of %s is done.\n", argv[1]);
	}

	else {
		/**
		 * execution body.
		 */
		printf("execution of %s is going to be made.\n", argv[1]);
		execvp(argv[1], argv + 1); 
	}

	return 0;
}

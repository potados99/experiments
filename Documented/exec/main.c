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
		exit(0);
	}
		
	execvp(*(argv + 1), argv + 1); 
	/* 
	   Start executable that has name of 'first argument'. 
	   Arguments for that executable including its name is stored in an array, starting from 'argv + 1'. 
	 */
	
	return 0;

}

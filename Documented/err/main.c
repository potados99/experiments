#include <stdio.h>
#include <string.h>
#include <error.h>
#include <errno.h>
#include <err.h>
#include <stdbool.h>
#include <stdlib.h>

void errorme() {
	fprintf(stderr, "my-gorgeous-app:");
}

int main(int argc, char * argv[]) {
	// insert code here...
	printf("Hello, world!\n");

	char *origin = strerror(0);
	char *cur_str = origin;

	printf("[ On memory ]\n");
	for(int i = 0; i < 1000; ++i, cur_str += strlen(cur_str) + 1) {
		if (strlen(cur_str)) printf("%d:\t<+%d>\tat %p\t\"%s\"\n", i, cur_str - origin, cur_str,  cur_str);
	}

	cur_str = origin;
	printf("[ In order of errno: ]\n");
	for(int i = 0; i < 124; cur_str = strerror(++i)) {
		printf("%d:\t<+%d>\tat %p\t\"%s\"\n", i, cur_str - origin, cur_str, cur_str);
	}

	// fopen(ag, "r");

//	perror("perror called");

//	error_print_progname = errorme;


	puts("");
	
	malloc(-1);
	//error_at_line(0, errno, __FILE__, __LINE__, "%s", "error_at_line() called");
	error(1, 0, "error called"); /* first parameter is a number that will be returned to console, when the second one is non-zero. */
	err(1, "err called."); /* similar to error, but the second parameter of that is not given. it takes errno as a condition. */

	printf("alive zone\n");

	return 0;
}


#include <stdio.h>
#include <string.h>
#include <error.h>
#include <errno.h>
#include <err.h>
#include <stdbool.h>

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

	char *ag = "ky";

	// fopen(ag, "r");

//	perror("perror called");

//	error_print_progname = errorme;

	error_at_line(errno, errno, __FILE__, __LINE__, "\"%s\"", ag);

	bool a = true;

	return 0;
}


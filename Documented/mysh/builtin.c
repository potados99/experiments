#include "builtin.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <errno.h>

typedef int (*builtin_fp)(const char *);

struct builtin {
	char name[32];
	builtin_fp function;
};

static struct builtin builtins[] = {
	{"cd", builtin_cd},
	{"exit", builtin_exit}
};


int is_builtin(const char *file) {
	if (file == NULL) return 0;

	int n_builtins = sizeof(builtins) / sizeof(struct builtin);
	if (n_builtins == 0) return 0;

	for (int i = 0; i < n_builtins; ++i) {
		if (strcmp(builtins[i].name, file) == 0) return 1;
	}

	return 0;
}

int launch_builtin(const char *function, const char *param) {
	if (function == NULL) return -1;

	int n_builtins = sizeof(builtins) / sizeof(struct builtin);
	if (n_builtins == 0) return -1;

	for (int i = 0; i < n_builtins; ++i) {
		if (strcmp(builtins[i].name, function) == 0) {
			return builtins[i].function(param);
		}
	}
	
	return -1;
}


int builtin_cd(const char *path) {
	char *validpath;
	
	if (path == NULL) {
		struct passwd *pw = getpwuid(getuid());
		validpath = pw->pw_dir;
	}
	else {
		validpath = path;
	}

	int result = chdir(validpath);
	if (result != 0) fprintf(stderr, "%s.\n", strerror(errno));
	return result;
}


int builtin_exit(const char *num) {
	int validnum;
	
	if (num == NULL) {
		validnum = 0;
	}
	else {
		char *endptr;
		validnum = strtol(num, &endptr, 10);
		if (endptr == num || *endptr != '\0') {
			fprintf(stderr, "exit error.\n");
			return -1;
		}
	}

	exit(validnum);

	/* return 0; */
}



#include "userio.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "str.h"

void clear() {
	printf("\033[H\033[J");
}

void show_prompt() {
	char username_buf[64] = {0, };
	char hostname_buf[64] = {0, };
	char cwd_buf[128] = {0, };

	getlogin_r(username_buf, sizeof(username_buf));
	gethostname(hostname_buf, sizeof(hostname_buf));
	getcwd(cwd_buf, sizeof(cwd_buf));
	

	printf("<%s@%s> %s $ ", username_buf, hostname_buf, cwd_buf);
}

char *const *get_strings(FILE *stream, int max, char *tokens) {

	if (stream == NULL) return NULL;
	if (max <= 0) return NULL;

	char single_buf[max];
	if (fgets(single_buf, sizeof(single_buf), stream) != single_buf) return NULL;
	
	int n_strings = 0;
	char **strings = (char **)malloc(sizeof(char *) * (n_strings + 1));

	char *substr = strtok(single_buf, tokens);
	while (substr) {

		strings = (char **)realloc(strings, sizeof(single_buf) * (++n_strings + 1));
		if (!strings) return NULL;

		strings[n_strings - 1] = alloc_str(substr);

		substr = strtok(NULL, tokens);
	}
	
	strings[n_strings] = NULL;

	return strings;
}


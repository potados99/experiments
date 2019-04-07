#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "launch.h"
#include "str.h"
#include "userio.h"

int main(int argc, char *const argv[]) {

	char *const *strs;

	clear();
	show_prompt();

	for (;;) {
		strs = get_strings(stdin, 128, " "); /* get strings from stdin, tokenized by space character. */
	}

	return 0;
}

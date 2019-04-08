#include "conv.h"

#include <stdio.h>
#include <stdlib.h>

int to_int(const char *digits, int base, int *num_out) {
	char *end;
	int result;

	result = strtol(digits, &end, base);
	if (*digits != '\0' && *end == '\0') {
		// success
		*num_out = result;
		return 0;
	}
	else {
		return -1;
	}
}

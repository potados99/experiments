#include "str.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <errno.h>

#define BUFFER_SIZE 128

char *alloc_str(char *buffer) {
	int size = strlen(buffer) + 1;
	char *string = (char *)malloc(sizeof(char) * size);
	snprintf(string, size, "%s", buffer);
	return string;
}

char **alloc_strs(char **buffer, int count) {
	char **strings = (char **)malloc(sizeof(char *) * count + 1);
	int size = 0;
	for (unsigned int i = 0; i < count; ++ i) {
		size = strlen(buffer[i]) + 1;
		strings[i] = (char *)malloc(sizeof(char) * size);
		snprintf(strings[i], size, "%s", buffer[i]);
	}
	return strings;
}

#ifndef userio_h
#define userio_h

#include <stdio.h>

void clear();

void show_prompt();

char *const *get_strings(FILE *stream, int max, char *tokens);

#endif

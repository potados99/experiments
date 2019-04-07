#ifndef userio_h
#define userio_h

#include <stdio.h>

void clear();

void show_prompt();
void say_prompt(char *message);

char **get_strings(FILE *stream, int max, char *tokens);

#endif

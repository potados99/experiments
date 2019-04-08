#ifndef userio_h
#define userio_h

#include <stdio.h>

#define IOFL_OUT 	0x01
#define IOFL_IN 	0x02

void clear_prompt(void);

void show_prompt(void);
void say_prompt(char *fmt, ...);

char **get_strings(FILE *stream, int max, char *tokens);

#endif /* userio_h */

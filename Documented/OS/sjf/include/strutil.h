#ifndef _strutil_h
#define _strutil_h

#include "pio.h"

char *mystrtok(char **m, char *s, char c);

/**
  * pick and iterate through lines in a bunch of text.
  */
void split_foreach(const char *text, int len, char delim, str_callback callback); 

#endif /* _strutil_h */

#ifndef str_h
#define str_h

char *alloc_str(char *buffer);
char **alloc_strs(char **buffer, int count);

void free_strs(char *strings[]);

#endif

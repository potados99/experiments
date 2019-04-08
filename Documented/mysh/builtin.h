#ifndef builtin_h
#define builtin_h

int is_builtin(const char *file);
int launch_builtin(const char *function, const char *param);

int builtin_cd(const char *path);
int builtin_exit(const char *num);

#endif /* builtin_h */

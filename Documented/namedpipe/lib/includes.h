#ifndef marcos_h
#define marcos_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

#define ERROR(x) { fprintf(stderr, "[ERROR] %s", x); exit(1); }
#define ERRORF(x, ...) { fprintf(stderr, "[ERROR] ");  fprintf(stderr, x, __VA_ARGS__); exit(1); }

#define MIN(X,Y) ((X) < (Y) ? (X) : (Y))

#ifdef VERBOSE
#define LOG(x) fprintf(stdout, "%s", x);
#define LOGF(x, ...) fprintf(stdout, x, __VA_ARGS__);
#else
#define LOG(x);
#define LOGF(x, ...);
#endif

#endif

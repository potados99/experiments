#ifndef _VERBOSE_H
#define _VERBOSE_H

#include <stdio.h>
#include <stdarg.h>

#if (VERBOSE > 1)
#define print_trace(_fmt, ...) \
	fprintf(stdout, _fmt, __VA_ARGS__)
#else
#define print_trace(_fmt, ...) NULL
#endif

#if (VERBOSE > 0)
#define print_info(_fmt, ...) \
	fprintf(stdout, _fmt, __VA_ARGS__)
#else
#define print_info(_fmt, ...) NULL
#endif

#define print_error(_fmt, ...) \
	fprintf(stderr, _fmt, __VA_ARGS__)

#endif /* _VERBOSE_H */

#ifndef _VERBOSE_H
#define _VERBOSE_H

static inline void verbose_out(FILE *stream, const char *fmt, ...) {
#if (VERBOSE > 0)
	va_list arg_ptr;

	va_start(arg_ptr, fmt);
	vfprintf(stream, fmt, vlist);
	va_end(arg_ptr);
#endif
}

#endif /* _VERBOSE_H */

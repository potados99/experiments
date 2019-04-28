#ifndef _MACROS_H
#define _MACROS_H

#define ASSERTDO(X, WHAT)			\
	do {					\
		if (!(X)) {			\
			WHAT;			\
		}				\
	} while(0)				

#define ASSERT(X) ASSERTDO(X, return)

#endif /* _MACROS_H */

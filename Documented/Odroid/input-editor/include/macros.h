#ifndef _MACROS_H
#define _MACROS_H


/**
  * Bitwise operation helper.
  */
#define ADD(X, Y) 				                \
	((X) | (Y))

#define SUB(X, Y)				                \
	((X) & ~(Y))

#define HAS(X, Y)				                \
	((X) & (Y))

#define HIGH_NIBBLE(b)                          \
	(((b) >> 4) & 0x0F)

#define LOW_NIBBLE(b)                           \
	((b) & 0x0F)

#define BIT_AT(I)				                \
	(0x01 << (I))


/**
  * Assertion for debug.
  */
#define ASSERTDO(X, WHAT)		                \
	do {					                    \
		if (!(X)) {			                    \
			WHAT;			                    \
		}				                        \
	} while(0)				

#define ASSERT(X) ASSERTDO(X, return)


#endif /* _MACROS_H */

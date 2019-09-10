#ifndef _arithmetic
#define _arithmetic

#include <stdbool.h>

/**
 * Check overflow
 *
 * @returan whether it is okay to invoke the operation or not.
 */
bool tadd_ok(int x, int y);
bool tsub_ok(int x, int y);
bool tmult_ok(int x, int y);

/**
 * Divide given number x by 16.
 * The absolute value of the result sticks to its floor.
 * e.g: 31 / 16 = 1, -31 / 16 = -1 (which is originally -2.)
 *
 * @return the result
 */
int div16(int x);

/**
 * Convert given signed number to unsigned representation.
 */
unsigned long unsigned32(int n);

#endif /* _arithmetic */

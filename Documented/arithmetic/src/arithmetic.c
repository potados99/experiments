#include "arithmetic.h"

/**
 * Lecture Note, Sep 10
 *
 * Multiplification of non 2-squared operand with shift operation:
 *	(u << 5) - (u << 3) = u*(2^5) - u*(2^3) = u*(2^5 - 2^3) = u * 24
 *
 * Ceiling of multification result:
 * 	Ceiling(x/y) = Floor((x + y - 1) / y)
 *
 * Sign conversion validation:
 * 	It is false that "if x <= 0 then -x >= 0"
 * 	Overflow occurs if x is T_MIN(-2147483647).
 * 	The problem is that in 2's complement representation
 * 	Range of positive numbers != that of negative one.
 *
 */

/**
 * Get MSB of given integer x.
 */
#define MSB(x) \
	(x & (1 << ((sizeof(typeof(x)) << 3) - 1)) /* 0x1...0000 */)

/**
 * Check if overflow/underflow occurs after adding y to x.
 *
 * If the x and the y has different sign, it will never happen
 * because the absolute value of the result will get smaller.
 *
 * If two have the same sign, we can determine if the overflow happened by
 * checking the result:
 * After the operation, if the result has an oppsite sign to the opperand,
 * it is the case the overflow took its place.
 */
bool tadd_ok(int x, int y) {
	return (MSB(x) != MSB(y) || MSB(x + y) == MSB(x));
}	

bool tsub_ok(int x, int y) {
	// TODO
	return true;
}

bool tmult_ok(int x, int y) {
	// TODO
	return true;
}

/**
 *
 *
 *
 *
 */
bool div16(int x) {

	int int_size = sizeof(int) << 3;
	int bias = ((x >> int_size)  )

}

/**
 * Interpret given number as unsigned form.
 * It prevents implicit upcasting with sign bit.
 *
 * @return the given number, in unsigned form.
 */
unsigned long unsigned32(int n) {
	return n & 0xFFFFFFFFL; /* (unsigned long)-1 */
}


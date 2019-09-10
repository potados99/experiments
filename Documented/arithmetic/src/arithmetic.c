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

/**
 * We can use the tadd_ok logic but under condition that y and -y is not same.
 * There is one case the condition not met: T_MIN, in binary 0x1000..0000
 */
bool tsub_ok(int x, int y) {
	
	return (y != (1 << 31) && tadd_ok(x, -y));
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
int div16(int x) {
	int int_width = sizeof(int) << 3;
	
	int bias = (x >> (int_width - 1)) & 0xF; /* Fill all bits with MSB. 16bit limit. */

	return (x + bias) >> (1 << 4);
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


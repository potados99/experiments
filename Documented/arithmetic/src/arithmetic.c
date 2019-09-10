#include "arithmetic.h"

bool tadd_ok(int x, int y) {
	// TODO
	return true;
}	

bool tmult_ok(int x, int y) {
	// TODO
	return true;
}

bool tsub_ok(int x, int y) {
	// TODO
	return true;
}

bool div16(int x) {

	int int_size = sizeof(int) << 3;
	int bias = ((x >> int_size)  )

}

/**
  * Note
  *
  * Multiplification of non 2-squared operand with shift operation  
  * (u << 5) - (u << 3) = u*(2^5) - u*(2^3) = u*(2^5 - 2^3) = u * 24
  *
  * Ceiling of multification result
  * Ceiling(x/y) = Floor((x + y - 1) / y)
  *
  * Sign conversion validation
  * It is false that "if x <= 0 then -x >= 0"
  * Overflow occurs if x is T_MIN(-2147483647).
  * The problem is that in 2's complement representation
  * Range of positive numbers != that of negative one.
  *
  */

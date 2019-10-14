#include "test.h"

#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>


int leftBitCount(int x) { //check 16 - 8 - 4 - 2
    int temp = x;
	int result;	
	int shift;
	int one = !(~x); 
	// Check the top 16 bits and add them to our result if they exist
	result = !(~(temp>>16)) << 4; //if there are no ones in the front, we just shift temp by a huge number, so temp is zero. 
	temp = temp << result;
	// check the remaining 8 bits (32-24)
	shift = !(~(temp >> 24)) << 3;
	temp = temp << shift;
	result = result | shift;
	// remaining 4 bits
	shift = !(~(temp>>28)) << 2;
	temp = temp << shift;
	result = result | shift;
	// remaining 2 bits
	shift = !(~(temp >> 30)) << 1;
	temp = temp << shift;
	result = result | shift;
	// remaining 1 bits
	result= result ^ (1&((temp>>31)));

	//rememer to add one if we have 32 on bits
	return result + one;
}


TEST(compile_test) { 
	// Define your tests...
	ASSERT(leftBitCount(0xF0000000) == 4);
	return true;
}

/**
 * Apply changes here after modifying tests.
 */
size_t testc = 1;

test_function testv[] = {
	compile_test
};

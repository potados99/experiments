#include "test.h"

#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

TEST(shift_test) { 
	// Define your tests...
	printf("1 << 35 = %x, 1 << 3 = %x.\n", 1 << 35, 1 << 3);
	ASSERT(1 << 35 == 1 << 3);
	return true;
}

/**
 * Apply changes here after modifying tests.
 */
size_t testc = 1;

test_function testv[] = {
	shift_test
};

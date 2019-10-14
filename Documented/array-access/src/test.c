#include "test.h"

#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

TEST(array_access_test) { 
	int arr[5] = { 32, 12, 35, 53, 11 };
	ASSERT(0[arr] == 32);
	
	return true;
}

/**
 * Apply changes here after modifying tests.
 */
size_t testc = 1;

test_function testv[] = {
	array_access_test
};

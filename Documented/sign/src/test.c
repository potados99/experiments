#include "test.h"

#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

TEST(sign_test) { 
	ASSERT(-1 < 0U == 0);
	return true;
}

/**
 * Apply changes here after modifying tests.
 */
size_t testc = 1;

test_function testv[] = {
	sign_test
};

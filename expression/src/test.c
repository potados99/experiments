#include "test.h"

#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

struct st {
	int red;
};

#define sym(name)	instance.name=2

TEST(compile_test) { 
	// Define your tests...

	int a = 3;

	ASSERT((a+=2) == 5);

	struct st instance = {0,};

	sym(red);

	ASSERT(instance.red == 2);

	return true;
}

/**
 * Apply changes here after modifying tests.
 */
size_t testc = 1;

test_function testv[] = {
	compile_test
};

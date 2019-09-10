#include "tests.h"
#include "arithmetic.h"

#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>


/***********************************
 * Test Declarations & Definitions
 ***********************************/

TEST(add_test) { 
	ASSERT(tadd_ok(2147483647, 3) == false);
	ASSERT(tadd_ok(-2147483468, - 1223727) == false);
	return true;		
}

TEST(sub_test) {
	ASSERT(tsub_ok(12, 3) == true);
	ASSERT(tsub_ok(-12345678, -2147483648) == false);
	return true;		
}

TEST(mult_test) {
	ASSERT(tmult_ok(23, 4) == true);
	return true;
}


/***********************************
 * Test Runner & Configurations.
 ***********************************/

size_t			testc = 3;

test_function	testv[] = {
	add_test,
	sub_test,
	mult_test
};

void run_tests() {
	for (size_t i = 0; i < testc; ++i) {
		printf("==== Test %zu Started ====\n", i);
		printf("==== Test %zu %s ====\n\n", i, testv[i]() ? "Succeeded" : "Failed");
	}
}

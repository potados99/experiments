#include "test.h"

#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

TEST(compile_test) { 
	// Define your tests...
	ASSERT(1 == 1);
	return true;
}

TEST(for_test) {
	int k = 0;
	int N = 100;
	for (int i = 0; i < 10; ++i, ++k, N <<= 1) {
		printf("YEAH!!\n");
	}

	printf("k after 10 loops: %d.\n", k);
	printf("N after 10 loops: %d.\n", N);

	return true;
}

/**
 * Apply changes here after modifying tests.
 */
size_t testc = 2;

test_function testv[] = {
	compile_test,
	for_test
};

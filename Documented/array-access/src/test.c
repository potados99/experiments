#include "test.h"

#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

TEST(array_access_test) { 
	int arr[5] = { 32, 12, 35, 53, 11 };
	ASSERT(0[arr] == 32);
	ASSERT(1[arr] == 12);

	return true;
}

TEST(nested_array_test) {
#define R 24
#define S 35
#define T 12
#define ADDR3D(X, Y, Z) (X*S*T + Y*T + Z)

	long A[R][S][T];
	ASSERT(&A[1][2][3] == ((long *)A + ADDR3D(1, 2, 3)));
	
	return true;
}

/**
 * Apply changes here after modifying tests.
 */
size_t testc = 2;

test_function testv[] = {
	array_access_test,
	nested_array_test
};

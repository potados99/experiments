#include "test.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

#include <errno.h>

TEST(compile_test) { 
	// Define your tests...
	ASSERT(1 == 1);
	return true;
}


static inline int to_int(const char *string) {
	/**
	int **string = int (*string);



	return **string;
	*/

	errno = 0;

	char *endptr = NULL;
	int parsed = (int)strtol(string, &endptr, 16);

	printf("Given: %s\n", string);

	if (errno != 0) {
		printf("ERROR!!!\n");
//		exit(1);
	}

	if (*string == '\0') {
		printf("String starts with null char! fuck! \n");
//		exit(2);
	}

	if (*endptr != '\0') {
		printf("Contains invalid character!!\n");
//		exit(3);
	}

	return parsed;
}

TEST(strtol_test) {
	const char *num_str = "0x7e";
	int expected = 0x7e;

	int actual = to_int(num_str);

	ASSERT(actual == expected);



	to_int("zdiulsfnbjlsehjbfsehjbfbhjsefhjbs");
	to_int(" vabc123");
	to_int("");
	to_int("\0");
	to_int("         1335 4");
	to_int("123a bc");
	






	return true;
}

/**
 * Apply changes here after modifying tests.
 */
size_t testc = 2;

test_function testv[] = {
	compile_test,
	strtol_test
};

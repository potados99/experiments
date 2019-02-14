#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "test.h"

int main(int argc, const char * argv[]) {
	printf("Hash distribution test.\n");

	if (argc > 1) {
		while(1) rand_test_1();
	}
	else {
		while(1) rand_test_2();
	}


	return 0;
}

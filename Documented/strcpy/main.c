#include <stdio.h>
#include <stdlib.h>

#include "pstring.h"

int main(int argc, char * argv[]) {
	int size = 6;
	char * dynm_arr = (char *)malloc(sizeof(char) * size);

	pstrcpy(dynm_arr, "hello");

	printf("string: %s\n", dynm_arr);

	return 0;
}

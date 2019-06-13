#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdarg.h>


int count(int n, ...);

int main(int argc, const char * argv[]) {
	// insert code here...
	printf("Hello, world! size of int is %lu.\n", sizeof(int));
	
	printf("sum of 1, 2, 3, 4 is %d.\n", count(4, 1, 2, 3, 4));

	return 0;
}

int count(int n, ...) {

	va_list vlist;
	va_start(vlist, n);

	int total = 0;
	for (int i = 0; i < n; ++i) {
		total += va_arg(vlist, int);
	}

	va_end(vlist);

	return total;
}


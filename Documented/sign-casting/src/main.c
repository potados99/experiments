#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned long unsigned32(int n);

int main(int argc, const char * argv[]) {	
	
	printf("2147483648 to unsigned int: %ld.\n", unsigned32(2147483648));

	return 0;
}

/**
  * Interpret given number as unsigned form.
  * It prevents implicit upcasting with sign bit.
  * @return the given number, in unsigned form.
  */
unsigned long unsigned32(int n) {
	return n & 0xFFFFFFFFL; /* (unsigned long)-1 */
}


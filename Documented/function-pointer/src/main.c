#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void the_function(int a) {
	printf("%s\n", "the function is called");

}

int main(int argc, const char * argv[]) {
	// insert code here...
	printf("Hello, world!\n");
	
	void (*fp)(int) = the_function;

	fp(10);

	return 0;
}



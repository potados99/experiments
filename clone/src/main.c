#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int magic_param_func(void *arg) {

	printf("the arg is: %s\n", (char *)arg);


	return 0;
}

int main(int argc, const char * argv[]) {
	// insert code here...
	printf("Hello, world!\n");
	

	char *num = "yeah hello";
	printf("Im gonna pass this number : %s\n", num);

	magic_param_func(num);


	return 0;
}

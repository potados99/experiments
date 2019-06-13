#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct st {
	int one;
	int two;
};


int main(int argc, const char * argv[]) {
	int *nums;

	struct st s;
	s.one = 5;
	s.two = 9;

	nums = (int *)&s;
	
	printf("nums[0]: %d, nums[1]: %d.\n", nums[0], nums[1]);
	
	// insert code here...
	printf("Hello, world!\n");
	
	return 0;
}

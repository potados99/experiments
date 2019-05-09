#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rect.h"

int main(int argc, const char * argv[]) {
	// insert code here...
	printf("Hello, world!\n");
	
	struct rect myrect = { {30, 10}, {39, 20} };

	print_rect(&myrect);

	return 0;
}

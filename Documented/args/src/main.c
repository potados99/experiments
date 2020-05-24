#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char * argv[]) {
	
	printf("argc: %d, argv: ", argc);
	for (int i = 0; i < argc; ++i) {
		printf("%s, ", argv[i]);
	}
	printf("\n");

	return 0;
}

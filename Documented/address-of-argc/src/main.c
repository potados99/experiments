#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char * argv[]) {
        int a = 0;

        long a_addr = (long)&a;
        long argc_addr = (long)&argc;

        printf("Address of argc: %lx\n", argc_addr);
	printf("Address of first stack variable: %lx\n", a_addr);
	printf("Diff of them: %ld\n", argc_addr - a_addr);

	return 0;
}

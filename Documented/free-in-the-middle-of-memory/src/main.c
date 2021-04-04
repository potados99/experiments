#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MEM_SIZE 50

int main(int argc, const char * argv[]) {
	char *memory_start = (char *)malloc(MEM_SIZE);
        if (!memory_start) {
            printf("Ooh shit!\n");
            return -1;
        }

        char *memory_5_after_start = memory_start + 5;
        
        free(memory_5_after_start);

	return 0;
}

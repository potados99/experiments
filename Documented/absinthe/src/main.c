#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int 	get_age();

int main(int argc, const char * argv[]) {
	printf("생쟝 사랑해요!\n");
        printf("생쟝의 나이는 %d쨜!\n", get_age());

	puts("음쟝 바보!!");
	return 0;
}

int get_age() {
        return 22;
}

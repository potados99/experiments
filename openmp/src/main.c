#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <omp.h>

int main(int argc, const char * argv[]) {
	// insert code here...
	printf("Hello, world!\n");
	
	#pragma omp parallel 
	{
		printf("I'm in a omp region\n");
	}


	#pragma omp parallel for
	for (int i = 0; i < 10; ++i) {
		printf("hey I'm %d, by thread %d.\n", i, omp_get_thread_num());
	}



	return 0;
}

#include "fork.h"

int main(int argc, const char *argv[]) {
	printf("Hello, world!\n");

	printf("\tFork test start.\n");
	fork_test();
	printf("\tFork test done.\n\n");

	printf("\tFork increase test start.\n");
	fork_increase_test();
	printf("\tFork increase test done.\n");

	return 0;
}

#!/usr/bin/c

#include <stdio.h>


int foo(int a, int b) {
	char ar[10] = "hello";
	printf("%s\n", ar);

	return a + b;
}

int main(int argc, int *argv[]) {
	int c = foo(2, 3);

	return 0;
}

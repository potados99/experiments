#include <stdio.h>

int print_test(int a, int b) {
	int chars = printf("%d %d %d %d\n", a, b, 999, 9999);

	return chars;
}

int input_test(int *a, int *b, int *c, int *d, int *e, int *f, int *g) {
	int items = sscanf(stdin, "%d %d %d %d %d %d %d", a, b, c, d, e, f, g);
	return items;
}

int main(int argc, const char * argv[]) {
	int _a = 3;
	int _b = 5;

	print_test(_a, _b);
	
	int i1, i2, i3, i4, i5, i6, i7;
	input_test(i1, i2, i3, i4, i5, i6, i7);

	return 0;
}

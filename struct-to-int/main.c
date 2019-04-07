#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct mystruct {
	int num;
	char character;
};

int main(int argc, const char * argv[]) {
	printf("Hello, world!\n");


	struct mystruct s;
	s.num = 2;
	s.character = 'a';

	int serialized = (int)s;

	struct mystruct unpacked = (struct mystruct)serialized;

	printf("after that: %d and %c\n". unpacked.num, unpacked.character);

	return 0;
}

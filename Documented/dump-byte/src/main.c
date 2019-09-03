#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void dump_byte(char *addr, int len);

int main(int argc, const char * argv[]) {
	int val = 0x12345678;

	printf("%x is stored in memory as form of:\n", val);

	dump_byte(&val, sizeof(int));

	return 0;
}

void dump_byte(char *addr, int len) {
	for (int i = 0; i < len; ++i) {
		printf("%02x ", *(addr + i));
	}
	printf("\n");
}

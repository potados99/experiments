#include "fnd.h"

#include <stdio.h>

/*
 
val  binary	 	hex
 0 	0011 1111	0x3F
 1	0000 0110	0x06
 2	0101 1011	0x5B
 3  0100 1111	0x4F
 4  0110 0110	0x66
 5	0110 1101	0x6D
 6	0111 1101	0x7D
 7	0000 0111	0x07
 8	0111 1111	0x7F
 9	0110 1111	0x6F
 A	0111 0111	0x77
 B	0111 1100	0x7C
 C	0111 1001	0x79
 D	0101 1110	0x5E
 E	0111 1011	0x7B
 F	0111 0001	0x71
 
 */

int digit_map[] = {
	0x3F,
	0x06,
	0x5B,
	0x4F,
	0x66,
	0x6D,
	0x7D,
	0x07,
	0x7F,
	0x6F,
	0x77,
	0x7C,
	0x79,
	0x5E,
	0x7B,
	0x71
};

void print_hex(int val) {
	if (val > 15 || val < 0) return;

	print_digits(digit_map[val]);
}

void print_digits(int digits) {
	if (digits > 0x7F || digits < 0) return;

	int pos = 0;

	while (digits) {
		if (digits & 0x01) {
			printf("Turn on digit %d\n", pos);
		}
		else {
			printf("Turn off digit %d\n", pos);
		}

		fflush(stdout);		
		
		pos += 1;
		digits >>= 1;
	}
}

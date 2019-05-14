#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "conv.h"
#include "fnd.h"

int main(int argc, const char * argv[]) {
	int mode;
	int arg; /* optional */

	if (argc < 2) {
		puts("Too less arguments.\n");
		goto Usage;
	}
	else if (to_int(argv[1], 10, &mode) != 0) {
		puts("Invalid chacter for mode.\n");
		goto Usage;
	}
	else if (mode != 1 && mode != 2) {
		puts("Invalid mode.\n");
		goto Usage;
	}
	else if (mode == 2 && argc < 3) {
		puts("Argument for mode 2 is not given.\n");
		goto Usage;
	}
	else if (mode == 2 && to_int(argv[2], 16, &arg) != 0) {
		puts("Invalid character for mode option.\n");
		goto Usage;
	}

	fnd_init_gpio();

	switch (mode) {
		case 1:
			fnd_print_range(0x00, 0x0F, 500);
			break;
		case 2:
			fnd_control_segments(arg);
			break;
		default:
			/* NOREACH */
			break;
	}

	return 0;
  
Usage:
	puts("Usage: App mode [argument].");
	puts("	Modes:");
	puts("		1: print from 0 to F.");
	puts("		2: turn on only specified digits.");
	puts("	Argument:");
	puts("		Sum of bits refering to the segment digits, hex rep'. (mode 2 optional)");

	return 1;
}

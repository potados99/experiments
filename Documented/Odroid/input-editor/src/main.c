#include <stdio.h>

#include "routines.h"
#include "keypad.h"
#include "pgpio.h"
#include "verbose.h"

struct keypad *mykeypad;

int main(int argc, const char * argv[]) {
	setup();

	while (1) {
		loop();
	}
	
	return 0;
}

void setup() {
	print_info("start\n");
}

void loop() {
	print_info("loop!\n");
	udelay(100000);
}

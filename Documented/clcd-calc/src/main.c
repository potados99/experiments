#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "clcd.h"
#include "keypad.h"

int main(int argc, char *const argv[]) {
	lcd_init();
	
	for (int i = 1; i < argc; ++i) {
		lcd_put_line(argv[i]);
	}
	
	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "clcd.h"
#include "keypad.h"
#include "machine_specific.h"

void onKey(enum KEY key) {
	printf("selected one: %d.\n", key);
}

int main(int argc, char *const argv[]) {
/*
	lcd_init();
	
	for (int i = 1; i < argc; ++i) {
		lcd_put_line(argv[i]);
	}
*/	

	int rows[] = { KEYPAD_0, KEYPAD_1, KEYPAD_2, KEYPAD_3 }; /* machine_specific */
	int cols[] = { KEYPAD_4, KEYPAD_5, KEYPAD_6, KEYPAD_7 };
	
	struct keypad mykeypad;

	keypad_setup(&mykeypad, rows, 4, cols, 4);
	keypad_set_listener(&mykeypad, onKey);
	

	while(1) {
		keypad_loop(&mykeypad);
	}

	
	return 0;
}

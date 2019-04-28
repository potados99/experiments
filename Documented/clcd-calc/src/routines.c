#include "routines.h"

#include "clcd.h"
#include "keypad.h"
#include "machine_specific.h"

struct keypad mykeypad;	
struct clcd myclcd;

/* callback */
void onKey(enum KEY key) {
	printf("selected one: %d.\n", key);
	clcd_put_char(&myclcd, key + '0');
}

void setup() {
	int rows[] = { KEYPAD_0, KEYPAD_1, KEYPAD_2, KEYPAD_3 }; /* machine_specific */
	int cols[] = { KEYPAD_4, KEYPAD_5, KEYPAD_6, KEYPAD_7 };
	
	int data_pins[] = { CLCD_D4, CLCD_D5, CLCD_D6, CLCD_D7 };
	int reg_pin = CLCD_RS;
	int en_pin = CLCD_EN;

	keypad_setup(&mykeypad, rows, 4, cols, 4);
	keypad_set_listener(&mykeypad, onKey);
	
	clcd_setup(&myclcd, data_pins, reg_pin, en_pin);
	clcd_init(&myclcd);
}

void loop() {
	keypad_loop(&mykeypad);
}

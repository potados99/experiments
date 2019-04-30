#include "routines.h"

#include "keypad.h"
#include "clcd.h"
#include "calc.h"
#include "machine_specific.h"

#include <stdlib.h>

/**
  * Keypad, clcd, calc.
  * Pointers to instances.
  *
  * They will be allocated in heap, when setup() is done.
  */
struct keypad 	*mykeypad;	
struct clcd 	*myclcd;
struct calc 	*mycalc;

/**
  * Keypad callback.
  */
void on_key_pressed(int key_index);

/**
  * Calc callback.
  */
void on_calc_append(int content);
void on_calc_shift(int content);
void on_calc_clear(int content);

/**
  * ENTRY.
  */
int main(int argc, char *const argv[]) {
	setup();

	while (1) {
		loop();
	}
	
	/* NOREACH */
	return 0;
}

/**
  * Run once.
  */
void setup() {
	/* temporary things */
	int rows[] = { KEYPAD_0, KEYPAD_1, KEYPAD_2, KEYPAD_3 }; /* machine_specific */
	int cols[] = { KEYPAD_4, KEYPAD_5, KEYPAD_6, KEYPAD_7 };
	
	int data_pins[] = { CLCD_D4, CLCD_D5, CLCD_D6, CLCD_D7 };
	int reg_pin = CLCD_RS;
	int en_pin = CLCD_EN;

	/* infinite things */
	mykeypad = (struct keypad *)malloc(sizeof(struct keypad) + 1);
	mycalc = (struct calc *)malloc(sizeof(struct calc) + 1);
	myclcd = (struct clcd *)malloc(sizeof(struct clcd) + 1);

	keypad_setup(mykeypad, rows, 4, cols, 4);
	keypad_set_listener(mykeypad, on_key_pressed);
	
	clcd_setup(myclcd, data_pins, reg_pin, en_pin);
	clcd_ready(myclcd);

	calc_setup(mycalc);
	calc_attach_callback(mycalc, on_calc_append, on_calc_shift, on_calc_clear);

	/* additional. */
	calc_clear(mycalc, '0');
}

/**
  * Run forever.
  */
void loop() {
	keypad_loop(mykeypad);
}


/**
  * When a key is pressed.
  */
void on_key_pressed(int key_index) {
	enum KEY key = (enum KEY)key_index;
	
	calc_key_input(mycalc, key);
}

/**
  * When calc has to add a character to display.
  */
void on_calc_append(int content) {
	if (content == '\n') {
		clcd_set_cursor(myclcd, 16);
	} else {
		clcd_put_char(myclcd, (char)content);
	}
}

/**
  * When calc has to shift cursor of display.
  */
void on_calc_shift(int content) {
	clcd_move_cursor(myclcd, content);
}

/**
  * When calc has to clear display.
  */
void on_calc_clear(int content) {
	clcd_clear(myclcd);
	if (content) {
		if (content == '\n') {
			clcd_set_cursor(myclcd, 16);
		} else {
			clcd_put_char(myclcd, (char)content);
		}
	}	
}


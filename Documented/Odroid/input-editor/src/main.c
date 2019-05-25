#include <stdio.h>
#include <stdlib.h>

#include "routines.h"
#include "keypad.h"
#include "vclcd.h"
#include "pgpio.h"
#include "verbose.h"
#include "machine_specific.h"

struct keypad *mykeypad;
struct vclcd *myvclcd;

void on_key_pressed(int key_index);

int main(int argc, const char * argv[]) {
	setup();

	while (1) {
		loop();
	}
	
	return 0;
}

void setup() {
	print_info("start\n");
	
	int rows[] = { KEYPAD_0, KEYPAD_1, KEYPAD_2, KEYPAD_3 }; /* machine_specific */
	int cols[] = { KEYPAD_4, KEYPAD_5, KEYPAD_6, KEYPAD_7 };
	
	mykeypad = (struct keypad *)malloc(sizeof(struct keypad) + 1);
    myvclcd = (struct vclcd *)malloc(sizeof(struct vclcd) + 1);
    
	keypad_setup(mykeypad, rows, 4, cols, 4);
	keypad_set_listener(mykeypad, on_key_pressed);
    
    vclcd_setup(myvclcd, "/dev/fb2");
    vclcd_clear(myvclcd, 0xFFFF);
    vclcd_write(myvclcd, 'a');
}

void loop() {
//	print_info("loop!\n");
//	keypad_loop(mykeypad);
	udelay(100000);
}

void on_key_pressed(int key_index) {
	print_info("[key at index %d pressed.]\n", key_index);
}

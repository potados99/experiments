#include <stdio.h>
#include <stdlib.h>

#include "keypad.h"
#include "vclcd.h"
#include "editor.h"

#include "routines.h"
#include "pgpio.h"
#include "verbose.h"
#include "machine_specific.h"

struct keypad *mykeypad;
struct vclcd *myvclcd;
struct editor *myeditor;

/**
 * Callbacks
 */
void on_key_pressed(int key_index);
void notify_cursor_move(int delta);
void notify_insert(int c);
void notify_delete(int _);
void notify_replace(int c);
int  ask_is_full(int _);

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
    myeditor = (struct editor *)malloc(sizeof(struct editor) + 1);
    
	keypad_setup(mykeypad, rows, 4, cols, 4);
	keypad_set_listener(mykeypad, on_key_pressed);
    
    vclcd_setup(myvclcd, FDFILE_PATH);
 
    editor_setup(myeditor);
    
    struct editor_callbacks callbacks = {
      notify_cursor_move, notify_insert, notify_delete, notify_replace, ask_is_full
    };
    
    editor_add_callbacks(myeditor, callbacks);
}

void loop() {
	keypad_loop(mykeypad);
}


void on_key_pressed(int key_index) {
	print_info("[key at index %d pressed.]\n", key_index);
    editor_input(myeditor, key_index);
}

void notify_cursor_move(int delta) {
    print_info("[cursor move %s.]\n", delta > 0 ? "right" : "left");
    vclcd_seek(myvclcd, delta, SEEK_CUR);
}
void notify_insert(int c) {
    print_info("[insert %c.]\n", c);
    vclcd_insert(myvclcd, c);
}
void notify_delete(int _) {
    print_info("[delete character.]\n");
    vclcd_delete(myvclcd);
}
void notify_replace(int c) {
    print_info("[replace with %c.]\n", c);
    vclcd_replace(myvclcd, c);
}

int ask_is_full(int _) {
    return 1//vclcd_is_full(myvclcd);
}

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
    
    /**
     * Test code
     */
    vclcd_setup(myvclcd, "/dev/fb2");
    fgetc(stdin);
    
    /*
    _vclcd_draw_char(myvclcd, myvclcd->curs_pos, 'a', PIXEL_BLACK);
    myvclcd->chars_len++;
    myvclcd->chars[myvclcd->curs_pos] = 'a';
    vclcd_seek(myvclcd, 1, SEEK_CUR);
    vclcd_dump(myvclcd);
    fgetc(stdin);

    _vclcd_draw_char(myvclcd, myvclcd->curs_pos, 'b', PIXEL_BLACK);
    myvclcd->chars_len++;
    myvclcd->chars[myvclcd->curs_pos] = 'b';
    vclcd_seek(myvclcd, 1, SEEK_CUR);
    vclcd_dump(myvclcd);
    fgetc(stdin);

    _vclcd_draw_char(myvclcd, myvclcd->curs_pos, 'c', PIXEL_BLACK);
    myvclcd->chars_len++;
    myvclcd->chars[myvclcd->curs_pos] = 'c';
    vclcd_seek(myvclcd, 1, SEEK_CUR);
    vclcd_dump(myvclcd);
    fgetc(stdin);

    _vclcd_draw_char(myvclcd, myvclcd->curs_pos, 'd', PIXEL_BLACK);
    myvclcd->chars_len++;
    myvclcd->chars[myvclcd->curs_pos] = 'd';
    vclcd_seek(myvclcd, 1, SEEK_CUR);
    vclcd_dump(myvclcd);
    fgetc(stdin);


//    _vclcd_shift(myvclcd, 1, 3, -1);
//    _vclcd_shift(myvclcd, 2, 1, -1);
//    _vclcd_shift(myvclcd, 1, 2, 1);
    _vclcd_shift(myvclcd, 1, 3, 25);
    vclcd_dump(myvclcd);
    */
    
    fgetc(stdin);

    vclcd_insert(myvclcd, 'a');
    vclcd_seek(myvclcd, 1, SEEK_CUR);
    
    fgetc(stdin);
    
    vclcd_insert(myvclcd, 'b');
    vclcd_seek(myvclcd, 1, SEEK_CUR);
    
    fgetc(stdin);
    
    vclcd_insert(myvclcd, 'c');
    
    fgetc(stdin);
    
    vclcd_insert(myvclcd, 'd');
    
    fgetc(stdin);
    
    vclcd_insert(myvclcd, 'e');
    vclcd_seek(myvclcd, 1, SEEK_CUR);
    
    fgetc(stdin);
    
    vclcd_insert(myvclcd, 'f');
    vclcd_seek(myvclcd, 1, SEEK_CUR);
    
    fgetc(stdin);
    
    

    /**
     * Test code done
     */
    
    
}

void loop() {
//	print_info("loop!\n");
//	keypad_loop(mykeypad);
	udelay(100000);
}

void on_key_pressed(int key_index) {
	print_info("[key at index %d pressed.]\n", key_index);
}

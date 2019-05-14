#include "clcd.h"
#include "pgpio.h"
#include "machine_specific.h"

#include <string.h>
#include <stdio.h>

void clcd_setup(struct clcd* clcd, int data_pins[], int reg_pin, int en_pin) {
	ASSERTDO((clcd != NULL), print_error("clcd_setup: clcd is null.\n"); return);
	ASSERTDO((data_pins != NULL), print_error("clcd_setup: data_pins is null.\n"); return);
	ASSERTDO((reg_pin >= 0), print_error("clcd_setup: reg_pin cannot be under zero.\n"); return);
	ASSERTDO((en_pin >= 0), print_error("clcd_setup: en_pin cannot be under zero.\n"); return);
	for (int i = 0; i < CLCD_DATA_PINS; ++i) {
		ASSERTDO((data_pins[i] >= 0), print_error("clcd_setup: data_pins[%d] cannot be under zero.\n", i); return);
	}

	/**
	  * initialize.
	  */
	clcd->initialized = false;
	clcd->cur_pos = 0;
	memset(clcd->data_pins, 0, sizeof(int) * CLCD_DATA_PINS);
	clcd->reg_pin = 0;
	clcd->en_pin = 0;

	/**
	  * assign.
	  */
	for (int i = 0; i < CLCD_DATA_PINS; ++i) {
		clcd->data_pins[i] = data_pins[i];
	}

	clcd->reg_pin = reg_pin;
	clcd->en_pin = en_pin;
}

void clcd_ready(struct clcd* clcd) {
	ASSERTDO((clcd != NULL), print_error("clcd_init: clcd is null.\n"); return);
	
	/**
	  * basic gpio pin setup.
	  */
	gpio_setup();

	pinv_mode(clcd->data_pins, CLCD_DATA_PINS, PGPIO_OUTPUT);
	pin_mode(clcd->reg_pin, PGPIO_OUTPUT);
	pin_mode(clcd->en_pin, PGPIO_OUTPUT);

	digital_writev(clcd->data_pins, CLCD_DATA_PINS, PGPIO_LOW);
	digital_write(clcd->reg_pin, PGPIO_LOW);
	digital_write(clcd->en_pin, PGPIO_LOW);

	clcd->initialized = true;

	/**
	  * wait and apply commands.
	  */
	udelay(35000);

	for (int i = 0; i < 3; ++i) {
		clcd_put_cmd(clcd, C_FUNSET | C_FUNSET_N); /* function set with two line. */
		udelay(5000);
	}

	clcd_put_cmd(clcd, C_DISP | C_DISP_D); /* display on, cursor off, not blink */
	clcd_put_cmd(clcd, C_RET_HOME); /* return home */
	
	udelay(3000);

	clcd_put_cmd(clcd, C_CLR_DISP); /* clear display */
	
	udelay(3000);
}

void clcd_put_cmd(struct clcd *clcd, unsigned char cmd) {
	ASSERTDO((clcd != NULL), print_error("clcd_put_cmd: clcd is null.\n"); return);
	ASSERTDO((clcd->initialized), print_error("clcd_put_cmd: clcd is not initialized.\n"); return);

	_clcd_select_cmd(clcd->reg_pin);
	_clcd_write_byte(clcd, cmd);
}

void clcd_put_char(struct clcd *clcd, char c) {
	ASSERTDO((clcd != NULL), print_error("clcd_put_char: clcd is null.\n"); return);
	ASSERTDO((clcd->initialized), print_error("clcd_put_char: clcd is not initialized.\n"); return);
	ASSERTDO((clcd->cur_pos < CLCD_LINES * CLCD_CHARS), print_info("clcd_put_char: cannot write more.\n"); return);

	_clcd_select_data(clcd->reg_pin);
	_clcd_write_byte(clcd, c);

	print_info("wrote %c to clcd.\b\n", c);

	clcd->cur_pos += 1;
	
	if ((clcd->cur_pos % CLCD_CHARS) == 0) {
		/* at the end of the line. */
		print_info("it was the line end.\n");

		clcd_set_cursor(clcd, clcd->cur_pos);
	}

	print_info("cursor now at %d.\n", clcd->cur_pos);
}
void clcd_put_line(struct clcd *clcd, char *line) {
	ASSERTDO((clcd != NULL), print_error("clcd_put_line: clcd is null.\n"); return);
	ASSERTDO((clcd->initialized), print_error("clcd_put_line: clcd is not initialized.\n"); return);
	ASSERTDO((line != NULL), print_error("clcd_put_line: line is null.\n"); return);

	int len = strlen(line);
	
	for (register int i = 0; i < len; ++i) {
		clcd_put_char(clcd, line[i]);
	}

	if (clcd->cur_pos < CLCD_CHARS) {
		clcd_put_cmd(clcd, 0xC0); /* linebreak */
	}
}

void clcd_set_cursor(struct clcd *clcd, int pos) {
	ASSERTDO((clcd != NULL), print_error("clcd_set_cursor: clcd is null.\n"); return);
	ASSERTDO((clcd->initialized), print_error("clcd_set_cursor: clcd is not initialized.\n"); return);
	ASSERTDO((pos >= 0), print_error("clcd_set_cursor: pos cannot be under zero.\n"); return);
	ASSERTDO((pos < 32), print_error("clcd_set_cursor: pos cannot reach or exceed 32.\n"); return);

	int line = pos / CLCD_CHARS;
	int col = pos % CLCD_CHARS;

	int actual_address = line * 0x40 + col;

	print_info("going to set cursor to posision %d, of which address is %d.\n", pos, actual_address);

	clcd_put_cmd(clcd, C_DDRAM_ADD | actual_address);
	clcd_put_cmd(clcd, C_DDRAM_ADD | actual_address);
	
	clcd->cur_pos = pos;
}

void clcd_move_cursor(struct clcd *clcd, int delta) {
	ASSERTDO((clcd != NULL), print_error("clcd_set_cursor: clcd is null.\n"); return);
	ASSERTDO((clcd->initialized), print_error("clcd_set_cursor: clcd is not initialized.\n"); return);
	
	clcd_set_cursor(clcd, clcd->cur_pos + delta);
}

void clcd_clear(struct clcd* clcd) {
	ASSERTDO((clcd != NULL), print_error("clcd_set_cursor: clcd is null.\n"); return);
	ASSERTDO((clcd->initialized), print_error("clcd_set_cursor: clcd is not initialized.\n"); return);
	
	clcd_put_cmd(clcd, C_CLR_DISP);
	clcd->cur_pos = 0;
}

#include "clcd.h"
#include "pgpio.h"
#include "machine_specific.h"

#include <string.h>

void clcd_setup(struct clcd* clcd, int data_pins[], int reg_pin, int en_pin) {
	ASSERTDO((clcd != NULL), print_error("clcd_setup: clcd is null.\n"); return);
	ASSERTDO((data_pins != NULL), print_error("clcd_setup: data_pins is null.\n"); return);
	ASSERTDO((reg_pin > 0), print_error("clcd_setup: reg_pin cannot be under zero.\n"); return);
	ASSERTDO((en_pin > 0), print_error("clcd_setup: en_pin cannot be under zero.\n"); return);
	for (int i = 0; i < CLCD_DATA_PINS; ++i) {
		ASSERTDO((data_pins[i] > 0), print_error("clcd_setup: data_pins[%d] cannot be under zero.\n", i); return);
	}

	/**
	  * initialize.
	  */
	clcd->initialized = false;
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

	clcd->initialized = true;
}

void clcd_init(struct clcd* clcd) {
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


	/**
	  * wait and apply commands.
	  */
	udelay(35000);

	clcd_put_cmd(clcd, 0x28);
	clcd_put_cmd(clcd, 0x28);
	clcd_put_cmd(clcd, 0x28);

	clcd_put_cmd(clcd, 0x0e);
	clcd_put_cmd(clcd, 0x02);
	
	udelay(3000);

	clcd_put_cmd(clcd, 0x01);
	
	udelay(3000);
}

void clcd_put_cmd(struct clcd *clcd, unsigned char cmd) {
	_clcd_select_cmd(clcd->reg_pin);
	_clcd_write_byte(clcd, cmd);
}

void clcd_put_char(struct clcd *clcd, char c) {
	_clcd_select_data(clcd->reg_pin);
	_clcd_write_byte(clcd, c);
}

void clcd_put_line(struct clcd *clcd, char *line) {
	int len = strlen(line);
	
	for (register int i = 0; i < len; ++i) {
		if (line[i] == '\n') {
			clcd_put_cmd(clcd, 0xc0);
		} else {
			clcd_put_char(clcd, line[i]);
		}
	}

	clcd_put_cmd(clcd, 0xC0); /* linebreak */
}


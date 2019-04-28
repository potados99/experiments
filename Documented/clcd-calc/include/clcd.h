#ifndef _CLCD_H
#define _CLCD_H

#include <stdbool.h>

#include "pgpio.h"
#include "machine_specific.h"

#define CLCD_R_CMD	0 /* register selection for command mode. */
#define CLCD_R_DATA 	1 /* register selection for data mode. */

#define CLCD_DATA_PINS	4 /* number of data pins in this configuration. (hardwired) */

struct clcd {
	bool initialized;

	int data_pins[CLCD_DATA_PINS];
	int reg_pin; /* register selection */
	int en_pin; /* enable */
};

/**
 * Trigger action for current GPIO output.
 */
static inline void _clcd_apply(int en_pin) {
	digital_write(en_pin, PGPIO_HIGH);
	udelay(100);
	digital_write(en_pin, PGPIO_LOW);
	udelay(100);
}

/**
 * Select command register.
 */
static inline void _clcd_select_cmd(int reg_pin) {
	digital_write(reg_pin, LCD_R_CMD);
}

/**
  * Select data register.
  */
static inline void _clcd_select_data(int reg_pin) {
	digital_write(reg_pin, LCD_R_DATA);
}

/**
 * Write 4 bits to (D4..D7).
 */
static inline void _clcd_write_nibble(struct clcd* clcd, unsigned char nibble) {
	for (register int i = 0; i < 4; ++i) {
		digital_write(clcd->data_pins[i], nibble & 0x01);
		nibble >>= 1;
	}
	_clcd_apply(clcd->en_pin);
}

/**
 * Write one byte. 
 * Write to (D4..D7) twice, 4 bits at once.
 */
static inline void _clcd_write_byte(struct clcd* clcd, unsigned char byte) {
	_clcd_write_nibble((byte >> 4) & 0x0f); /* high 4 */
	_clcd_write_nibble(byte & 0x0f); /* low 4 */
}


/**
  * Initial setup.
  */
void clcd_setup(struct clcd* clcd, int data_pins[], int reg_pin, int en_pin);

/**
 * Get CLCD ready for use.
 */
void clcd_init(struct clcd* clcd);

/**
 * Send a command to the CLCD.
 */
void clcd_put_cmd(struct clcd* clcd, unsigned char cmd);

/**
 * Send a single ascii character to CLCD.
 */
void clcd_put_char(struct clcd* clcd, char c);

/**
 * Write a line. NULL-terminate.
 */
void clcd_put_line(struct clcd* clcd, char *line);

#endif /* _CLCD_H */

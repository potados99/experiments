#ifndef _CLCD_H
#define _CLCD_H

/**
  * Easy control HD44780.
  *
  * Usage:
  *	1) Declare and allocate a variable of type struct clcd.
  *	2) clcd_setup(): variable init and hardware setup.
  *	3) clcd_init(): get display ready for use.
  *
  * Notice:
  *	Set CLCD_DELAY for your own sake.
  *
  */

#include "pgpio.h"
#include "machine_specific.h"
#include "macros.h"

#include <stdbool.h>

#define CLCD_R_CMD	PGPIO_LOW 		/* register selection for command mode. */
#define CLCD_R_DATA 	PGPIO_HIGH		/* register selection for data mode. */

#define CLCD_DATA_PINS	4 		/* number of data pins in this configuration. (hardwired) */

#define CLCD_LINES	2
#define CLCD_CHARS	16

/**
  * Edit me if you want.
  */
#define CLCD_DELAY 500

/**
  * HD44780U commands
  */
/* Clear display */
#define C_CLR_DISP	BIT_AT(0) 	/* clear display and return home. */

/* Return home */
#define C_RET_HOME	BIT_AT(1) 	/* set DDRAM address to 0. */

/* Entry mode set */
#define C_ENTRY		BIT_AT(2) 	/* cursor and shift setting. */
#define C_ENTRY_INC	BIT_AT(1) 	/* cursor move right. */
#define C_ENTRY_DEC	!BIT_AT(1) 	/* cursor move left. */
#define C_ENTRY_S	BIT_AT(0) 	/* shift screen, not a cursor. */

/* Display on/off control */
#define C_DISP		BIT_AT(3) 	/* set display on/off, cursor on/off, cursor blink. */
#define C_DISP_D	BIT_AT(2) 	/* display on. */
#define C_DISP_C	BIT_AT(1) 	/* cursor on. */
#define C_DISP_B	BIT_AT(0) 	/* blink cursor. */

/* Cursor or display shift */
#define C_SHIFT		BIT_AT(4) 	/* shift cursor or display. */
#define C_SHIFT_S	BIT_AT(3) 	/* shift display. */
#define C_SHIFT_C	!BIT_AT(3)	/* shift cursor. */
#define C_SHIFT_R	BIT_AT(2)	/* shift to right. */
#define C_SHIFT_L	!BIT_AT(2)	/* shift to left.*/

/* Function set */
#define C_FUNSET 	BIT_AT(5) 	/* set function. */
#define C_FUNSET_DL	BIT_AT(4) 	/* data length. (8 on 1, 4 on 0) */
#define C_FUNSET_N	BIT_AT(3) 	/* number of lines. (2 on 1, 1 on 0) */
#define C_FUNSET_F	BIT_AT(2) 	/* large font. cannot be with C_FUNSET_N. */

/* Set DDRAM address */
#define C_DDRAM_ADD	BIT_AT(7)


struct clcd {
	bool initialized;

	int cur_pos;
	int data_pins[CLCD_DATA_PINS];
	int reg_pin; /* register selection */
	int en_pin; /* enable */
};

/**
 * Trigger action for current GPIO output.
 */
static inline void _clcd_apply(int en_pin) {
	digital_write(en_pin, PGPIO_HIGH);
	udelay(CLCD_DELAY);
	digital_write(en_pin, PGPIO_LOW);
	udelay(CLCD_DELAY);
}

/**
 * Select command register.
 */
static inline void _clcd_select_cmd(int reg_pin) {
	digital_write(reg_pin, CLCD_R_CMD);
	udelay(CLCD_DELAY);
}

/**
  * Select data register.
  */
static inline void _clcd_select_data(int reg_pin) {
	digital_write(reg_pin, CLCD_R_DATA);
	udelay(CLCD_DELAY);
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
	_clcd_write_nibble(clcd, HIGH_NIBBLE(byte)); /* high 4 */
	_clcd_write_nibble(clcd, LOW_NIBBLE(byte)); /* low 4 */
}


/**
  * Initial setup.
  */
void clcd_setup(struct clcd* clcd, int data_pins[], int reg_pin, int en_pin);

/**
 * Get CLCD ready for use.
 */
void clcd_ready(struct clcd* clcd);

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

/**
  * Set cursor position. (DDRAM address)
  */
void clcd_set_cursor(struct clcd *clcd, int pos);

/**
  * Move cursor position
  */
void clcd_move_cursor(struct clcd *clcd, int delta);

/**
  * Clear clcd.
  */
void clcd_clear(struct clcd *clcd);

#endif /* _CLCD_H */

#include "keypad.h"
#include "verbose.h"
#include "pgpio.h"
#include "machine_specific.h"

#include <string.h>

void keypad_setup(struct keypad *keypad, int rows[], int n_rows, int cols[], int n_cols) {
	ASSERTDO((keypad != NULL), verbose_out(stderr, "keypad_setup: keypad is null.\n"); return);
	ASSERTDO((rows != NULL), verbose_out(stderr, "keypad_setup: rows is null.\n"); return);
	ASSERTDO((cols != NULL), verbose_out(stderr, "keypad_setup: cols is null.\n"); return);	

	/* init */
	keypad->initialized = false;

	memset(keypad->rows, 0, sizeof(int) * MAX_ROWS);
	memset(keypad->cols, 0, sizeof(int) * MAX_COLS);
	
	keypad->n_rows = 0;
	keypad->n_cols = 0;
	
	keypad->callback = NULL;

	/* assign */
	keypad->n_rows = n_rows;
	for (int i = 0; i < keypad->n_rows; ++i) {
		keypad->rows[i] = rows[i];
	}

	keypad->n_cols = n_cols;
	for (int i = 0; i < keypad->n_cols; ++i) {
		keypad->cols[i] = cols[i];
	}

	gpio_setup();

	keypad->initialized = true;
}

void keypad_set_listener(struct keypad *keypad, keypad_listener listener) {
	ASSERTDO((keypad != NULL), verbose_out(stderr, "keypad_set_listener: keypad is null.\n"); return);
	
	if (listener != NULL) {
		keypad->callback = listener;
	}
}

int keypad_read(struct keypad *keypad) {
	ASSERTDO((keypad != NULL), verbose_out(stderr, "keypad_read: keypad is null.\n"); return -1);
	
	/* all rows LOW. */
	pinv_mode(keypad->rows, keypad->n_rows, PGPIO_OUTPUT);
	digital_writev(keypad->rows, keypad->n_rows, PGPIO_LOW);
	
	int sel_col = -1;
	int sel_row = -1;
	
	/* find column. */
	for (int i = 0; i < keypad->n_cols; ++i) {
		pin_mode(keypad->cols[i], PGPIO_INPUT_PULLUP); /* set mode and read at once. */
		
		if (digital_read(keypad->cols[i]) == 0)	{
			/* in pull-up mode, active zero. */
			sel_col = i;
			verbose_out(stdout, "keypad: selected column: %d.\n", i);

			break;
		}

		udelay(KEYPAD_SCAN_DELAY); /* to save cpu. */
	}
	
	if (sel_col == -1) {
		/* none of them are selected. */
		return -1;
	}


	/* selected column LOW. */
	pin_mode(keypad->cols[sel_col], PGPIO_OUTPUT);
	digital_write(keypad->cols[sel_col], PGPIO_LOW);

	/* find row. */
	for (int i = 0; i < keypad->n_rows; ++i) {
		pin_mode(keypad->rows[i], PGPIO_INPUT_PULLUP);

		if (digital_read(keypad->rows[i]) == 0) {
			sel_row = i;
			verbose_out(stdout, "keypad: selected row: %d.\n", i);
			
			break;
		} 

		udelay(KEYPAD_SCAN_DELAY); /* to save cpu. */
	}

	if (sel_row == -1) {
		/* Hmm.. can this happen? */
		verbose_out(stderr, "WTF???\n");
		return -1;
	}

	return _point_to_index(sel_row, sel_col, keypad->n_cols);
}
	
bool pressed = false;

bool keypad_loop(struct keypad *keypad) {
	ASSERTDO((keypad != NULL), verbose_out(stderr, "keypad_loop: keypad is null.\n"); return false);

	if (keypad->callback != NULL) {
		int read = keypad_read(keypad);
		printf("read: %d\n", read);	
		if (read != -1) {
			if (!pressed) {
				/* has something pushed just now. */
				keypad->callback((enum KEY)read);
				pressed = true;
			} else {
				printf("nothin to do!\n");
			}
		} else {
			pressed = false;
		}
	}

	return true;
}

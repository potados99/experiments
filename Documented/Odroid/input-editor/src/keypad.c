#include "keypad.h"
#include "verbose.h"
#include "pgpio.h"
#include "machine_specific.h"

#include <string.h>

void keypad_setup(struct keypad *keypad, int rows[], int n_rows, int cols[], int n_cols) {
	ASSERTDO((keypad != NULL), print_error("keypad_setup: keypad is null.\n"); return);
	ASSERTDO((rows != NULL), print_error("keypad_setup: rows is null.\n"); return);
	ASSERTDO((cols != NULL), print_error("keypad_setup: cols is null.\n"); return);	
	ASSERTDO((n_rows >= 0), print_error("keypad_setup: n_rows cannot be under zero.\n"); return);
	ASSERTDO((n_cols >= 0), print_error("keypad_setup: n_cols cannot be under zero.\n"); return);
	for (int i = 0; i < n_rows; ++i) {
		ASSERTDO((rows[i] >= 0), print_error("keypad_setup: rows[%d] cannot be under zero.\n", i); return);
	}
	for (int i = 0; i < n_cols; ++i) {
		ASSERTDO((cols[i] >= 0), print_error("keypad_setup: cols[%d] cannot be under zero.\n", i); return);
	}

	/* initialize */
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
	ASSERTDO((keypad != NULL), print_error("keypad_set_listener: keypad is null.\n"); return);
	
	if (listener != NULL) {
		keypad->callback = listener;
	}
}

int keypad_read(struct keypad *keypad) {
	ASSERTDO((keypad != NULL), print_error("keypad_read: keypad is null.\n"); return -1);
	
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
			print_trace("keypad: selected column: %d.\n", i);

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
			print_trace("keypad: selected row: %d.\n", i);
			
			break;
		} 

		udelay(KEYPAD_SCAN_DELAY); /* to save cpu. */
	}

	if (sel_row == -1) {
		/* Hmm.. can this happen? */
		print_trace("FASTER THAN ME?\n");
		
		return -1;
	}

	return _point_to_index(sel_row, sel_col, keypad->n_cols);
}

bool keypad_loop(struct keypad *keypad) {
	ASSERTDO((keypad != NULL), print_error("keypad_loop: keypad is null.\n"); return false);

	static bool pressed = false;

	if (keypad->callback != NULL) {
		int read = keypad_read(keypad);
		
		if (read != -1) { 
			/* something is pressed. */

			if (!pressed) {
				/* has something pushed just now. */
				keypad->callback(read);
		
				pressed = true;
			} else {
				/* being kept pressed. do nothing. */
			}

		} else {
			/* read nothing. of cource not pressed. */
			pressed = false;
		}
	}

	return true;
}

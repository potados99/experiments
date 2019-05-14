#ifndef _KEYPAD_H
#define _KEYPAD_H

/**
  * Abstract keypad matrix.
  * 
  * Usage: 
  * 	1) Declare and allocate a variable of type struct keypad.
  *	2) keypad_setup(): variable init and hardware setup.
  *	3) keypad_set_listener(): add callback.
  *
  *
  * Notice:
  *	A macro variable KEYPAD_SCAN_DELAY must exist.
  *	Callback must be registered to use full functionality.
  */

#include <stdbool.h>

#define MAX_ROWS 4
#define MAX_COLS 4

typedef void (*keypad_listener)(int);

struct keypad {
	bool initialized;

	int rows[MAX_ROWS];
	int n_rows;

	int cols[MAX_COLS];
	int n_cols;

	keypad_listener callback;	
};

/**
  * Convert row and column point to key index.
  */
static inline int _point_to_index(int row, int col, int n_cols) {
	return (row * n_cols) + col;
}

/**
  * Init and assign struct keypad.
  */
void keypad_setup(struct keypad *keypad, int rows[], int n_rows, int cols[], int n_cols);

/**
  * Set a callback launchec when input is available.
  */
void keypad_set_listener(struct keypad *keypad, keypad_listener listener);

/**
  * Read matrix and return the index of button pushed at that time.
  * If none, return -1.
  */
int keypad_read(struct keypad *keypad);

/**
  * A single update loop.
  * Should be run in a fast and infinite loop.
  */
bool keypad_loop(struct keypad *keypad);


#endif /* _KEYPAD_H */



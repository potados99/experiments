#ifndef _KEYPAD_H
#define _KEYPAD_H

#include <stdbool.h>

#define MAX_ROWS 4
#define MAX_COLS 4

/**
  * Could vary.
  */
enum KEY {
	NUM_0 		= 1,
	NUM_1 		= 8,
	NUM_2 		= 9,
	NUM_3 		= 10,
	NUM_4 		= 4,
	NUM_5 		= 5,
	NUM_6 		= 6,
	NUM_7 		= 0,
	NUM_8 		= 1,
	NUM_9 		= 2,
	FUN_ADD 	= 11,
	FUN_SUB 	= 7,
	FUN_RES 	= 15
};

typedef void (*keypad_listener)(enum KEY);

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



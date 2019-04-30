#ifndef _CALC_H
#define _CALC_H

/**
  * Decimal Adder/Subtractor with display.
  *
  * Usage:
  * 	1) Declare and allocate a variable type of struct calc.
  *	2) calc_setup(): initialize variable and get ready.
  *	3) calc_attatch_callback(): add callbacks.
  *
  * Notice:
  *	Three callbacks needed. 
  *	One for when to add a character to display,
  *	One for when to shift a cursor of display.
  * 	One for when to clear a display.
  *
  */

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "clcd.h"
#include "macros.h"

#define CALC_EXP_MAX 	64
#define CALC_MAX_DIGITS	9

#define CALC_ADD	0x10
#define CALC_SUB	0x20
#define CALC_RES	0x40

enum KEY {
	NUM_0 		= 13,
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

struct exp {
	bool 		isnumber;
	int 		content;
};

typedef void (*calc_callback)(int);

struct calc {
	bool		initialized;
	bool		isdone;

	struct exp	exps[CALC_EXP_MAX];
	int		exps_len;

	uint8_t		cur_exp[CALC_MAX_DIGITS];
	int		cur_exp_len;

	bool 		exp_reading;
	int		next_operator;

	bool		erroring;

	calc_callback	on_append;
	calc_callback	on_shift;
	calc_callback	on_clear;
};

static inline bool calc_isdigit(int num) {
	return ((num >= 0) && (num <= 9));
}

/**
  * Initialize struct fields.
  */
void calc_setup(struct calc *calc);

/**
  * Add callbacks.
  */
void calc_attach_callback(struct calc *calc, calc_callback on_append, calc_callback on_shift, calc_callback on_clear);

/**
  * Prepare for incomming digits as a part of expression.
  */
void calc_start_input_exp(struct calc *calc);

/**
  * Add the very came digit to the part of current expression.
  */
void calc_on_input_exp(struct calc *calc, int digit);

/**
  * Stop reading inputs as an expression.
  */
void calc_end_input_exp(struct calc *calc);

/**
  * Add a complete expression(could be an operator) to array.
  */
void calc_add_exp(struct calc *calc, struct exp expression);

/**
  * Clear all expressions calc have. (no erase immediately)
  */
void calc_clr_exp(struct calc *calc);

/**
  * Evaluate expressions and return >= 0 if success.
  * On successful execution, *result will take the value.
  */
int calc_eval(struct calc *calc, int *result);

/**
  * Invoke callback to inform that a display has to add character.
  */
void invoke_on_append(struct calc *calc, int content);

/**
  * Invoke callback to inform that a display has to shift cursor.
  */
void invoke_on_shift(struct calc *calc, int content);

/**
  * Invoke callback to inform that a display has to erase all.
  */
void invoke_on_clear(struct calc *calc, int content);

/**
  * Invoke invoke_on_append with number as a string.
  */
void invoke_on_append_dec(struct calc *calc, int num);

/**
 * User call this every time keypad is pushed.
 */
void calc_key_input(struct calc *clcd, enum KEY input);

/**
  * Clear all. including display and expression array.
  */
void calc_clear(struct calc *calc, char with);

/**
  * Print error message and reset.
  */
void calc_error(struct calc *calc, char *with);

#endif /* _CALC_H */

#include "calc.h"

#include <math.h>
#include <string.h>
#include <stdlib.h>

void calc_setup(struct calc *calc) {
	ASSERTDO((calc != NULL), print_error("calc_setup: calc is null.\n"); return);

	/* initialize. */
	calc->initialized = false;
	calc->isdone = false;
	memset(calc->exps, 0, sizeof(struct exp) * CALC_EXP_MAX);
	calc->exps_len = 0;
	memset(calc->cur_exp, 0, sizeof(int) * CALC_MAX_DIGITS);
	calc->cur_exp_len = 0;
	calc->exp_reading = false;
	calc->next_operator = 0;
	calc->erroring = false;
	calc->on_append = NULL;
	calc->on_shift = NULL;
	calc->on_clear = NULL;

	/* assign. */
	calc->initialized = true;
	calc->isdone = true;

	calc_start_input_exp(calc);
}

void calc_attach_callback(struct calc *calc, calc_callback on_append, calc_callback on_shift, calc_callback on_clear) {
	ASSERTDO((calc != NULL), print_error("calc_attach_callback: calc is null.\n"); return);
	ASSERTDO((on_append != NULL), print_error("calc_attach_callback: on_append is null.\n"); return);
	ASSERTDO((on_shift != NULL), print_error("calc_attach_callback: on_shift is null.\n"); return);
	ASSERTDO((on_clear != NULL), print_error("calc_attach_callback: on_clear is null.\n"); return);
	
	calc->on_append = on_append;
	calc->on_shift = on_shift;
	calc->on_clear = on_clear;
}

void calc_start_input_exp(struct calc *calc) {
	ASSERTDO((calc != NULL), print_error("_calc_start_input_exp: calc is null.\n"); return);

	calc->cur_exp_len = 0;
	calc->exp_reading = true;
}

void calc_on_input_exp(struct calc *calc, int digit) {
	ASSERTDO((calc != NULL), print_error("calc_on_input_exp: calc is null.\n"); return);
	ASSERTDO((calc_isdigit(digit)), print_error("calc_on_input_exp: digit is not a digit.\n"); return);
	ASSERTDO((calc->initialized), print_error("calc_on_input_exp: calc is not initialized.\n"); return);
	ASSERTDO((calc->exp_reading), print_error("calc_on_input_exp: calc is not reading incomming keys. start input first.\n"); return);
	ASSERTDO((calc->cur_exp_len <= 9), print_error("calc_on_input_exp: one expression can hold only 9 digits.\n"); return);

	calc->cur_exp[calc->cur_exp_len++] = digit;

	print_info("current exp reading: ");
	for (int i = 0; i < calc->cur_exp_len; ++i) {
		print_info("%d ", calc->cur_exp[i]);
	}
	print_info("\n");
}

void calc_end_input_exp(struct calc *calc) {
	ASSERTDO((calc != NULL), print_error("calc_end_input_exp: calc is null.\n"); return);

	int num = 0;

	for (int i = 0; i < calc->cur_exp_len; ++i) {
		num += calc->cur_exp[i] * pow(10, calc->cur_exp_len - 1 - i);
	}
	
	calc->cur_exp_len = 0;
	calc->exp_reading = false;
	
	print_info("complete expression is: %d\n", num);

	struct exp this_exp = { .isnumber = true, .content = num };

	calc_add_exp(calc, this_exp);
}

void calc_add_exp(struct calc *calc, struct exp expression) {
	ASSERTDO((calc != NULL), print_error("calc_add_exp: calc is null.\n"); return);
	ASSERTDO((calc->exps != NULL), print_error("calc_add_exp: calc->exps is null.\n"); return);
	
	calc->exps[calc->exps_len++] = expression;
}

void calc_clr_exp(struct calc *calc) {
	ASSERTDO((calc != NULL), print_error("calc_clr_exp: calc is null.\n"); return);
	
	calc->exps_len = 0;
}

int calc_eval(struct calc *calc, int *result) {
	ASSERTDO((calc != NULL), print_error("calc_eval: calc is null.\n"); return -1);
	ASSERTDO((result != NULL), print_error("calc_eval: result is null.\n"); return -1);

	int res = 0;
	
	int last_operator = CALC_ADD;

	for (int i = 0; i < calc->exps_len; ++i) {
		if (calc->exps[i].isnumber) {
			if (last_operator == CALC_ADD) {
				res += calc->exps[i].content;
			} else if (last_operator == CALC_SUB) {
				res -= calc->exps[i].content;
			} else {
				print_info("calc_eval: operator must be either CLCD_ADD or CLCD_SUB.\n");
			}
		} else {
			last_operator = calc->exps[i].content;
		}
	}

	*result = res;
	
	return 0;
}

void invoke_on_append(struct calc *calc, int content) {
	ASSERTDO((calc != NULL), print_error("invoke_on_append: calc is null.\n"); return);
	
	if (calc->on_append) {
		calc->on_append(content);
		print_trace("invoke on_append with %c.\n", content);
	}
}

void invoke_on_shift(struct calc *calc, int content) {
	ASSERTDO((calc != NULL), print_error("invoke_on_shift: calc is null.\n"); return);

	if (calc->on_shift) {
		calc->on_shift(content);
		print_trace("invoke on_shift with %c.\n", content);
	}	
}

void invoke_on_clear(struct calc *calc, int content) {
	ASSERTDO((calc != NULL), print_error("invoke_on_clear: calc is null.\n"); return);

	if (calc->on_clear) {
		calc->on_clear(content);
		print_trace("invoke on_clear with %c.\n", content);
	}	
}

void invoke_on_append_dec(struct calc *calc, int num) {
	char buf[CALC_MAX_DIGITS] = {0, };
	sprintf(buf, "%d", num);
	
	for (int i = 0; i < strlen(buf); ++i) {
		invoke_on_append(calc,(int)(buf[i]));
	}
}

void calc_key_input(struct calc *calc, enum KEY key) {
	int input = 0;

	switch (key) {
		case NUM_0:	input = 0; break;
		case NUM_1:	input = 1; break;
		case NUM_2:	input = 2; break;	
		case NUM_3:	input = 3; break;
		case NUM_4:	input = 4; break;
		case NUM_5:	input = 5; break;
		case NUM_6:	input = 6; break;
		case NUM_7:	input = 7; break;
		case NUM_8:	input = 8; break;
		case NUM_9:	input = 9; break;
		case FUN_ADD:	input = CALC_ADD; break;
		case FUN_SUB:	input = CALC_SUB; break;
		case FUN_RES:	input = CALC_RES; break;
	}

	if (calc_isdigit(input)) {
		/**
		  * Digit came.
		  */

		if (calc->isdone || calc->erroring) {
			calc_clear(calc, '\0');
			calc_start_input_exp(calc);

			calc->isdone = false;
			calc->erroring = false;
		
		} else if (calc->next_operator != 0) {
			/**
			  * Time to fix the operator.
			  */

			/* add this operator to expression collection. */
			struct exp the_exp = { .isnumber = false, .content = calc->next_operator };
			calc_add_exp(calc, the_exp);

			/* start scanning new incomming expression. */
			calc_start_input_exp(calc);	

			calc->next_operator = 0;
		}

		if (calc->cur_exp_len == 1 && calc->cur_exp[0] == 0) {
			/**
			  * MSB of currend expression is zero.
			  */

			if (input == 0) {
				return; /* ignore. */
			} else {
				print_info("shift back.\n");
				invoke_on_shift(calc, -1);
			}
		}

		if (calc->cur_exp_len >= 9) {
			calc_error(calc, "Error:\noverflow :(");
			print_info("error: overflow.\n");
			return;
		}

		/* read it. */
		calc_on_input_exp(calc, input);

		/* print it. */
		invoke_on_append(calc, (int)(input + '0'));

	} else if (input == CALC_RES) {
		/** 
		  * Time to see the result.
		  */

		if (calc->erroring) {
			return;
		}
	
		if (calc->isdone) {
			return; /* do nothing after showing result. */
		}

		/* finish scanning number. */
		calc_end_input_exp(calc);

		if (calc->next_operator != 0) {
			/**
			  * End with operator.
			  */

			invoke_on_shift(calc, -1);
		}

		/* evaluate and throw away */
		int eval_result = 0;
		ASSERTDO((calc_eval(calc, &eval_result) >= 0), print_error("calc_key_input: cannot evaluate.\n"); return);
		calc_clr_exp(calc);
	
		/* add the result to expression collection. */
		struct exp new_exp = { .isnumber = true, .content = eval_result };
		calc_add_exp(calc, new_exp);

		/* print evaluation output. */
		invoke_on_append(calc, '=');
		if (eval_result >= 1000000000 || eval_result <= -1000000000) {
			/**
			  * more than 9 digits.
			  */
			calc_error(calc, "Error:\noverflow :(");
			print_info("error: overflow.\n");	
			return;
		}
		invoke_on_append_dec(calc, eval_result);

		calc->isdone = true;

	} else if (input == CALC_ADD || input == CALC_SUB) {
		/**
		  * Operator came.
		  */

		if (calc->erroring) {
			return;
		}

		if (calc->isdone) {
			/**
			  * Starting from last result. 
			  */

			/* get the last result. */
			int eval_result = 0;
			ASSERTDO((calc_eval(calc, &eval_result) >= 0), print_error("calc_key_input: cannot evaluate.\n"); return);
	
			/* print it. */
			invoke_on_clear(calc, '\0');
			invoke_on_append_dec(calc, eval_result);
			
			calc->isdone = false;
		}
		
		/* stop scanning incomming expression. */
		calc_end_input_exp(calc);
		
		if (calc->next_operator != 0) {
			invoke_on_shift(calc, -1); /* at least second operator choice. */
		}
		
		calc->next_operator = input;
		
		invoke_on_append(calc, (char)(input == CALC_ADD ? '+' : '-'));

	} else {
		/* NOREACH */
	}
}

void calc_clear(struct calc *calc, char with) {
	calc_clr_exp(calc);

	invoke_on_clear(calc, (int)with);
}

void calc_error(struct calc *calc, char *with) {
	calc_end_input_exp(calc);
	calc_clear(calc, '\0');

	calc->isdone = true;
	calc->next_operator = 0;

	calc->erroring = true;

	for (int i = 0; i < strlen(with); ++i) {
		invoke_on_append(calc, (int)with[i]);
	}
}

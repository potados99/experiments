//
//  debug.h
//  big_calc
//
//  Created by POTADOS on 04/02/2019.
//  Copyright © 2019 potados. All rights reserved.
//

#ifndef _pdbg_h
#define _pdbg_h

#include <stdio.h>
#include <stdlib.h>

typedef int RET;

enum RETURN_CODE {
    RET_SIG_EOF         = 2,
    RET_SIG_EXIT        = 1,
    RET_OK              = 0,
    RET_WRONG_PARAM     = -1,
    RET_ACTION_FAIL     = -2,
    RET_MEM_VIOLATION   = -3,
    RET_WRONG_PTR       = -4,
    RET_WRONG_VAL       = -5,
    RET_WRONG_FLOW      = -6,
    RET_CLBCK_FAIL      = -7
};

/**
 * Print fatal error and exit.
 *
 * @param _exit_code        Int value returned to system.
 * @param _fmt              Formated message.
 */
#define fatal(_exit_code, _fmt, ...)                                        \
do {                                                                        \
_print_log(stderr, "Fatal", _fmt, ##__VA_ARGS__);                           \
exit(_exit_code);                                                           \
} while(0)

/**
 * Print error and return.
 *
 * @param _return           Any type of value returned to caller.
 * @param _fmt              Formated message.
 */
#define error(_return, _fmt, ...)                                           \
do {                                                                        \
_print_log(stderr, "Error", _fmt, ##__VA_ARGS__);                           \
return _return;                                                             \
} while(0)

/**
 * Print warning and return.
 *
 * @param _fmt              Formated message.
 */
#define warn(_fmt, ...)                                                     \
_print_log(stdout, "Warn", _fmt, ##__VA_ARGS__);

/**
 * Print log and return.
 *
 * @param _fmt              Formated message.
 */
#define log(_fmt, ...)                                           	        \
_print_log(stdout, "Log", _fmt, ##__VA_ARGS__);

/**
 * Verify condition.
 * if condition is false, print error and return.
 *
 * @param _x                Condition. Error occures when it is zero(false).
 * @param _return           Any type of value returned to caller.
 * @param _fmt              Formated message.
 */
#define verify(_x, _return, _fmt, ...)                                      \
do {                                                                        \
if (!(_x)) {                                                                \
_print_log(stderr, "Error", _fmt, ##__VA_ARGS__);                           \
return _return;                                                             \
}                                                                           \
} while(0)

/**
 * Verify condition.
 * if condition is false, print error and execute _BLOCK.
 *
 * @param _x                Condition. Error occures when it is zero(false).
 * @param _BLOCK            Code block executed when condition is false.
 * @param _fmt              Formated message.
 */
#define verify_do(_x, _BLOCK, _fmt, ...)                                    \
do {                                                                        \
if (!(_x)) {                                                                \
_print_log(stderr, "Error", _fmt, ##__VA_ARGS__);                           \
_BLOCK                                                                      \
}                                                                           \
} while(0)

/**
 * Check condition.
 * if condition is false, print error.
 *
 * @param _x                Condition. Error occures when it is zero(false).
 * @param _fmt              Formated message.
 */
#define check(_x, _fmt, ...)                                                \
do {                                                                        \
if (!(_x)) {                                                                \
_print_log(stdout, "Warning", _fmt, ##__VA_ARGS__);                         \
}                                                                           \
} while(0)

/**
 * Check condition.
 * if condition is false, do _BLOCK.
 *
 * @param _x                Condition. Error occures when it is zero(false).
 * @param _fmt              Formated message.
 */
#define check_do(_x, _BLOCK, _fmt, ...)                                     \
do {                                                                        \
if (!(_x)) {                                                                \
_print_log(stdout, "Warning", _fmt, ##__VA_ARGS__);                         \
_BLOCK									    \
}                                                                           \
} while(0)

/**
 * Print log.
 *
 * @param _level            Level of error.
 * @param _fmt              Formated message.
 *
 * @return                  Number of characters printed.
 */
#define _print_log(_stream, _level, _fmt, ...)                              \
fprintf(_stream,                                                            \
"<" _level "> at file \"%s\", function \"%s\", line %d: " _fmt "\n",        \
__FILE__, __func__, __LINE__, ##__VA_ARGS__)


#endif /* _pdbg_h */


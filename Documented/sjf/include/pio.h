//
//  io.h
//  brainfuck-interpreter
//
//  Created by POTADOS on 05/02/2019.
//  Copyright © 2019 potados. All rights reserved.
//

#ifndef _pio_h
#define _pio_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pdbg.h"

/**
 * String callback.
 * A string and its length is passed.
 */
typedef int (*str_callback)(const char *, int);

/**
 * Handle user input from stream and launch callback.
 * Default EOF handling is:
 *  stop reading & run callback & return RET_SIG_EOF.
 *
 * @param from          Input stream.
 * @param about         Number of bytes to read.
 * @param until         Read until this character. (not included.)
 * @param stop_on       Immediately return stop_with when this character is came.
 * @param stop_with     Signal to return when stop_on came.
 * @param and_then      Callback to launch when input completed.
 *
 * @return              Zero on normal, negative on error, positive on signal.
 *                      normal: got 'until' or reach 'about', and callback is successful.
 *                      error:  callback failed.
 *                      signal: got EOF.
 */
RET p_with_input(FILE           *from,
                 int            about,
                 char           until,
                 char           stop_on,
                 int            stop_with,
                 str_callback   and_then);

/**
 * Open and read file, and launch callback.
 *
 * @param filename      Input filename.
 * @param callback      Callback to launch when input completed.
 *
 * @return              Zero on normal, negative on error.
 */
RET p_with_file(const char * filename, str_callback callback);

#endif /* _pio_h */

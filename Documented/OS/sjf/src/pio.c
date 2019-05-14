//
//  io.c
//  brainfuck-interpreter
//
//  Created by POTADOS on 05/02/2019.
//  Copyright © 2019 potados. All rights reserved.
//

#include "pio.h"

RET p_with_input(FILE           *from,
                 int            about,
                 char           until,
                 char           stop_on,
                 int            stop_with,
                 str_callback   and_then) {
    
    verify(from, RET_WRONG_PARAM, "from is null.");
    verify(and_then, RET_WRONG_PARAM, "and_then is null.");

    char total_buf[1024]    = {0, };
    int total_len           = 0;

    check_do(about < (int)sizeof(total_buf), { about = 1024; }, "about is %d, exceeds max buffer size %d.", about, (int)sizeof(total_buf));
    
    int current_char       = 0;
    char * p                = total_buf;
    
    int got_eof             = 0;
    
    while ((current_char = fgetc(from))) {
        if (current_char == until) {
            break;
        }
        else if (about && ((int)(p - total_buf) >= about)) {
            warn("stop reading due to length limit of %d.", about);
            break;
        }
        else if (stop_on && (current_char == stop_on)) {
            return stop_with;
        }
        else if (current_char == EOF) {
            warn("got unexpected EOF.");
            got_eof = 1;
            break;
        }
        else {
            *p++ = current_char;
        }
    }
    
    total_buf[(total_len = (int)(p - total_buf))] = '\0'; /* just for safety. */
    
    int callback_result = and_then(total_buf, total_len);

    if (got_eof) return RET_SIG_EOF;
    else
        if (callback_result < 0) error(RET_ACTION_FAIL, "callback failed.");
        else return callback_result;
}

RET p_with_file(const char * filename, str_callback callback) {
    verify(filename, RET_WRONG_PARAM, "filename is null.");
    verify(callback, RET_WRONG_PARAM, "callback is null.");

    FILE *file;
    file = fopen(filename, "rt");
    verify(file, RET_ACTION_FAIL, "fopen failed for \"%s\".", filename);
    
    // read forever until EOF, no exit signal.
    int result = p_with_input(file, 0, EOF, 0, 0, callback);
    
    fclose(file);
    
    if (result < 0) error(RET_ACTION_FAIL, "p_with_input failed.");
    else return result;
}


#ifndef _EDITOR_H
#define _EDITOR_H

/**
 * An english input editor with 3 * 3 keypad.
 *
 */

#include "macros.h"
#include "verbose.h"

#include <stdbool.h>

typedef void (*editor_callback)(int);

struct editor_callbacks{
    editor_callback on_cursor_move;
    editor_callback on_insert;
    editor_callback on_delete;
    editor_callback on_replace;
};

struct editor {
    bool initialized;
    
    bool typing;
    char last_char;
    int last_key;
    
    struct editor_callbacks callbacks;
};

/**
 * Map key index to editor key.
 */
enum editor_key {
    KEY_DQZ = 0,
    KEY_ABC = 1,
    KEY_DEF = 2,
    KEY_GHI = 4,
    KEY_JKL = 5,
    KEY_MNO = 6,
    KEY_PRS = 8,
    KEY_TUV = 9,
    KEY_WXY = 10,
    
    KEY_CL = 7,     /* cursor left */
    KEY_CR = 15,    /* cursor right */
    KEY_DEL = 11,
    KEY_SPC = 13    /* space */
};

/**
 * Get next character sequence of same button from current character.
 * The sequence is hardcoded.
 */
static inline int next_char(char c) {
    /**
     * .qz
     * abc
     * def
     *
     * ghi
     * jkl
     * mno
     *
     * prs
     * tuv
     * wxy
     */
    
    switch (c) {
        case '.': return 'q';
        case 'q': return 'z';
        case 'z': return '.';
            
        case 'a': return 'b';
        case 'b': return 'c';
        case 'c': return 'a';
            
        case 'd': return 'e';
        case 'e': return 'f';
        case 'f': return 'd';
            
        case 'g': return 'h';
        case 'h': return 'i';
        case 'i': return 'g';
            
        case 'j': return 'k';
        case 'k': return 'l';
        case 'l': return 'j';
            
        case 'm': return 'n';
        case 'n': return 'o';
        case 'o': return 'm';
            
        case 'p': return 'r';
        case 'r': return 's';
        case 's': return 'p';
            
        case 't': return 'u';
        case 'u': return 'v';
        case 'v': return 't';
            
        case 'w': return 'x';
        case 'x': return 'y';
        case 'y': return 'w';
            
        default: return -1;
    }
}

/**
 * Launch callback if not null.
 */
static inline int launch_callback(editor_callback callback, int param) {
    ASSERTDO((callback != NULL), print_error("launch_callback: callback is null.\n"); return -1);

    callback(param);
    
    return 0;
}


/********************************************************************************
 * Internal functions.
 ********************************************************************************/

/**
 * Callback launchers
 */
int _editor_on_cursor_move(struct editor *editor, int delta);
int _editor_on_insert(struct editor *editor, char c);
int _editor_on_delete(struct editor *editor);
int _editor_on_replace(struct editor *editor, char c);


/********************************************************************************
 * Public functions.
 ********************************************************************************/

/**
 * Initial setup.
 */
int editor_setup(struct editor *editor);

/**
 * Add callbacks.
 */
int editor_add_callbacks(struct editor *editor, struct editor_callbacks callbacks);

/**
 * Do action given the index of the key pressed.
 */
int editor_input(struct editor *editor, int key_index);

#endif /* _EDITOR_H */

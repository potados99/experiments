#include "editor.h"
#include "verbose.h"
#include "macros.h"

/*
 struct editor {
 bool initialized;
 
 bool typing;
 char last_typed;
 
 struct editor_callbacks callbacks;
 };
 */


int _editor_on_cursor_move(struct editor *editor, int delta) {
    return launch_callback(editor->callbacks.on_cursor_move , delta);
}

int _editor_on_insert(struct editor *editor, char c) {
    return launch_callback(editor->callbacks.on_insert , c);
}

int _editor_on_delete(struct editor *editor) {
    return launch_callback(editor->callbacks.on_delete , 0);
}

int _editor_on_replace(struct editor *editor, char c) {
    return launch_callback(editor->callbacks.on_replace , c);
}

int editor_setup(struct editor *editor) {
    ASSERTDO((editor != NULL), print_error("editor_setup: editor is null.\n"); return -1);

    editor->initialized = false;
    
    editor->typing = false;
    editor->last_typed = 0;
    
    editor->initialized = true;

    return 0;
}

int editor_add_callbacks(struct editor *editor, struct editor_callbacks callbacks) {
    ASSERTDO((editor != NULL), print_error("editor_add_callbacks: editor is null.\n"); return -1);
    
    ASSERTDO((callbacks.on_cursor_move != NULL),
             print_error("editor_add_callbacks: callbacks.on_cursor_move is null.\n");
             return -1);
    
    ASSERTDO((callbacks.on_insert != NULL),
             print_error("editor_add_callbacks: callbacks.on_insert is null.\n");
             return -1);
    
    ASSERTDO((callbacks.on_delete != NULL),
             print_error("editor_add_callbacks: callbacks.on_delete is null.\n");
             return -1);
    
    ASSERTDO((callbacks.on_replace != NULL),
             print_error("editor_add_callbacks: callbacks.on_replace is null.\n");
             return -1);
    
    editor->callbacks = callbacks;
    
    return 0;
}

int editor_input(int key_index) {
    
    /*
     KEY_DQZ
     KEY_ABC
     KEY_DEF
     KEY_GHI
     KEY_JKL
     KEY_MNO
     KEY_PRS
     KEY_TUV
     KEY_WXY
     KEY_CL
     KEY_CR
     KEY_DEL
     KEY_SPC

     */
    
    switch (key_index) {
        case KEY_DQZ:
            
            break;
            
        case KEY_ABC:
        
            break;
            
        case KEY_DEF:
            
            break;
            
        case KEY_GHI:
            
            break;
            
        case KEY_JKL:
            
            break;
            
        case KEY_MNO:
            
            break;
            
        case KEY_PRS:
            
            break;
            
        case KEY_TUV:
            
            break;
            
        case KEY_WXY:
            
            break;
            
        case KEY_CL:
            
            break;
            
        case KEY_CR:
            
            break;
            
        case KEY_DEL:
            
            break;
            
        case KEY_SPC:
            
            break;
            
        default:
            break;
    }
    
    
    return 0;
    
}

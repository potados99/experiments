#include "editor.h"
#include "verbose.h"
#include "macros.h"

/*
 struct editor {
 bool initialized;
 
 bool typing;
 char last_char;
 int last_key;
 
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
    editor->last_char = 0;
    editor->last_key = 0;

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

int editor_input(struct editor *editor, int key_index) {
    ASSERTDO((editor != NULL), print_error("editor_input: editor is null.\n"); return -1);

    char c;
    char head_char = '\0';
    
    switch (key_index) {
        case KEY_DQZ:   editor->typing = true; head_char = '.'; break;
        case KEY_ABC:   editor->typing = true; head_char = 'a'; break;
        case KEY_DEF:   editor->typing = true; head_char = 'd'; break;
        case KEY_GHI:   editor->typing = true; head_char = 'g'; break;
        case KEY_JKL:   editor->typing = true; head_char = 'j'; break;
        case KEY_MNO:   editor->typing = true; head_char = 'm'; break;
        case KEY_PRS:   editor->typing = true; head_char = 'p'; break;
        case KEY_TUV:   editor->typing = true; head_char = 't'; break;
        case KEY_WXY:   editor->typing = true; head_char = 'w'; break;
            
        case KEY_CL:    editor->typing = false; break;
        case KEY_CR:    editor->typing = false; break;
        case KEY_DEL:   editor->typing = false; break;
        case KEY_SPC:   editor->typing = false; break;
            
        default:
            print_error("editor_input: wrong key index: %d.\n", key_index);
            return -1;
    }
    
    if (editor->last_key == key_index && editor->typing) {
        /**
         * Pushing the same alphabet key for >= two times.
         */
        c = next_char(editor->last_char);
        
        _editor_on_replace(editor, c);
        
        editor->last_char = c;
    }
    else if (editor->typing) {
        /**
         * New alphabet key is pushed.
         */
        _editor_on_insert(editor, head_char);
    }
    else {
        /**
         * Function key
         */
        switch (key_index) {
            case KEY_CL:
                _editor_on_cursor_move(editor, -1);
                break;
                
            case KEY_CR:
                _editor_on_cursor_move(editor, +1);
                break;
                
            case KEY_DEL:
                _editor_on_delete(editor);
                break;
                
            case KEY_SPC:
                _editor_on_insert(editor, ' ');
                _editor_on_cursor_move(editor, +1);
                break;
                
            default:
                print_error("editor_input: impossible case. what is this?\n");
                break;
        }
    }
    
    editor->last_key = key_index;
    
    return 0;
}

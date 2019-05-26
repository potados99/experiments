#include "vclcd.h"
#include "verbose.h"
#include "pgpio.h"
#include "machine_specific.h"
#include "font.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

/**
 * Get address of top left point of the character area cur_pos is at.
 * Tested 190526
 */
static inline int vclcd_offset(int cur_pos) {
    return  OFFSET_VERTICAL( (VCLCD_CHAR_HEIGHT + VCLCD_CHAR_PADDING) * ROW_INDEX(cur_pos) ) +
            OFFSET_HORIZONTAL( (VCLCD_CHAR_WIDTH + VCLCD_CHAR_PADDING) * COL_INDEX(cur_pos) ) +
            MARGIN;
}

/**
 * Get address of bottom left point of the character area cur_pos is at.
 * Tested 190526
 */
static inline int vclcd_offset_cursor(int cur_pos) {
    return vclcd_offset(cur_pos) + OFFSET_VERTICAL(VCLCD_CHAR_HEIGHT);
}


/* Tested 190526 */
int _vclcd_clear(struct vclcd *vclcd, uint16_t pixel_center, uint16_t pixel_side) {
    ASSERTDO((vclcd != NULL), print_error("_vclcd_clear: vclcd is null.\n"); return -1);

    int         col_index = 0;
    uint16_t    pixel = pixel_side;
    
    for (int i = 0; i < VCLCD_WIDTH * VCLCD_HEIGHT; ++i) {
        if      (col_index == 0)                       pixel = pixel_side;
        else if (col_index == MARGIN)                  pixel = pixel_center;
        else if (col_index == VCLCD_WIDTH - MARGIN)    pixel = pixel_side;
            
        *(vclcd->mem + i) = pixel;
        
        if (++col_index == VCLCD_WIDTH) col_index = 0;
    }
    
    return 0;
}

/* Tested 190526 */
int _vclcd_draw_char(struct vclcd *vclcd, int at, char c, uint16_t pixel) {
    ASSERTDO((vclcd != NULL), print_error("_vclcd_draw_char: vclcd is null.\n"); return -1);
    
    int idx = font_index(c);
    ASSERTDO((idx != -1), print_error("_vclcd_draw_char: attempting to write wrong character: [%c]\n", c); return -1);

    const unsigned int      *font_rows = *(font + idx);
    int                     pixel_pos = vclcd_offset(at);
    
    int                     cur_row;                                /* a single row of font. */
    uint16_t                *address;                               /* actual address where pixel will be written. */
    
    for (int row = 0; row < VCLCD_CHAR_HEIGHT; ++row) {
        
        cur_row = *font_rows++;                                     /* from the first font row. */
        address = vclcd->mem + pixel_pos + VCLCD_CHAR_WIDTH - 1;    /* right end of the LCD row */
        
        for (int col = 0; col < VCLCD_CHAR_WIDTH; ++col) {
            if ((cur_row & 0x01))
                *address = pixel;
            
            cur_row >>= 1;
            address -= 1;
        }
        
        pixel_pos += OFFSET_VERTICAL(1);
    }

    return 0;
}

/* Tested 190526 */
int _vclcd_draw_cursor(struct vclcd *vclcd, int at, uint16_t pixel) {
    uint16_t *address = vclcd->mem + vclcd_offset_cursor(at);
    
    for (int row = 0; row < VCLCD_CURSOR_THICKNESS; ++row) {
        for (int col = 0; col < VCLCD_CHAR_WIDTH; ++col) {
            *address++ = pixel;
        }
        
        address += (OFFSET_VERTICAL(1) - VCLCD_CHAR_WIDTH);
    }
    
    return 0;
}

/* Tested 190526 */
int _vclcd_shift(struct vclcd *vclcd, int start, int length, int offset) {
    ASSERTDO((vclcd != NULL), print_error("_vclcd_shift: vclcd is null.\n"); return -1);
    ASSERTDO((start >= 0 && start < VCLCD_ROWS * VCLCD_COLS),
             print_error("_vclcd_shift: start out of range.\n"); return -1);
    ASSERTDO((start + length >= 0 && start + length < VCLCD_ROWS * VCLCD_COLS),
             print_error("_vclcd_shift: start + length out of range.\n"); return -1);
    ASSERTDO((start + offset >= 0 && start + length + offset < VCLCD_ROWS * VCLCD_COLS),
             print_error("_vclcd_shift: offset too big.\n"); return -1);

    if (length == 0) return 0;
    if (offset == 0) return 0;
    
    int right_whole = (start + length >= vclcd->chars_len);
    if (right_whole) {
        length = vclcd->chars_len - start; /* fit. */
    }
    
    int affected_start = 0;
    int affected_end = 0;
    
    
    /****************************************
     * Graphic - clear affected characters.
     ****************************************/
    if (offset > 0) {
        affected_start = start;
        affected_end = start + length - 1 + offset;
    }
    else if (offset < 0) {
        affected_start = start + offset;
        if (affected_start < 0) affected_start = 0;
        
        affected_end = start + length - 1;
    }

    for (int i = affected_start; i <= affected_end; ++i) {
        if (vclcd->chars[i]) /* end could be null. */
            _vclcd_draw_char(vclcd, i, vclcd->chars[i], COLOR_NONE);
    }
    
    
    /****************************************
     * Data - update data.
     ****************************************/
    memmove(vclcd->chars + start + offset, vclcd->chars + start, length);
    
    /* fill emptiness with [space] */
    if (offset > 0) {
        memset(vclcd->chars + start, ' ', offset);
    }
    else if (offset < 0) {
        memset(vclcd->chars + start + length + offset, (right_whole ? '\0' : ' '), offset * -1);
    }
    
    if (right_whole) {
        vclcd->chars_len += offset;
    }
    
    
    /****************************************
     * Graphic - write charactes again.
     ****************************************/
    for (int i = affected_start; i <= affected_end; ++i) {
        if (vclcd->chars[i]) /* draw only non-null char. */
            _vclcd_draw_char(vclcd, i, vclcd->chars[i], COLOR_CHARACTER);
    }

    return 0;
}


/* Tested 190526 */
int vclcd_setup(struct vclcd *vclcd, const char *dev_path) {
    ASSERTDO((vclcd != NULL), print_error("vclcd_setup: vclcd is null.\n"); return -1);
    
    vclcd->initialized = false;
    
    /**
     * open fd
     */
    if ((vclcd->fd = open(dev_path, O_RDWR)) == -1) {
        perror("open() failed");
        print_error("vclcd_setup: open() failed with %s.\n", dev_path);
        return -1;
    }
    
    /**
     * map memory
     */
    int size = VCLCD_WIDTH * VCLCD_HEIGHT * sizeof(uint16_t);
    int prot = PROT_WRITE | PROT_READ;
    int flag = MAP_SHARED;
    if ((vclcd->mem = mmap(0, size, prot, flag, vclcd->fd, 0)) == MAP_FAILED) {
        perror("mmap() failed");
        print_error("vclcd_setup: mmap() failed.\n");
        return -1;
    }
    
    memset(vclcd->chars, 0, sizeof(char) * VCLCD_ROWS * VCLCD_COLS);
    vclcd->chars_len = 0;
    vclcd->curs_pos = 0;
    
    vclcd->initialized = true;
    
    _vclcd_clear(vclcd, COLOR_BACKGROUND, COLOR_OUTSIDE);
    _vclcd_draw_cursor(vclcd, vclcd->curs_pos, COLOR_CURSOR);
    
    return 0;
}

/* Tested 190526 */
int vclcd_close(struct vclcd *vclcd) {
    ASSERTDO((vclcd != NULL), print_error("vclcd_close: vclcd is null.\n"); return -1);
    
    _vclcd_clear(vclcd, PIXEL_BLACK, PIXEL_BLACK);
    
    if (munmap(vclcd->mem, VCLCD_WIDTH * VCLCD_HEIGHT * sizeof(uint16_t)) == -1) {
        perror("munmap() failed");
        print_error("vclcd_close: munmap() failed.\n");
        return -1;
    }
    
    if (close(vclcd->fd) == -1) {
        perror("close() failed");
        print_error("vclcd_close: close() failed.\n");
        return -1;
    }
    
    return 0;
}

/* Tested 190526 */
int vclcd_seek(struct vclcd *vclcd, int offset, int whence) {
    ASSERTDO((vclcd != NULL), print_error("vclcd_cursor_seek: vclcd is null.\n"); return -1);
    
    int result;
    switch (whence) {
        case SEEK_CUR:
            result = vclcd->curs_pos + offset;
            break;
            
        case SEEK_SET:
            result = offset;
            break;
            
        default:
            print_error("vclcd_cursor_seek: only SEEK_CUR and SEEK_SET are allowed.\n");
            return -1;
    }
    
    int in_display = (result >= 0 && result < (VCLCD_CHAR_WIDTH * VCLCD_CHAR_HEIGHT));
    ASSERTDO(in_display,
             print_error("vclcd_cursor_seek: position %d exceeds expected range.\n", result);
             return -1);
    
    int in_range = (result <= vclcd->chars_len);
    ASSERTDO(in_range,
             print_info("vclcd_cursor_seek: cursor at the end of string. cannot go further.\n");
             return vclcd->curs_pos);
    
    _vclcd_draw_cursor(vclcd, vclcd->curs_pos, PIXEL_WHITE); /* remove cursor. */
    _vclcd_draw_cursor(vclcd, result, PIXEL_BLACK); /* redraw cursor. */
    
    return (vclcd->curs_pos = result);
}

/* Tested 190526 */
int vclcd_insert(struct vclcd *vclcd, char c) {
    ASSERTDO((vclcd != NULL), print_error("vclcd_insert: vclcd is null.\n"); return -1);
    ASSERTDO((font_index(c) != -1), print_error("vclcd_insert: invalid character: [%c].\n", c); return -1);
    
    ASSERTDO((vclcd->chars_len < VCLCD_ROWS * VCLCD_COLS), print_error("vclcd_insert: no more space!\n"); return -1);
    
    int cursor_on_char = (vclcd->curs_pos < vclcd->chars_len);
    int shift_needed = cursor_on_char;
    
    
    /****************************************
     * Graphic and data - shift, redraw
     * and apply it to data.
     ****************************************/
    if (shift_needed) {
        if (_vclcd_shift(vclcd, vclcd->curs_pos, vclcd->chars_len - vclcd->curs_pos, 1) == -1) {
            print_error("vclcd_insert: _vclcd_shift() failed.\n");
            return -1;
        }
    }
    
    
    /****************************************
     * Graphic - draw new character
     ****************************************/
    if (_vclcd_draw_char(vclcd, vclcd->curs_pos, c, COLOR_CHARACTER) == -1) {
        print_error("vclcd_insert: _vclcd_draw_char() failed.\n");
        return -1;
    }
    
    
    /****************************************
     * Data - assign character and
     * increase length if not updated by shift.
     ****************************************/
    if (!shift_needed) {
        /**
         * _vclcd_shift() increases char_len.
         * In case cursor is right after the last character, where shift does not happen,
         * we have to increase chars_len here.
         */
        vclcd->chars_len += 1;
    }
    
    vclcd->chars[vclcd->curs_pos] = c;
    
    return 0;
}

/* Tested 190526 */
int vclcd_delete(struct vclcd *vclcd) {
    ASSERTDO((vclcd != NULL), print_error("vclcd_delete: vclcd is null.\n"); return -1);

    int cursor_on_char = (vclcd->curs_pos < vclcd->chars_len);
    if (!cursor_on_char) {
        /**
         * Hahahahahahahahahhahahahahahahahah!!!
         */
        static bool black = true;
        _vclcd_clear(vclcd, COLOR_BACKGROUND, black ? PIXEL_BLACK : PIXEL_WHITE);
        _vclcd_draw_cursor(vclcd, 0, COLOR_CURSOR);
        black = !black;
        
        return 0; /* nothing to delete. */
    }
    int cursor_on_last_char = (vclcd->curs_pos + 1 == vclcd->chars_len);
    if (cursor_on_last_char) {
        /**
         * _vclcd_shift() removes data and redraw characters.
         * But without it we have to do it manually.
         */
        
        
        /****************************************
         * Graphic - erase character from LCD.
         ****************************************/
        if (_vclcd_draw_char(vclcd, vclcd->curs_pos, vclcd->chars[vclcd->curs_pos], COLOR_NONE) == -1) {
            print_error("vclcd_delete: _vclcd_draw_char() failed.\n");
            return -1;
        }
        
        
        /****************************************
         * Data - update data.
         ****************************************/
        vclcd->chars[vclcd->curs_pos] = '\0';
        vclcd->chars_len -= 1;
    }
    else {
        
        /****************************************
         * Graphic and data - shift.
         ****************************************/
        if (_vclcd_shift(vclcd, vclcd->curs_pos + 1, vclcd->chars_len - 1 - vclcd->curs_pos, -1) == -1) {
            print_error("vclcd_delete: _vclcd_shift() failed.\n");
            return -1;
        }
    }
    
    return 0;
}

/* Tested 190526 */
int vclcd_replace(struct vclcd *vclcd, char c) {
    ASSERTDO((vclcd != NULL), print_error("vclcd_replace: vclcd is null.\n"); return -1);
    ASSERTDO((font_index(c) != -1), print_error("vclcd_replace: invalid character: [%c].\n", c); return -1);

    /****************************************
     * Graphic
     ****************************************/
    if (_vclcd_draw_char(vclcd, vclcd->curs_pos, vclcd->chars[vclcd->curs_pos], COLOR_NONE) == -1) {
        print_error("vclcd_delete: _vclcd_draw_char() failed. clear failed.\n");
        return -1;
    }
    
    
    /****************************************
     * Data
     ****************************************/
    vclcd->chars[vclcd->curs_pos] = c;
    
    
    /****************************************
     * Graphic
     ****************************************/
    if (_vclcd_draw_char(vclcd, vclcd->curs_pos, vclcd->chars[vclcd->curs_pos], COLOR_CHARACTER) == -1) {
        print_error("vclcd_delete: _vclcd_draw_char() failed. redraw failed.\n");
        return -1;
    }
    
    return 0;
}

/* Tested 190526 */
int vclcd_is_full(struct vclcd *vclcd) {
    ASSERTDO((vclcd != NULL), print_error("vclcd_is_full: vclcd is null.\n"); return -1);

    return (vclcd->chars_len >= VCLCD_ROWS * VCLCD_COLS);
}

/* Tested 190526 */
void vclcd_dump(struct vclcd *vclcd) {
    ASSERTDO((vclcd != NULL), print_error("vclcd_dump: vclcd is null.\n"); return);

    for (int i = 0; i < vclcd->chars_len; ++i) {
        printf("[%c]", vclcd->chars[i]);
    }
    puts("");
    
}

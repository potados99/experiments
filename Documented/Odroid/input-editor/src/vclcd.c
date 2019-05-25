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

/*
 struct vclcd {
 
 bool        initialized;
 
 int         fd;
 uint16_t    *mem;
 
 char        chars[VCLCD_ROWS * VCLCD_COLS];
 int         chars_len;
 int         curs_pos;
 
 };
*/

/**
 * not all area of the LCD is used.
 * 10 * 8 characters are aligned center horizontally.
 * the left and right margin is 22 ( same as (320 - ((240 * 10) + (4 * 9))) / 2 )
 */
#define MARGIN                              22
#define ROW_INDEX(INDEX)                    (INDEX / VCLCD_COLS)
#define COL_INDEX(INDEX)                    (INDEX % VCLCD_COLS)
#define OFFSET_VERTICAL(AMOUNT)             ((VCLCD_WIDTH) * (AMOUNT))
#define OFFSET_HORIZONTAL(AMOUNT)           (AMOUNT)

/**
 * get address of top left point of the character area cur_pos is at.
 */
static inline int vclcd_offset(int cur_pos) {
    return  OFFSET_VERTICAL( (VCLCD_CHAR_HEIGHT + VCLCD_CHAR_PADDING) * ROW_INDEX(cur_pos) ) +
            OFFSET_HORIZONTAL( (VCLCD_CHAR_WIDTH + VCLCD_CHAR_PADDING) * COL_INDEX(cur_pos) ) +
            MARGIN;
}

/**
 * get address of bottom left point of the character area cur_pos is at.
 */
static inline int vclcd_offset_cursor(int cur_pos) {
    return vclcd_offset(cur_pos) + OFFSET_VERTICAL(VCLCD_CHAR_HEIGHT);
}

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

    return 0;
}

int vclcd_close(struct vclcd *vclcd) {
    ASSERTDO((vclcd != NULL), print_error("vclcd_close: vclcd is null.\n"); return -1);

    if (munmap(vclcd->mem, VCLCD_WIDTH * VCLCD_HEIGHT * sizeof(uint16_t))) {
        perror("munmap() failed");
        print_error("vclcd_close: munmap() failed.\n");
        return -1;
    }
    
    if (close(vclcd->fd)) {
        perror("close() failed");
        print_error("vclcd_close: close() failed.\n");
        return -1;
    }
    
    return 0;
}

void vclcd_clear(struct vclcd *vclcd) {
    ASSERTDO((vclcd != NULL), print_error("vclcd_clear: vclcd is null.\n"); return);

    for (int i = 0; i < VCLCD_WIDTH * VCLCD_HEIGHT; ++i) {
        *(vclcd->mem + i) = 0;
    }
}

int vclcd_read(struct vclcd *vclcd) {
    ASSERTDO((vclcd != NULL), print_error("vclcd_read: vclcd is null.\n"); return -1);
    
    return vclcd->chars[vclcd->curs_pos];
}

int vclcd_write(struct vclcd *vclcd, char c) {
    ASSERTDO((vclcd != NULL), print_error("vclcd_write: vclcd is null.\n"); return -1);
    
    int idx;
    if ((idx = font_index(c)) == -1) {
        print_error("vclcd_write: attempting to write wrong character.\n");
    }
    
    int font_row;
    int pixel_pos;
    for (int row = 0; row < VCLCD_CHAR_HEIGHT; ++row) {
        font_row = font[idx][row];
        pixel_pos = vclcd_offset(vclcd->curs_pos) + (VCLCD_WIDTH * row);
        
        for (int col = 0; col < VCLCD_CHAR_WIDTH; ++col) {
            *(vclcd->mem + pixel_pos + VCLCD_CHAR_WIDTH - 1 - col) = (font_row & 0x01);
            pixel_pos += 1;
            font_row >>= 1;
        }
    }
    
    vclcd->chars[vclcd->curs_pos] = c;
    
    return 0;
}

int vclcd_cursor_move(struct vclcd *vclcd, int delta) {
    return 0;

}

int vclcd_cursor_set(struct vclcd *vclcd, int offset) {
    return 0;

    
}

int vclcd_insert(struct vclcd *vclcd, char c) {
    return 0;

}

int vclcd_remove(struct vclcd *vclcd) {
    return 0;

}

int vclcd_replace(struct vclcd *vclcd, char c) {
    return 0;

}



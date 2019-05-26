#ifndef _VCLCD_H
#define _VCLCD_H

/**
 * Virtual Character LCD.
 *
 * Macros under must be declared:
 * VCLCD_WIDTH
 * VCLCD_HEIGHT
 * VCLCD_PIXEL_SIZE_BIT
 * VCLCD_PIXEL_RED_BIT
 * VCLCD_PIXEL_GREEN_BIT
 * VCLCD_PIXEL_BLUE_BIT
 * VCLCD_CHAR_WIDTH
 * VCLCD_CHAR_HEIGHT
 * VCLCD_CHAR_PADDING
 * VCLCD_COLS
 * VCLCD_ROWS
 */

#include "machine_specific.h"
#include <stdbool.h>
#include <stdint.h>

struct vclcd {
    bool        initialized;
    
    int         fd;
    uint16_t    *mem;
    
    char        chars[VCLCD_ROWS * VCLCD_COLS];
    int         chars_len;
    int         curs_pos;
};

/**
 * 24bit to 16bit.
 */
#define PIXEL(R, G, B)      ((uint16_t)(((R >> 3) << 11) | ((G >> 2) << 5) | (B >> 3)))

/**
 * Presets.
 */
#define PIXEL_BLACK         PIXEL(0, 0, 0)
#define PIXEL_WHITE         PIXEL(0xff, 0xff, 0xff)

/**
 * Initial works
 */
int vclcd_setup(struct vclcd *vclcd, const char *dev_path);

/**
 * Close connection to LCD.
 */
int vclcd_close(struct vclcd *vclcd);

/**
 * Clear all pixel.
 * @param pixel_center  specifies color to be filled in whole character area.
 * @param pixel_side    specifies color for others area without characters.
 */
int vclcd_clear(struct vclcd *vclcd, uint16_t pixel_center, uint16_t pixel_side);

/**
 * Read and return a character at cursor position of vclcd.
 */
int vclcd_read(struct vclcd *vclcd);

/**
 * Write a character to current cursor position of vclcd.
 */
int vclcd_write(struct vclcd *vclcd, char c, uint16_t pixel);


/**
 * Move cursor position.
 * lssek() style. :)
 */
int vclcd_seek(struct vclcd *vclcd, int offset, int whence);

/**
 * Insert a character at cursor position and shift right.
 */
int vclcd_insert(struct vclcd *vclcd, char c);

/**
 * Remove a character at cursor position and shift left.
 */
int vclcd_delete(struct vclcd *vclcd);

/**
 * Replace a character at cursor position.
 */
int vclcd_replace(struct vclcd *vclcd, char c);

#endif /* _VCLCD_H */

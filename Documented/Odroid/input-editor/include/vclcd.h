#ifndef _VCLCD_H
#define _VCLCD_H

/**
 * Virtual Character LCD.
 *
 * Supported features:
 * - write char
 * - shift chars
 * - insert & delete char
 * - move cursor
 *
 * Usage:
 *  * 1) Declare and allocate a variable of type struct vclcd.
 *    2) vclcd_setup(): variable init and hardware setup.
 *
 * Notice:
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
 * VCLCD_CURSOR_THICKNESS
 */

#include "machine_specific.h"
#include <stdbool.h>
#include <stdint.h>

struct vclcd {
    bool                                    initialized;
    
    int                                     fd;
    uint16_t                                *mem;
    
    char                                    chars[VCLCD_ROWS * VCLCD_COLS];
    int                                     chars_len;
    int                                     curs_pos;
};

/**
 * 24bit to 16bit.
 */
#define PIXEL(R, G, B)                      ((uint16_t)(((R >> 3) << 11) | ((G >> 2) << 5) | (B >> 3)))

/**
 * Presets.
 */
#define PIXEL_BLACK                         PIXEL(0x00, 0x00, 0x00)
#define PIXEL_WHITE                         PIXEL(0xff, 0xff, 0xff)
#define PIXEL_LIGHTGRAY                     PIXEL(0x8f, 0x8f, 0x8f)
#define PIXEL_DARKGRAY                      PIXEL(0x30, 0x30, 0x30)

/**
 * Colors.
 */
#define COLOR_BACKGROUND                    PIXEL_WHITE
#define COLOR_OUTSIDE                       PIXEL_BLACK
#define COLOR_NONE                          COLOR_BACKGROUND
#define COLOR_CHARACTER                     PIXEL_BLACK
#define COLOR_CURSOR                        PIXEL_DARKGRAY

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


/********************************************************************************
 * Internal functions.
 ********************************************************************************/

/**
 * Clear all pixel.
 * @param pixel_center  specifies color to be filled in whole character area.
 * @param pixel_side    specifies color for others area without characters.
 */
int _vclcd_clear(struct vclcd *vclcd, uint16_t pixel_center, uint16_t pixel_side);

/**
 * Write a character at position.
 */
int _vclcd_draw_char(struct vclcd *vclcd, int at, char c, uint16_t pixel);

/**
 * Draw a cursor at current cursor position.
 */
int _vclcd_draw_cursor(struct vclcd *vclcd, int at, uint16_t pixel);

/**
 * Shift characters.
 * Shift left will remove character, and right will add [space] character.
 * Cursor will not be affected.
 */
int _vclcd_shift(struct vclcd *vclcd, int start, int length, int offset);


/********************************************************************************
 * Public functions.
 ********************************************************************************/

/**
 * Initial works
 */
int vclcd_setup(struct vclcd *vclcd, const char *dev_path);

/**
 * Close connection to LCD.
 */
int vclcd_close(struct vclcd *vclcd);

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

/**
 * Check if full.
 */
int vclcd_is_full(struct vclcd *vclcd);

/**
 * Print content of vclcd.
 */
void vclcd_dump(struct vclcd *vclcd);

#endif /* _VCLCD_H */

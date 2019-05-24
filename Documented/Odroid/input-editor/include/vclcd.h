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

struct vclcd {
    char    *chars;
    int     chars_len;
    int     cursor;
};

/**
 * Initial works
 */
int vclcd_setup(struct vclcd *vclcd);

/**
 * Read and return a character at cursor position of vclcd.
 */
char vclcd_read(struct vclcd *vclcd);

/**
 * Write a character to current cursor position of vclcd.
 */
int vclcd_write(struct vclcd *vclcd, char c);

/**
 * Move cursor position of clcd.
 */
int vclcd_cursor_move(struct vclcd *vclcd, int delta);

/**
 * Set cursor position of clcd.
 */
int vclcd_cursor_set(struct vclcd *vclcd, int offset);

int vclcd_insert(struct vclcd *vclcd, char c);
int vclcd_remove(struct vclcd *vclcd);
int vclcd_replace(struct vclcd *vclcd, char c);

#endif /* _VCLCD_H */

#ifndef _MACHINE_SPECIFIC_H
#define _MACHINE_SPECIFIC_H

/**
  * Keypad connection.
  */
#define KEYPAD_0	13	/* R1 */
#define KEYPAD_1	14	/* R2 */
#define KEYPAD_2	6	/* R3 */
#define KEYPAD_3	10	/* R4 */
#define KEYPAD_4	21	/* C1 */
#define KEYPAD_5	22	/* C2 */
#define KEYPAD_6	23	/* C3 */
#define KEYPAD_7	24	/* C4 */

/**
  * Keypad scan delay.
  */
#define KEYPAD_SCAN_DELAY 1000

/**
 * LCD specification
 */
#define VCLCD_WIDTH             320
#define VCLCD_HEIGHT            240
#define VCLCD_PIXEL_SIZE_BIT    16
#define VCLCD_PIXEL_RED_BIT     5 /* pixel order is fixed to RGB. */
#define VCLCD_PIXEL_GREEN_BIT   6
#define VCLCD_PIXEL_BLUE_BIT    5
#define VCLCD_CHAR_WIDTH        24
#define VCLCD_CHAR_HEIGHT       24
#define VCLCD_CHAR_PADDING      4
#define VCLCD_COLS              10 /* 10 chars in a line. */
#define VCLCD_ROWS              8 /* 10 chars in a line. */
#define VCLCD_CURSOR_THICKNESS  2

#endif /* _MACHINE_SPECIFIC_H */

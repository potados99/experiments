#ifndef _CLCD_H
#define _CLCD_H

#define LCD_R_CMD	0
#define LCD_R_DATA 	1

extern int lcd_pins[];

/**
 * Trigger action for current GPIO output.
 */
void _lcd_apply();

/**
 * Write 4 bits to (D4..D7).
 */
void _lcd_write_nibble(unsigned char nibble);

/**
 * Write one byte. 
 * Write to (D4..D7) twice, 4 bits at once.
 */
void _lcd_write_byte(unsigned char byte);

/**
 * Select where to write data.
 * LCD_R_CMD or LCD_R_DATA.
 */
void _lcd_select_register(int r);





/**
 * Send a command to the CLCD.
 */
void lcd_put_cmd(unsigned char cmd);

/**
 * Send a single ascii character to CLCD.
 */
void lcd_put_char(char c);

/**
 * Write a line. NULL-terminate.
 */
void lcd_put_line(char *line);

/**
 * Setup pins.
 */
void lcd_init();

#endif /* _CLCD_H */

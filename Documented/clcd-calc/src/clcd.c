#include "clcd.h"
#include "pgpio.h"

#include <string.h>

int lcd_pins[] = {
	LCD_D4,
	LCD_D5,
	LCD_D6,
	LCD_D7,
	LCD_RS,
	LCD_EN
};

void _lcd_apply() {
	digital_write(LCD_EN, 1);
	udelay(100);
	digital_write(LCD_EN, 0);
	udelay(100);
}

void _lcd_write_nibble(unsigned char nibble) {
	for (register int i = 0; i < 4; ++i) {
		digital_write(lcd_pins[i], nibble & 0x01);
		nibble >>= 1;
	}
	_lcd_apply();
}

void _lcd_write_byte(unsigned char byte) {
	_lcd_write_nibble((byte >> 4) & 0x0f); /* high 4 */
	_lcd_write_nibble(byte & 0x0f); /* low 4 */
}

void _lcd_select_register(int r) {
	digital_write(LCD_RS, r);
}





void lcd_put_cmd(unsigned char cmd) {
	_lcd_select_register(LCD_R_CMD);
	_lcd_write_byte(cmd);
}

void lcd_put_char(char c) {
	_lcd_select_register(LCD_R_DATA);
	_lcd_write_byte(c);
}

void lcd_put_line(char *line) {
	int len = strlen(line);
	
	for (register int i = 0; i < len; ++i) {
		lcd_put_char(line[i]);
	}

	lcd_put_cmd(0xC0); /* linebreak */
}

void lcd_init() {
	gpio_setup();

	pinv_mode(lcd_pins, sizeof(lcd_pins)/sizeof(int), PGPIO_OUTPUT);
	digital_writev(lcd_pins, sizeof(lcd_pins)/sizeof(int), 0);

	udelay(35000);

	lcd_put_cmd(0x28);
	lcd_put_cmd(0x28);
	lcd_put_cmd(0x28);

	lcd_put_cmd(0x0e);
	lcd_put_cmd(0x02);
	
	udelay(3000);

	lcd_put_cmd(0x01);
	
	udelay(3000);
}

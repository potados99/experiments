#include "fnd.h"

#include <stdio.h>
#include <unistd.h>
#include <wiringPi.h>

/*
val  binary	 	hex
 0 	0011 1111	0x3F
 1	0000 0110	0x06
 2	0101 1011	0x5B
 3  	0100 1111	0x4F
 4  	0110 0110	0x66
 5	0110 1101	0x6D
 6	0111 1101	0x7D
 7	0000 0111	0x07
 8	0111 1111	0x7F
 9	0110 1111	0x6F
 A	0111 0111	0x77
 B	0111 1100	0x7C
 C	0111 1001	0x79
 D	0101 1110	0x5E
 E	0111 1011	0x7B
 F	0111 0001	0x71
 */

static int gpio_initialized = 0;

/**
  * Segment index is fixed.
  */
int digit_map[] = {
	0x3F, 0x06, 0x5B, 0x4F,
	0x66, 0x6D, 0x7D, 0x07,
	0x7F, 0x6F, 0x77, 0x7C,
	0x79, 0x5E, 0x7B, 0x71
};

/**
  * Defined in makefile.
  */
int gpio_map[] = {
	GPIO_SEG_0, /* segment 0 */ 
	GPIO_SEG_1, 
	GPIO_SEG_2, 
	GPIO_SEG_3, 
	GPIO_SEG_4, 
	GPIO_SEG_5, 
	GPIO_SEG_6  /* segment 6 */
};

void fnd_print_range(int start, int end, int interval_msec) {
	while(start <= end) {
		fnd_print_hex(start);

		if (start++ != end) 
			usleep(interval_msec * 1000);
	}
}

void fnd_print_hex(int val) {
	if (val < HEX_DIGIT_MIN || val > HEX_DIGIT_MAX) 
		return;

	fnd_control_segments(digit_map[val]);
}

void fnd_control_segments(int segment_bits) {
	if (segment_bits < ALL_SEGMENTS_OFF || segment_bits > ALL_SEGMENTS_ON) 
		return;

	int pos = 0;

	while (pos < FND_SEGMENTS) {
		fnd_set_segment(pos, (segment_bits & 0x01));

		pos += 1;
		segment_bits >>= 1;
	}
}

void fnd_set_segment(int segment_index, int val) {
	if (segment_index < 0 || segment_index > FND_SEGMENTS - 1) 
		return;
	
	if (gpio_initialized) {
		digitalWrite(gpio_map[segment_index], val ? HIGH : LOW);
	}
	else {
		puts("GPIO not initialized!");
	}
}

void fnd_init_gpio() {
	wiringPiSetup();

	for (int i = 0; i < FND_SEGMENTS; ++i) {
		pinMode(gpio_map[i], OUTPUT);
	}

	gpio_initialized = 1;
}

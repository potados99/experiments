#ifndef _PGPIO_H
#define _PGPIO_H

/**
 * Potados wiringPi wrapper.
 */

#include <wiringPi.h>

#define GPIO_OUT OUTPUT
#define GPIO_IN INPUT

#define ASSERT(X) 				\
	do {					\
		if (!(X))	return;		\
	} while(0)

void gpio_setup();

void pin_mode(int pin, int mode);

void pinv_mode(int pinv[], int pinc, int mode);

void dwrite(int pin, int value);

void dwritev(int pinv[], int pinc, int value);

void udelay(int usec);

#endif /* _PGIO_H */

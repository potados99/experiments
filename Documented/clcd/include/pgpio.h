#ifndef _PGPIO_H
#define _PGPIO_H

/**
 * Potados wiringPi wrapper.
 */

#define ASSERT(X) 				\
	do {					\
		if (!(X))	return;		\
	} while(0)

void gpio_setup();

void pin_mode(int pin, int mode);

void pinv_mode(int pinv[], int pinc, int mode);

void dwrite(int pin, int value);

#endif /* _PGIO_H */

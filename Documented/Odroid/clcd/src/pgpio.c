#include "pgpio.h"

#include <stdio.h>
#include <stdbool.h>
#include <wiringPi.h>

static bool initialized; 

static inline bool check_init() {
	if (!initialized) {
		fprintf(stderr, "wiringPi not setup.\n");
		return false;
	}
	else return true;
}

void gpio_setup() {
	wiringPiSetup();
	initialized = true;
}

void pin_mode(int pin, int mode) {
	ASSERT(check_init());

	pinMode(pin, mode);
}

void pinv_mode(int pinv[], int pinc, int mode) {
	ASSERT(check_init());

	for (register int i = 0; i < pinc; ++i) {
		pin_mode(pinv[i], mode);
	}
}

void dwrite(int pin, int value) {
#if (VERBOSE > 0)
	printf("Writing to pin: %d, with value: %d.\n", pin, value);
#endif
	digitalWrite(pin, value);
}

void dwritev(int pinv[], int pinc, int value) {
	for (register int i = 0; i < pinc; ++i) {
		dwrite(pinv[i], value);
	}
}

void udelay(int usec) {
	delayMicroseconds(usec);
}

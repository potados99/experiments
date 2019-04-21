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
	Assert(check_init());

	for (int i = 0; i < pinc; ++i) {
		pinMode(pinv[i], mode);
	}
}

void dwrite(int pin, int value) {
	digitalWrite(pin, value);
}



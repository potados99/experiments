#ifndef _PGPIO_H
#define _PGPIO_H

/**
 * Potados wiringPi wrapper.
 */

#include <stdio.h>
#include <stdbool.h>

#ifdef DEBUG
#include <unistd.h>
static inline void wiringPiSetup() { printf("wiringPiSetup()\n"); }
static inline void pinMode(int pin, int mode) { printf("pinMode(%d, %d)\n", pin, mode); }
static inline void pullUpDnControl(int pin, int mode) { printf("pullUpDnControl(%d, %d)\n", pin, mode); }
static inline void digitalWrite(int pin, int val) { printf("digitalWrite(%d, %d)\n", pin, val); }
static inline int digitalRead(int pin) {  printf("digitalRead(%d)\n", pin); return 0; }
static inline void delayMicroseconds(int msec) { printf("delayMicroseconds(%d)\n", msec); usleep(msec); }
#define INPUT 0x10
#define OUTPUT 0x20
#define LOW 0
#define HIGH 1
#define PUD_UP 0x50
#define PUD_DN 0x60
#else
#include <wiringPi.h> /* not use when debugging */
#endif

#include "pgpio.h"
#include "macros.h"
#include "verbose.h"

#define PGPIO_INPUT INPUT
#define PGPIO_OUTPUT OUTPUT
#define PGPIO_INPUT_PULLUP 0x99

#define PGPIO_LOW LOW
#define PGPIO_HIGH HIGH

static bool initialized; 

/**
  * Check if GPIO control is available.
  */
static inline bool check_init() {
	if (!initialized) {
		print_info("wiringPi is not initialized.\n");
		
		return false;
	} else {
		return true;
	}	
}

/**
  * Do initial things for GPIO.
  */
static inline void gpio_setup() {
	wiringPiSetup();
	initialized = true;

	print_info("wiringPi setup.\n");
}

/**
  * Set pin mode. 
  * 
  * PGPIO_INPUT_PULLUP is an alias for "set pinMode to INPUT and pud to PUD_UP."
  */
static inline void pin_mode(int pin, int mode) {
	ASSERTDO(check_init(), return);

	if (mode == PGPIO_INPUT_PULLUP) {
		pinMode(pin, PGPIO_INPUT);
		pullUpDnControl(pin, PUD_UP);
		
		print_trace("setting pin %d to input_pullup.\n", pin);
	} else {
		pinMode(pin, mode);
		
		print_trace("setting pin %d to mode %d.\n", pin, mode);
	}
}

/**
  * Set a single pin mode to multiple pins.
  */
static inline void pinv_mode(int pinv[], int pinc, int mode) {
	ASSERTDO(check_init(), return);

	for (register int i = 0; i < pinc; ++i) {
		pin_mode(pinv[i], mode);
	}
}

/**
  * Digital write to pin.
  */
static inline void digital_write(int pin, int value) {
	ASSERTDO(check_init(), return);

	digitalWrite(pin, value);
	print_trace("wrote to pin: %d, with value: %d.\n", pin, value);
}

/**
  * Digital write one value to multiple pins.
  */
static inline void digital_writev(int pinv[], int pinc, int value) {
	for (register int i = 0; i < pinc; ++i) {
		digital_write(pinv[i], value);
	}
}

/*
 * Digital read a pin.
 */
static inline int digital_read(int pin) {
	return digitalRead(pin);
}

/**
  * Delay for usec microseconds.
  */
static inline void udelay(int usec) {
	delayMicroseconds(usec);
}

#endif /* _PGIO_H */


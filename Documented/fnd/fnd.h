#ifndef fnd_h
#define fnd_h

#define HEX_DIGIT_MIN 		0x00
#define HEX_DIGIT_MAX 		0x0F

#define FND_SEGMENTS 		7
#define ALL_SEGMENTS_ON 	0x7F
#define ALL_SEGMENTS_OFF 	0x00

/**
  * Map segment index to physical GPIO pin number.
  * Actual value will be filled by Makefile.
  */
extern int 			gpio_map[];

/**
  * Map single digit hex number to segment control bits.
  */
extern int 			digit_map[];

/**
  * Print hex number range.
  * For all number printed x it is true that x >= start and x <= end.

  * @param interval_msec	Interval between prints, in millisecond.
  */
void 				fnd_print_range(int start, int end, int interval_msec);

/** 
  * Print single hex number.
  */
void 				fnd_print_hex(int val);

/**
  * Set segments.
  * Each position of bits indicates segment index.
  * 1 bit turns on, 0 bit turns off.
  */
void 				fnd_control_segments(int segment_bits);

/**
  * Set a single segment to value.
  */
void				fnd_set_segment(int segment, int val);

#endif /* fnd_h */

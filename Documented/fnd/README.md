# FND control

## Usage
~~~
App mode [argument]
~~~
Mode:
	1:	print single digit of hex number from 0 to F.
	2:	turn on segments specified by each bits of argument.

Argument:
	Hexadecimal representation of sum of bits refering to each segments.

## Compile Options

In Makefile, modify "VERBOSE" or "GPIO_PIN".

When "VERBOSE" is set to more than zero, the number and/or the segments are printed.

Number of "GPIO_PIN" MUST be same as the number of segments, which is 7.

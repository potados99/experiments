# FND Makefile.

TARGET = App

CC = gcc
CFLAGS = -Wall -std=c11
LFLAGS = -lwiringPi


############## MODIFY ME ################
# Odroid pin: 98 99 118 103 97 108 100
GPIO_PIN = 27 26 11 6 24 23 22

VERBOSE = 1
#########################################


SEG_INDEX = $(shell seq 0 6)
MACROS_KEY = $(foreach index, $(SEG_INDEX), -DGPIO_SEG_$(index)=)
MACROS = $(join $(MACROS_KEY), $(GPIO_PIN)) -DVERBOSE=$(VERBOSE)

SOURCE = $(wildcard *.c)
OBJECT = $(SOURCE:.c=.o)

$(TARGET): $(OBJECT)
	$(LINK.c) $(LFLAGS) -o $@ $^

%.o: %.c
	$(COMPILE.c) $(MACROS) $<

clean:
	rm *.o $(TARGET)*

# FND Makefile.

TARGET = App

CC = gcc
CFLAGS = -Wall -std=c11
LFLAGS = -lwiringPi


############## MODIFY ME ################
# Odroid pin: 103 118 99 98 100 108 97
GPIO_PIN = 6 11 26 27 22 23 24
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

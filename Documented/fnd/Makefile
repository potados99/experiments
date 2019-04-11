# FND Makefile.

TARGET = App

CC = gcc
CFLAGS = -Wall
LFLAGS = -lwiringPi


############ MODIFY ME ###########
GPIO_PIN = 12 13 14 15 16 17 18
VERBOSE = 1
##################################


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

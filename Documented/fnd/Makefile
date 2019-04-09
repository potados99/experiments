# Makefile boilerplate version 0.0.1 (20190204)

TARGET = App

CC = gcc
CFLAGS = -Wall

############ MODIFY ME ###########
GPIO_PIN = 12 24 36 48 56 73 81
##################################

SEG_INDEX = $(shell seq 0 6)
MACROS_KEY = $(foreach index, $(SEG_INDEX), -DGPIO_SEG_$(index)=)
MACROS = $(join $(MACROS_KEY), $(GPIO_PIN))

SOURCE = $(wildcard *.c)
OBJECT = $(SOURCE:.c=.o)

$(TARGET): $(OBJECT)
	$(LINK.c) -o $@ $^

%.o: %.c
	$(COMPILE.c) $(MACROS) $<

clean:
	rm *.o $(TARGET)*

# 201701562 Song Byeong Jun

TARGET = necho

CC = gcc
CFLAGS = -Wall

SOURCE = $(wildcard *.c)
OBJECT = $(SOURCE:.c=.o)

$(TARGET): $(OBJECT)
	$(LINK.c) -o $@ $^

# Object file wildcard rule.
%.o: %.c
	$(COMPILE.c) $<

clean:
	rm *.o $(TARGET)*


TARGET = cp
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

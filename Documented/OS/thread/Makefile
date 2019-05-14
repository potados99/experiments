TARGET = thread
CC = gcc
LFLAGS = -lpthread

SOURCE = $(wildcard *.c)
OBJECT = $(SOURCE:.c=.o)

$(TARGET): $(OBJECT)
	$(CC) -o $@ $< $(LFLAGS)

%.o: %.c
	$(CC) -c -o $@ $<

clean:
	rm *.o $(TARGET)

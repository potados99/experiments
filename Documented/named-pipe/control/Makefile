CC = gcc
CFLAGS = -Wall -O3 -I./../lib
TARGET = control
BIN = /usr/bin

$(TARGET) : *.c ./../lib/*.c
	$(CC) $(CFLAGS) -o $(TARGET) *.c ./../lib/*.c
	sudo mv $(TARGET) $(BIN)/

clean:
	rm $(BIN)/$(TARGET)

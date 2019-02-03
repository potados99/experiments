CC = gcc
TARGET = strcpy
FLASG = -Wall

$(TARGET): main.o pstring.o
	$(CC) -o $(TARGET) main.o pstring.o

main.o: main.c
	$(CC) -c main.c

pstring.o: pstring.c
	$(CC) -c pstring.c

clean:
	rm *.o $(TARGET)


TARGET = gdbtest
CC = gcc
FLAGS = -g

$(TARGET) : main.o
	$(CC) -o $(TARGET) main.o $(FLAGS)

main.o : main.c
	$(CC) -o main.o -c main.c $(FLAGS)

clean :
	if [ -f $(TARGET) ]; then rm $(TARGET); echo "Target removed."; fi

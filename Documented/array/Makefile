TARGET = array
CC = gcc
FLAGS = -g

$(TARGET) : main.o analysis.o
	$(CC) -o $(TARGET) main.o analysis.o $(FLAGS)

main.o : main.c
	$(CC) -o main.o -c main.c $(FLAGS)

analysis.o : analysis.c
	$(CC) -o analysis.o -c analysis.c $(FLAGS)

clean :
	if [ -f $(TARGET) ]; then rm $(TARGET) *.o; echo "Target removed."; fi

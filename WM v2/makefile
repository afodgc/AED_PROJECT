CC = gcc
TARGET = wrdmttns
FLAGS = -Wall -std=c99 -O3 
ARGS = 

all:
	$(CC) $(FLAGS) -o $(TARGET) main.c arguments.c problem.c dicionario.c

clean:
	rm -rf *.o

valgrind:
	 valgrind --leak-check=full ./wrdmttns ${ARGS}
CC = gcc
TARGET = wrdmttns
FLAGS = -g -Wall
ARGS = teste.dict dandaan.pals

all:
	$(CC) $(FLAGS) -o $(TARGET) main.c arguments.c

clean:
	rm -rf *.o

valgrind:
	 valgrind --leak-check=full ./wrdmttns ${ARGS}
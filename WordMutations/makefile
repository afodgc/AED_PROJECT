CC = gcc
TARGET = wrdmttns
FLAGS = -Wall -std=c99 -g -pg
ARGS = 

all:
	$(CC) $(FLAGS) -o $(TARGET) main.c arguments.c problem.c dicionario.c graph.c dijkstra.c -lm

clean:
	rm -rf *.o


CC = gcc
TARGET = wrdmttns
FLAGS = -Wall -std=c99 -O3
ARGS = 

all:
	$(CC) $(FLAGS) -o $(TARGET) main.c arguments.c problem.c dicionario.c graph.c dijkstra.c -lm

FILES = $(shell ls test/Gracolas/*.pals)

testes:
	for F in ${FILES}; do ./wrdmttns test/portugues.dict $${F} ; done;
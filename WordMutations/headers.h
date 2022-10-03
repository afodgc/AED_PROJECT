#ifndef HEADERS_H_INCLUDED
#define HEADERS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STR 30

typedef struct _problem
{
    char starting_word[MAX_STR];
    char arrival_word[MAX_STR];
    int game_mode;
    struct _problem *next;
} problem;

char *get_arguments(int argc, char **argv, char *file_name, char extension[]);

problem *readProblemFile(char *file_pals, problem *head);
void freeProblem(problem *head);

void quicksort(char **dicionario, int first, int last);
void swapWords(char *first, char *second);

#endif
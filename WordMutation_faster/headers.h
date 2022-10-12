#ifndef HEADERS_H_INCLUDED
#define HEADERS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STR 100
#include "dicionario.h" //pode-se fazer isto???

typedef struct
{
    char starting_word[MAX_STR];
    char arrival_word[MAX_STR];
    int game_mode;
} problem;

char *get_arguments(int argc, char **argv, char *file_name, char extension[]);
FILE *openFile(char *file_pals, char *mode);
int checkIfFileExists(char *file_name);

void solveProblem(dict *dict_head, char *file_out_sem_extencao, char *file_pals);
void gameMode1(dict *dict_head, problem problem, FILE *file_out, int problem_word_size);
void gameMode2(dict *dict_head, problem problem, FILE *file_out, int problem_word_size);

#endif
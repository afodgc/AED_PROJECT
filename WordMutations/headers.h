#ifndef HEADERS_H_INCLUDED
#define HEADERS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STR 100
#include "dicionario.h" //pode-se fazer isto???
#include "graph.h"

typedef struct
{
    char starting_word[MAX_STR];
    char arrival_word[MAX_STR];
    int numOfmutations;
} problem;

char *get_arguments(int argc, char **argv, char *file_name, char extension[]);
FILE *openFile(char *file_pals, char *mode);
int checkIfFileExists(char *file_name);

void solveProblem(dict *dict_head, char *name_of_output_file, char *file_pals);

char *createOutput(char *name);
int checkIfProblemIsWellDef(dict *dict_head, problem problem, FILE *fpout, int *startWordIndex, int *destWordIndex, int *numOfVertices, int printResult);

void printResposta(Caminho resultado, int origem, int destino, FILE *output, problem problem, dict *dict_head);
void printR(Caminho resultado, int origem, int destino, FILE *output, problem problem, dict *dict_head);

#endif
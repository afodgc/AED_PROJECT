#ifndef DICIONARIO_H_INCLUDED
#define DICIONARIO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _dict
{
    char **table;
    int table_size;
    int word_size;
    struct _dict *next;
} dict;

void quicksort(char **dicionario, int first, int last);
void swapWords(char *first, char *second);

int *contadorDePalvaras(FILE *file_dict);
dict *dict_init(char *file_dict_name);

#endif
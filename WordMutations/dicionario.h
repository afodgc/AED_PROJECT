#ifndef DICIONARIO_H_INCLUDED
#define DICIONARIO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LEN_WORDS 100

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
dict *aloc_dict(int *numOfWordsPerSize, dict *head);
dict *aloc_dict_words(dict *head, FILE *fp_dict);
void freeDict(dict *head);
int binaryScr(char **table, int low, int high, char *palavra);

#endif
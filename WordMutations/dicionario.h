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

int binaryScr(char **table, int low, int high, char *palavra);

int *contadorDePalvarasDict(FILE *file_dict, int *);
int *contadorDePalvarasInput(FILE *file_pals, int *wordsInInput);
dict *dict_init(char *file_dict_name, char *file_pals);
dict *aloc_dict(int *numOfWordsPerSize, dict *head, int *wordsInInput);
dict *aloc_dict_words(dict *head, FILE *fp_dict, int *wordsInInput);
void freeDict(dict *head);

#endif
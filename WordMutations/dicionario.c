#include "dicionario.h"
#include "headers.h"

#define MAX_lEN_WORDS 100

/******************************************************
 * quicksort()
 *
 * argumets:
 *          char **dicionario: dicionario de palavras com o mesmo tamanho
 *          int first:         indexe primeiro elemento do dicionario
 *          int last:          indexe ultimo elemnto do dicionario
 *
 * return: void
 *
 * side efects: ordena as palavras de um dicionario com palavras do mesmo tamanho
 *****************************************************/
void quicksort(char **dicionario, int first, int last)
{
   int i, j, pivot;

   if (first < last)
   {
      pivot = first;
      i = first;
      j = last;
      while (i < j)
      {
         while ((strcmp(dicionario[i], dicionario[pivot]) <= 0) && i < last)
            i++;
         while (strcmp(dicionario[j], dicionario[pivot]) > 0)
            j--;
         if (i < j)
         {
            swapWords(dicionario[i], dicionario[j]);
         }
      }
      swapWords(dicionario[pivot], dicionario[j]);
      quicksort(dicionario, first, j - 1);
      quicksort(dicionario, j + 1, last);
   }
}

/******************************************************
 * quicksort()
 *
 * argumets:
 *          char *first:  palavra que vai ser trocada
 *          char *second: palavra que vai ser trocada
 *
 * return: void
 *
 * side efects: troca duas palavras de uma tabela de palavras
 *****************************************************/
void swapWords(char *first, char *second)
{
   char temp[100];

   strcpy(temp, first);
   strcpy(first, second);
   strcpy(second, temp);

   return;
}

/**************************************************************************************************
 * contadorDePalvaras()
 *
 * argumets:
 *          FILE *file_dict:  ponteiro para o ficheiro com o dicionário
 *
 * return: int *numeroPalavrasPorTamanho: contem o numero de palavras para cada tamanho de palavra,
 *                                        sendo o indice igual ao tamanho das palavras contadas
 *
 * side efects: numeroPalavrasPorTamanho alocado (deverá ser libertado posteriormente)
 *************************************************************************************************/
int *contadorDePalvaras(FILE *file_dict)
{
   int *numeroPalavrasPorTamanho = NULL, tamanho;
   char temporario[100];

   numeroPalavrasPorTamanho = (int *)calloc(MAX_lEN_WORDS, sizeof(int));

   // lé todas as palavras do ficheiro e contas por tamanho
   while (fscanf(file_dict, "%s", temporario) == 1)
   {
      tamanho = strlen(temporario);
      numeroPalavrasPorTamanho[tamanho]++;
   }

   fseek(file_dict, 0, SEEK_SET); // mete o ponteiro do ficheiro a apontar para o inicio od ficheiro

   return numeroPalavrasPorTamanho;
}

/********************************************************************************************
 * dict_init()
 *
 * argumets:
 *          char *file_dict_name:  nome do ficheiro de dicionário
 *
 * return: dict *: cabeça de lista de tabelas de palavras
 *
 * side efects: retorna o dicionário numa extrotura de dados
 ********************************************************************************************/
dict *dict_init(char *file_dict_name)
{
   FILE *fp_dict = NULL;
   int *numOfWordsPerSize = NULL;
   dict *head = NULL;

   fp_dict = openFile(file_dict_name, "r");

   numOfWordsPerSize = contadorDePalvaras(fp_dict);

   head = aloc_dict(numOfWordsPerSize, head);

   free(numOfWordsPerSize);
   fclose(fp_dict);

   return head;
}

/****************************************
 * aloc_dict()
 *
 *
 ****************************************/
dict *aloc_dict(int *numOfWordsPerSize, dict *head)
{
   dict *d, *aux;

   for (int index = 0; index < MAX_lEN_WORDS; index++)
   {
      if (numOfWordsPerSize[index] != 0)
      {
         if (head == NULL)
         {
            d = (dict *)malloc(sizeof(dict));

            if (d == NULL)
               exit(0);

            d->next = NULL;
            d->table_size = numOfWordsPerSize[index];
            d->word_size = index;
            d->table = (char **)malloc(d->table_size * sizeof(char *));
            if (d->table == NULL)
               exit(0);
            head = d;
         }
         else
         {
            aux = d;
            d = (dict *)malloc(sizeof(dict));
            if (d == NULL)
               exit(0);
            aux->next = d;
            d->next = NULL;
            d->table_size = numOfWordsPerSize[index];
            d->word_size = index;
            d->table = (char **)malloc(d->table_size * sizeof(char *));
            if (d->table == NULL)
               exit(0);
         }
      }
   }
   return head;
}

void freeDict(dict *head)
{
   // Desalocar as proprias structs e as tabelas!!
}
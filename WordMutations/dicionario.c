#include "dicionario.h"
#include "headers.h"

/*******************************************************************************
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
 ********************************************************************************/
void quicksort(char **dicionario, int first, int last)
{
   int i, j, pivot;
   char *tmp;

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
            tmp = dicionario[i];
            dicionario[i] = dicionario[j];
            dicionario[j] = tmp;
            // swapWords(dicionario[i], dicionario[j]);
         }
      }
      if (pivot != j)
      {
         tmp = dicionario[pivot];
         dicionario[pivot] = dicionario[j];
         dicionario[j] = tmp;
      }
      // swapWords(dicionario[pivot], dicionario[j]);
      quicksort(dicionario, first, j - 1);
      quicksort(dicionario, j + 1, last);
   }
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
int *contadorDePalvarasDict(FILE *file_dict, int *numeroPalavrasPorTamanho)
{
   int tamanho;
   char temporario[MAX_LEN_WORDS];

   numeroPalavrasPorTamanho = (int *)calloc(MAX_LEN_WORDS, sizeof(int));

   // lé todas as palavras do ficheiro e contas por tamanho
   while (fscanf(file_dict, "%s", temporario) == 1)
   {
      tamanho = strlen(temporario);
      numeroPalavrasPorTamanho[tamanho]++;
   }

   fseek(file_dict, 0, SEEK_SET); // mete o ponteiro do ficheiro a apontar para o inicio do ficheiro

   return numeroPalavrasPorTamanho;
}

int *contadorDePalvarasInput(FILE *file_pals, int *wordsInInput)
{
   char temporario[MAX_LEN_WORDS], temporario2[MAX_LEN_WORDS];
   int x = 0;

   wordsInInput = (int *)calloc(MAX_LEN_WORDS, sizeof(int));
   // ver os tamanhos das palavras dos problemas, para sabermos que dicts temos de alocar
   while (fscanf(file_pals, "%s %s %d", temporario, temporario2, &x) == 3)
   {
      if (strlen(temporario) == strlen(temporario2))
      {
         wordsInInput[strlen(temporario)] = 1;
      }
   }

   return wordsInInput;
}
/********************************************************************************************
 * dict_init()
 *
 * argumets:
 *          char *file_dict_name:  nome do ficheiro de dicionário
 *
 * return: dict *: cabeça de lista de tabelas de palavras
 *
 * side efects: retorna o dicionário numa estrutura de dados
 ********************************************************************************************/
dict *dict_init(char *file_dict_name, char *file_pals)
{
   FILE *fp_dict = NULL, *fp_pals = NULL;
   int *numOfWordsPerSize = NULL, *wordsInInput = NULL;
   dict *head = NULL, *aux_head = NULL;

   // abrir ficheiros
   fp_dict = openFile(file_dict_name, "r");
   fp_pals = openFile(file_pals, "r");

   numOfWordsPerSize = contadorDePalvarasDict(fp_dict, numOfWordsPerSize);
   wordsInInput = contadorDePalvarasInput(fp_pals, wordsInInput);

   head = aloc_dict(numOfWordsPerSize, head, wordsInInput);
   head = aloc_dict_words(head, fp_dict, wordsInInput);

   aux_head = head;

   while (aux_head != NULL)
   {
      quicksort(aux_head->table, 0, aux_head->table_size - 1); // ordenação
      aux_head = aux_head->next;
   }

   free(numOfWordsPerSize);
   free(wordsInInput);
   fclose(fp_dict);
   fclose(fp_pals);

   return head;
}

/**********************************************************************************
 * aloc_dict()
 *
 * arguments:
 *           int *numOfWordsPerSize: vetor com o numero de palavras por tamanho
 *           dict *head:             ponteiro para a cabeça de lista do dicionário
 *
 * return:   dict *head: retorna a cabeça da lista
 *
 * side efects: aloca a memoria necessaria para todas as tabelas de palavras
 *********************************************************************************/
dict *aloc_dict(int *numOfWordsPerSize, dict *head, int *wordsInInput)
{
   dict *d = NULL, *aux = NULL;

   for (int index = 0; index < MAX_LEN_WORDS; index++)
   {
      if (numOfWordsPerSize[index] != 0 && wordsInInput[index] == 1)
      {
         if (head == NULL)
         {
            d = (dict *)malloc(sizeof(dict));

            if (d == NULL)
               exit(0);

            d->next = NULL;
            d->table_size = 0;
            d->word_size = index;
            d->table = (char **)malloc(numOfWordsPerSize[index] * sizeof(char *));
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
            d->table_size = 0;
            d->word_size = index;
            d->table = (char **)malloc(numOfWordsPerSize[index] * sizeof(char *));
            if (d->table == NULL)
               exit(0);
         }
      }
   }
   return head;
}

/*********************************************************************************************
 * aloc_dict_words()
 *
 * arguments:
 *            dict *head:    cabeça da lista de tabelas do dicionário
 *            FILE *fp_dict: ficheiro do dicionário já aberto
 *
 * return: retorna a cabeça da lista do dicionário
 *
 * side efects: aloca espaço para as palavras e preenche as tabelas de palavras do dicionário
 **********************************************************************************************/
dict *aloc_dict_words(dict *head, FILE *fp_dict, int *wordsInInput)
{
   char word[MAX_LEN_WORDS];
   int word_size = 0;
   dict *aux_head = NULL;

   while ((fscanf(fp_dict, "%s", word)) == 1)
   {
      aux_head = head;
      word_size = strlen(word);
      // so podemos alocar esta palavra se tivermos criado um no na lista para este tamanho
      if (wordsInInput[word_size] == 1)
      {
         // temos de encontrar a lista que tenha o tamanho destas palavras
         while (aux_head->word_size != word_size)
         {
            aux_head = aux_head->next;
         }

         // a lista que queremos alterar está em aux_head
         aux_head->table[aux_head->table_size] = (char *)malloc(sizeof(char) * (word_size + 1));
         if (aux_head->table[aux_head->table_size] == NULL)
            exit(0);

         strcpy(aux_head->table[aux_head->table_size], word);
         (aux_head->table_size)++;
      }
   }

   return head;
}

/**************************************************************
 * freeDict()
 *
 * argumets:
 *           dict *head: cabeça da lista de tabelas de dicionários
 * return: void
 *
 * side efects: dá free a lista de tabelas do dicionário
 *****************************************************************/
void freeDict(dict *head)
{
   dict *aux_head = NULL, *temp = NULL;
   aux_head = head;
   while (aux_head != NULL)
   {
      for (int i = 0; i < aux_head->table_size; i++)
      {
         free(aux_head->table[i]);
      }
      free(aux_head->table);
      temp = aux_head;
      aux_head = temp->next;
      free(temp);
   }
}

/**************************************************
 * binaryScr()
 *
 * arguments:
 *          int low:       index do menor elemento
 *          int high:      index do maior elemento
 *          char *palavra: palavra a ser encontrada
 *
 * return: retorna -1 se não encontrar a palavra ou o index da palavra se a encontrar
 *
 * side efects: função que procura o index de uma palavra numa tablea ordenada alfabeticamente
 *************************************************/
int binaryScr(char **table, int low, int high, char *palavra)
{
   int mid, cmp; // valor médio entre  low e o high

   if (high >= low)
   {
      mid = low + (high - low) / 2;
      cmp = strcmp(table[mid], palavra);

      // se encontrar a palavra retorna o index
      if (cmp == 0)
         return mid;

      // se a palavra estiver mais à frente por ordem alfabética, vai procurar na metade mais à frente do meio
      if (cmp > 0)
         return binaryScr(table, low, mid - 1, palavra);
      // se a palavra estiver mais para trás por ordem alfabética, vai procurar na metade à trás fo meio
      else
         return binaryScr(table, mid + 1, high, palavra);
   }
   return -1;
}

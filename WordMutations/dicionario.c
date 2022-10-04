#include "dicionario.h"


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
void quicksort(char **dicionario,int first,int last){
   int i, j, pivot;

   if(first<last){
      pivot=first;
      i=first;
      j=last;
      while(i<j){
         while((strcmp(dicionario[i],dicionario[pivot]) <= 0) && i<last) 
         i++;
         while(strcmp(dicionario[j],dicionario[pivot]) > 0) 
         j--;
         if(i<j){
            swapWords(dicionario[i], dicionario[j]);
         }
      }
      swapWords(dicionario[pivot], dicionario[j]);
      quicksort(dicionario,first,j-1);
      quicksort(dicionario,j+1,last);
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
void swapWords(char *first, char *second){
    char temp[100];

    strcpy(temp, first);
    strcpy(first, second);
    strcpy(second, temp);

    return;
}
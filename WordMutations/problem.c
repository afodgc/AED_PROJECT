#include "headers.h"
#include "dicionario.h"
#include "graph.h"

/********************************************************************
 * openFile()
 * argumets:
 *          char *file_pals: nome do ficheiro que se pretende abrir
 *          char *mode:      modo de abertura do ficheiro
 *
 * return:  FILE *fp:        ponteiro para o ficheiro que foi aberto
 *
 * side efects: abre o ficheiro e verifica se aabertura foi bem feita
 *******************************************************************/
FILE *openFile(char *file_pals, char *mode)
{
    FILE *fp;
    fp = fopen(file_pals, mode);

    if (fp == NULL)
    {
        // funçao que dê free em tudo
        exit(0);
    }

    return fp;
}

/* -------TO-DO------- solve problem*/

// while existir problemas para resolver
// verificar se as palavras tem o mesmo tamanho
// no inicio verificar se as palavras existem no dicionário
// algoritmo de procura do caminho mais cuto
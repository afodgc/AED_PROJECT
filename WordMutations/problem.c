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

void solveProblem(dict *dict_head, char *name_of_output_file, char *file_pals)
{
    problem problem;
    FILE *fpIn = NULL, *fpOut = NULL;

    char *file_out = createOutput(name_of_output_file);

    fpIn = openFile(file_pals, "r");
    fpOut = openFile(file_out, "w");

    while ((fscanf(fpIn, "%s %s %d", problem.starting_word, problem.arrival_word, problem.numOfmutations)) == 3)
    {
        checkIfProblemIsWellDef(dict_head, problem, fpOut);
    }

    fclose(fpIn);
    fclose(fpOut);
}

// criar nome do ficheiro de saida
char *createOutput(char *name)
{
    char *file_out = (char *)malloc(sizeof(char) * (strlen(name) + strlen(".paths") + 1));
    if (file_out == NULL)
    {
        exit(0);
    }

    strcpy(file_out, name);
    strcat(file_out, ".paths");

    return file_out;
}

void checkIfProblemIsWellDef(dict *dict_head, problem problem, FILE *fpout)
{
    int startWordSize = 0, destWordSize = 0;
}
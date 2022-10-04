#include "headers.h"

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

void freeProblem(problem *head)
{
    problem *aux;

    while (head != NULL)
    {
        aux = head;
        // printf("%s %s %d\n", head->starting_word, head->arrival_word, head->game_mode);
        head = aux->next;
        free(aux);
    }
}

/*************************************************************************************************
 * readProblemFile()
 * argumets:
 *          problem *p:       struct que contem a palavra incial e final do problema e o game mode
 *          char *file_pals:  nome do ficheiro que contem os problemas que se pretende resolver
 *
 * return:  void
 *
 * side efects: função que lê e guarda numa lista todos os dados dos problemas a serem executados
 *************************************************************************************************/

problem *readProblemFile(char *file_pals, problem *head)
{
    FILE *fp;
    problem *aux, *p;

    fp = openFile(file_pals, "r");

    p = (problem *)malloc(sizeof(problem));

    if (p == NULL)
        exit(0);

    p->next = NULL;
    head = p;

    while ((fscanf(fp, "%s %s %d", p->starting_word, p->arrival_word, &(p->game_mode)) == 3))
    {
        aux = p;
        p = (problem *)malloc(sizeof(problem));
        if (p == NULL)
            exit(0);
        aux->next = p;
        p->game_mode = 0;
        p->next = NULL;
    }

    aux->next = NULL;
    free(p); // dar free no último que alocamos mas não vamos usar
    fclose(fp);
    return head;
}

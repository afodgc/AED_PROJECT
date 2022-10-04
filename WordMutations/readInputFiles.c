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
<<<<<<< HEAD
        exit(0);
=======
    {
    }
    exit(0);
>>>>>>> 1aed9f6e6f741f83c987620369d837e2218865a0

    return fp;
}

void freeProblem(problem *head)
{
    problem *aux;

    while (head != NULL)
    {
        aux = head;
<<<<<<< HEAD
        printf("%s %s %d\n", head->starting_word, head->arrival_word, head->game_mode);
=======
        // printf("%s %s %d", head->starting_word, head->arrival_word, head->game_mode);
>>>>>>> 1aed9f6e6f741f83c987620369d837e2218865a0
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
<<<<<<< HEAD
problem *readProblemFile(problem *p, char *file_pals, problem *head)
{
    FILE *fp;
    problem *aux;
=======
problem *readProblemFile(char *file_pals, problem *head)
{
    FILE *fp;
    problem *aux, *p;
>>>>>>> 1aed9f6e6f741f83c987620369d837e2218865a0

    fp = openFile(file_pals, "r");

    p = (problem *)malloc(sizeof(problem));
<<<<<<< HEAD
=======

    if (p == NULL)
        exit(0);

>>>>>>> 1aed9f6e6f741f83c987620369d837e2218865a0
    p->next = NULL;
    head = p;

    while ((fscanf(fp, "%s %s %d", p->starting_word, p->arrival_word, &(p->game_mode)) == 3))
    {
        aux = p;
        p = (problem *)malloc(sizeof(problem));
<<<<<<< HEAD
        aux->next = p;
        p->game_mode = 0;

        p->next = NULL;
    }

=======
        if (p == NULL)
            exit(0);
        aux->next = p;
        p->game_mode = 0;
        p->next = NULL;
    }

    aux->next = NULL;
    free(p); // dar free no último que alocamos mas não vamos usar
>>>>>>> 1aed9f6e6f741f83c987620369d837e2218865a0
    fclose(fp);
    return head;
}

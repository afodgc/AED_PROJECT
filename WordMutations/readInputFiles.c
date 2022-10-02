#include "headers.h"

/********************************************************************
 * openFile()
 * argumets: 
 *          char *file_pals: nome do ficheiro que se pretende abrir
 *          char *mode:      modo de abertura do ficheiro
 * 
 * return:  FILE *fp:        ponteiro para o ficheiro que foi aberto
 *******************************************************************/
FILE *openFile(char *file_pals, char *mode)
{
    FILE *fp;
    fp = fopen(file_pals, mode);

    if (fp == NULL)
    {
        printf("erro no ficheiro");
        exit(0);
    }
    return fp;
}

/*************************************************************************************************
 * readProblemFile()
 * argumets:
 *          problem *p:       struct que contem a palavra incial e final do problema e o game mode
 *          char *file_pals:  nome do ficheiro que contem os problemas que se pretende resolver
 * 
 * return:  void
 *************************************************************************************************/
void readProblemFile(problem *p, char *file_pals)
{
    FILE *fp;
    p->next = NULL;
    p->game_mode = 0;
    fp = openFile(file_pals, "r");

    

    while ((fscanf(fp, "%s %s %d", p->starting_word, p->arrival_word, &(p->game_mode)) == 3))
    {
        printf("%s %s %d", p->starting_word, p->arrival_word, p->game_mode);
    }

    fclose(fp);
}

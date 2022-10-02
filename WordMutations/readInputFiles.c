#include "headers.h"

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

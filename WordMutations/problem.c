#include "headers.h"
#include "dicionario.h"

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
    problem *aux = NULL, *p = NULL;

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

void solveProblem(dict *dict_head, problem *problem_head, char *file_pals)
{
    problem *aux_problem_head = problem_head;
    FILE *fp_out;
    int starting_word_size = 0;
    int arrival_word_size = 0;

    char *file_out = (char *)malloc(sizeof(char) * (strlen(file_pals) + strlen(".stats") + 1));
    if (file_out == NULL)
        exit(0);
    strcpy(file_out, file_pals);
    strcat(file_out, ".stats");
    fp_out = openFile(file_out, "w");

    while (aux_problem_head != NULL)
    {
        starting_word_size = strlen(aux_problem_head->starting_word);
        arrival_word_size = strlen(aux_problem_head->arrival_word);

        if (aux_problem_head->game_mode == 1 && (starting_word_size == arrival_word_size))
        {
            gameMode1(dict_head, aux_problem_head, fp_out, starting_word_size);
        }
        else if (aux_problem_head->game_mode == 2 && (starting_word_size == arrival_word_size))
        {
            gameMode2(dict_head, aux_problem_head, fp_out, starting_word_size);
        }
        else
        {
            fprintf(fp_out, "%s %s %d", aux_problem_head->starting_word, aux_problem_head->arrival_word, aux_problem_head->game_mode);
        }
        fprintf(fp_out, "\n");
        aux_problem_head = aux_problem_head->next;
    }

    free(file_out);
    fclose(fp_out);
}

// dizer o tamanho da tabela
void gameMode1(dict *dict_head, problem *problem, FILE *file_out, int problem_word_size)
{
    dict *aux_dict = dict_head;

    while (aux_dict != NULL)
    {
        if (aux_dict->word_size == problem_word_size)
        {
            fprintf(file_out, "%s %d\n", problem->starting_word, aux_dict->table_size);
            return;
        }

        aux_dict = aux_dict->next;
    }
    return;
}

// dizer a posiçao de cada palavra
void gameMode2(dict *dict_head, problem *problem, FILE *file_out, int problem_word_size)
{
    dict *aux_dict = dict_head;
    int starting_index = 0, arrival_index = 0;

    while (aux_dict != NULL)
    {
        if (aux_dict->word_size == problem_word_size)
        {
            starting_index = binaryScr(aux_dict->table, 0, aux_dict->table_size - 1, problem->starting_word);
            arrival_index = binaryScr(aux_dict->table, 0, aux_dict->table_size - 1, problem->arrival_word);
            if (starting_index == -1 || arrival_index == -1)
            {
                // problema mal definido
                fprintf(file_out, "%s %s %d", problem->starting_word, problem->arrival_word, problem->game_mode);
                return;
            }
            else
            {
                fprintf(file_out, "%s %d\n%s %d\n", problem->starting_word, starting_index, problem->arrival_word, arrival_index);
                return;
            }
        }
        aux_dict = aux_dict->next;
    }
    return;
}
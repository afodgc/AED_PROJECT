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


/*********************************************************************************
 * solveProblem()
 *
 * arguments:
 *           dict *dict_head:
 *           problem *problem_head:
 *           char *file_pals:
 *
 * return: void
 *
 * side efects: resolve todos os problemas dados pelo file_pals
 ********************************************************************************/
void solveProblem(dict *dict_head, char *file_out_sem_extençao, char *file_pals)
{
    //declaração de variaveis
    FILE *fp_out, *fp_in;        //ponteiros para os ficheiros
    int starting_word_size = 0;  //tamanho da primeira palavra do problema
    int arrival_word_size = 0;   //tamanho da segunda palavra do problema
    problem problem;             //estrotura que guarda o problema


    //criação do nome do ficheiro de saida
    char *file_out = (char *)malloc(sizeof(char) * (strlen(file_pals) + strlen(".stats") + 1));
    if (file_out == NULL) {
        exit(0);
    }
    strcpy(file_out, file_out_sem_extençao);
    strcat(file_out, ".stats");


    //abertura de ficheiros
    fp_out = openFile(file_out, "w");
    fp_in = openFile(file_pals, "r");

    //leitura dos problemas e resolução
    while ((fscanf(fp_in, "%s %s %d", problem.starting_word, problem.arrival_word, &(problem.game_mode)) == 3))
    {
        starting_word_size = strlen(problem.starting_word);
        arrival_word_size = strlen(problem.arrival_word);

        
        if ((problem.game_mode == 1) && (starting_word_size == arrival_word_size))
        {
            gameMode1(dict_head, problem, fp_out, starting_word_size);
        }
        else if ((problem.game_mode == 2) && (starting_word_size == arrival_word_size))
        {
            gameMode2(dict_head, problem, fp_out, starting_word_size);
        }
        else
        {
            // problema mal definido
            fprintf(fp_out, "%s %s %d\n", problem.starting_word, problem.arrival_word, problem.game_mode);
        }

        fprintf(fp_out, "\n");
    }

    free(file_out);
    fclose(fp_out);
    fclose(fp_in);
    return;
}

/******************************************************************************************************************
 * gameMode1()
 *
 * arguments:
 *          dict *dict_head:       lista de tabelas de dicionários
 *          problem *problem:      lista de problemas
 *          FILE *file_out:        ponteiro para o ficheiro de saida
 *          int problem_word_size: tamanho das palavras do problema
 *
 * return: void
 *
 * side efects: função que resolve os problemas com gamemod=1
 *              caso as palavras do problema se encontrem numa das tabelas de dicinários
 *              dá print do numero de palavras nessa tabela
 *******************************************************************************************************************/
void gameMode1(dict *dict_head, problem problem, FILE *file_out, int problem_word_size)
{
    dict *aux_dict = dict_head;
    int starting_index = 0, arrival_index = 0;

    while (aux_dict != NULL)
    {
        if (aux_dict->word_size == problem_word_size)
        {
            // ver se as palavras existem
            starting_index = binaryScr(aux_dict->table, 0, aux_dict->table_size - 1, problem.starting_word);
            arrival_index = binaryScr(aux_dict->table, 0, aux_dict->table_size - 1, problem.arrival_word);
            if (starting_index == -1 || arrival_index == -1)
            {
                // problema mal definido
                fprintf(file_out, "%s %s %d\n", problem.starting_word, problem.arrival_word, problem.game_mode);
                return;
            }
            else
            {
                fprintf(file_out, "%s %d\n", problem.starting_word, aux_dict->table_size);
                return;
            }
        }

        aux_dict = aux_dict->next;
    }

    // o tamanho dos pares de palavras nao existe no dic
    fprintf(file_out, "%s %s %d\n", problem.starting_word, problem.arrival_word, problem.game_mode);

    return;
}

/******************************************************************************************************************
 * gameMode2()
 *
 * arguments:
 *          dict *dict_head:       lista de tabelas de dicionários
 *          problem *problem:      lista de problemas
 *          FILE *file_out:        ponteiro para o ficheiro de saida
 *          int problem_word_size: tamanho das palavras do problema
 *
 * return: void
 *
 * side efects: função que resolve os problemas com gamemod=2
 *              caso as palavras do problema se encontrem numa das tabelas de dicinários dá print da seu index
 *******************************************************************************************************************/
void gameMode2(dict *dict_head, problem problem, FILE *file_out, int problem_word_size)
{
    dict *aux_dict = dict_head;
    int starting_index = 0, arrival_index = 0;

    while (aux_dict != NULL)
    {
        if (aux_dict->word_size == problem_word_size)
        {
            starting_index = binaryScr(aux_dict->table, 0, aux_dict->table_size - 1, problem.starting_word);
            arrival_index = binaryScr(aux_dict->table, 0, aux_dict->table_size - 1, problem.arrival_word);
            if (starting_index == -1 || arrival_index == -1)
            {
                // problema mal definido
                fprintf(file_out, "%s %s %d\n", problem.starting_word, problem.arrival_word, problem.game_mode);
                return;
            }
            else
            {
                fprintf(file_out, "%s %d\n%s %d\n", problem.starting_word, starting_index, problem.arrival_word, arrival_index);
                return;
            }
        }
        aux_dict = aux_dict->next;
    }
    
    // o tamanho dos pares de palavras nao existe no dic
    fprintf(file_out, "%s %s %d\n", problem.starting_word, problem.arrival_word, problem.game_mode);
    return;
}
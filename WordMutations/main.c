#include "headers.h"
#include "dicionario.h"

int main(int argc, char **argv)
{
    problem *problem_head = NULL; /*struct que guarda todos os dados via input sobre o problema*/
    dict *dict_head = NULL;
    char *file_dict = NULL, *file_pals = NULL; /*nome dos ficheiros de input*/

    /*verificação se os ficheiros de input tem a extensão correta*/
    char extension[] = ".dict";
    file_dict = get_arguments(argc, argv, file_dict, extension);

    strcpy(extension, ".pals");
    file_pals = get_arguments(argc, argv, file_pals, extension);

    /*lê o ficheiro com todos os problemas e armazena as palavras iniciais, finais e gameMode*/
    problem_head = readProblemFile(argv[2], problem_head);

    dict_head = dict_init(argv[1]);

    solveProblem(dict_head, problem_head, file_pals);

    free(file_pals);
    freeProblem(problem_head);
    freeDict(dict_head);
    return EXIT_SUCCESS;
}
#include "headers.h"

int main(int argc, char **argv)
{
    problem *problem = NULL, *problem_head = NULL; /*struct que guarda todos os dados via input sobre o problema*/
    char *file_dict = NULL, *file_pals = NULL;     /*nome dos ficheiros de input*/

    char extension[] = ".dict";

    /*verificação se os ficheiros de input tem a extensão correta*/

    file_dict = get_arguments(argc, argv, file_dict, extension);

    strcpy(extension, ".pals");
    file_pals = get_arguments(argc, argv, file_pals, extension);

    /*lê o ficheiro com todos os problemas e armazena as palavras iniciais, finais e gameMode*/
    problem_head = readProblemFile(problem, argv[2], problem_head);

    /*frees*/
    free(file_pals);
    freeProblem(problem_head);
    return EXIT_SUCCESS;
}
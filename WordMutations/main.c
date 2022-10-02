#include "headers.h"


int main(int argc, char **argv)
{
    problem problem;   /*struct que guarda todos os dados via input sobre o problema*/
    char *file_dict = NULL, *file_pals = NULL;   /*nome dos ficheiros de input*/


    /*verificação se os ficheiros de input tem a extensão correta*/
    char extension[] = "dict";
    file_dict = get_arguments(argc, argv, file_dict, extension);

    strcpy(extension, "pals");
    file_pals = get_arguments(argc, argv, file_pals, extension);


    /*lê o ficheiro com todos os problemas e armazena as palavras iniciais, finais e gameMode*/
    readProblemFile(&problem, argv[2]);

    /*frees*/
    free(file_pals);
    free(file_dict);

    return EXIT_SUCCESS;
}
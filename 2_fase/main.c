#include "headers.h"
#include "dicionario.h"

int main(int argc, char **argv)
{
    dict *dict_head = NULL;
    char *file_dict = NULL, *file_pals_sem_extencao = NULL; /*nome dos ficheiros de input*/

    /*verificação se os ficheiros de input tem a extensão correta*/
    char extension[] = ".dict";
    file_dict = get_arguments(argc, argv, file_dict, extension);

    strcpy(extension, ".pals");
    file_pals_sem_extencao = get_arguments(argc, argv, file_pals_sem_extencao, extension);

    dict_head = dict_init(argv[1]);

    //TO-DO: aloc grafo

    //TO-DO:   solve problem



    free(file_pals_sem_extencao);
    freeDict(dict_head);
    return EXIT_SUCCESS;
}
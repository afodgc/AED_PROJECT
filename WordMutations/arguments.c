#include "headers.h"

/**********************************************************
 * get_arguments()
 * argumets:
 *          int argc:        number of argumets
 *          char **argv:     vetor dos argumentos
 *          char *file_name: nome do ficheiro
 *          char extension[]:extenção a ser verificada
 *
 * return:  char *file_name nome do ficheiro sem a extenção
 *
 * side efects: verifica se os argumetos tem extenções corretas
 *********************************************************/
char *get_arguments(int argc, char **argv, char *file_name, char extension[])
{

    char *dict_extension = NULL; // extenção que argumeto tem
    int dots = 0;                // numero de pontos que o argumeto tem
    int argument_size = 0;       // tamanho do argumeto
    int index = 0;               // variavel que diz qual o argumeto a ser analisado(1 ou 2)
    int i = 0;
    int k = 0;

    // primeiro que tudo verificar se foram inseridos 2 argumentos
    if (argc != 3)
        exit(0);

    // para selecionar o argumento a analisar
    if (strcmp(extension, ".dict") == 0)
    {
        index = 1;
    }
    else
    {
        index = 2;
    }

    argument_size = strlen(argv[index]);

    if (argument_size < 5)
        exit(0);

    dict_extension = (char *)malloc(sizeof(char) * (5 + 1));

    for (i = argument_size - 5, k = 0; i < argument_size; i++, k++)
    {
        dict_extension[k] = argv[index][i];
    }
    dict_extension[k] = '\0';

    if (strcmp(dict_extension, extension) != 0)
    {
        free(dict_extension);
        exit(0);
    }

    if (index == 1)
    {
        free(dict_extension);
        return file_name; // no .dict nao precisamos do nome
    }

    file_name = (char *)malloc(sizeof(char) * (argument_size - 5 + 1)); //-5 por causa da .dict e +1 por causa do '/0'

    // copiar o file_name
    for (i = 0; i < argument_size - 5; i++)
    {
        file_name[i] = argv[index][i];
    }
    file_name[i] = '\0';

    free(dict_extension);
    return file_name;
}
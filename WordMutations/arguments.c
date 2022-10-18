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

    char *file_extension = NULL; // extenção que argumeto tem
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

    file_extension = (char *)malloc(sizeof(char) * (5 + 1)); // extensao tem tamanho 5 + '\0'

    if (file_extension == NULL)
        exit(0);

    // sacar estensao do nome do ficheiro
    for (i = argument_size - 5, k = 0; i < argument_size; i++, k++)
    {
        file_extension[k] = argv[index][i];
    }
    file_extension[k] = '\0';

    // ver se é a extensao que queremos
    if (strcmp(file_extension, extension) != 0)
    {
        free(file_extension);
        exit(0);
    }

    if (index == 1)
    {
        free(file_extension);
        if (checkIfFileExists(argv[index]) == 0) // se nao existir damos exit
            exit(0);
        return file_name; // no .dict nao precisamos do nome
    }

    if (checkIfFileExists(argv[index]) == 0)
    { // se o ficheiro nao existir
        free(file_extension);
        exit(0);
    }
    file_name = (char *)malloc(sizeof(char) * (argument_size - 5 + 1)); //-5 por causa da .dict e +1 por causa do '/0'
    if (file_name == NULL)
        exit(0);

    // copiar o file_name
    for (i = 0; i < argument_size - 5; i++)
    {
        file_name[i] = argv[index][i];
    }
    file_name[i] = '\0';

    free(file_extension);
    return file_name;
}


/**********************************************************************
 * checkIfFileExists()
 * 
 * argumets:   
 *          char *file_name: nome do ficheiro
 * 
 * return:  retorna 1 se existir ou 0 se não existir
 * 
 * side efects: função que verifica se o ficheiro existe 
 **********************************************************************/
int checkIfFileExists(char *file_name)
{
    FILE *fp = NULL;
    fp = fopen(file_name, "r");
    if (fp == NULL)
        return 0; // nao existe
    fclose(fp);
    return 1; // existe
}
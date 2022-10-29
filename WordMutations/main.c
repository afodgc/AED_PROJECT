#include "headers.h"
#include "dicionario.h"
#include "graph.h"

/*========================================================================*/
/* Nomes:  Afonso Daniel Guerreiro Coelho   numeros de aluno: 103450
 *         Miguel Luís Valentim Andrade                       102530
 *
 * Data: 21/10/2022
 * =======================================================================
 *  Descrição: Este programa é a nossa implementação do projeto de AED
 *             chamado de "WordMutations" que calcula o caminho de custo
 *             minino entre duas palavras. Para mais informações
 *             sobre o projeto veja o pdf.
 *
 *
 */
/*========================================================================*/
int main(int argc, char **argv)
{
    dict *dict_head = NULL;
    char *file_dict = NULL, *name_of_output_file = NULL; /*nome dos ficheiros de input*/

    /*verificação se os ficheiros de input tem a extensão correta*/
    char extension[] = ".dict";
    file_dict = get_arguments(argc, argv, file_dict, extension);

    strcpy(extension, ".pals");
    name_of_output_file = get_arguments(argc, argv, name_of_output_file, extension);

    dict_head = dict_init(argv[1], argv[2]);

    solveProblem(dict_head, name_of_output_file, argv[2]);

    free(name_of_output_file);
    freeDict(dict_head);
    return EXIT_SUCCESS;
}
#include "headers.h"
#include "dicionario.h"
#include "graph.h"

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

/* -------TO-DO------- solve problem*/

// while existir problemas para resolver
// verificar se as palavras tem o mesmo tamanho
// no inicio verificar se as palavras existem no dicionário
// algoritmo de procura do caminho mais cuto

void solveProblem(dict *dict_head, char *name_of_output_file, char *file_pals)
{
    problem problem;
    Graph **graph;
    FILE *fpIn = NULL, *fpOut = NULL;
    int startWordIndex = 0, destWordIndex = 0, numOfGraphs = 0, numOfVertices = 0;
    char *file_out = createOutput(name_of_output_file);
    int i = 0;
    // alocar ponteiro para os ponteiros para grafos
    graph = (Graph **)malloc(sizeof(Graph *));

    fpIn = openFile(file_pals, "r");
    fpOut = openFile(file_out, "w");

    while ((fscanf(fpIn, "%s %s %d", problem.starting_word, problem.arrival_word, &problem.numOfmutations)) == 3)
    {
        // se o problema estiver mal definido passamos ao próximo problema
        if (checkIfProblemIsWellDef(dict_head, problem, fpOut, &startWordIndex, &destWordIndex, &numOfVertices) == 0)
            continue;

        for (i = 0; i < numOfGraphs; i++)
        {
            // estamos a ver se ja existe um grafo alocado para aquele tamanho de palavras
            graph[i]->wordSize = strlen(problem.starting_word);
            // se já existir temos de fazer umas coisas...
        }
        // if(graph[i]->result != 0) break; isto serve para passarmos para o proximo problema

        // se nao existir temos de alocar um novo grafo para este tamanho de palavras
        graph[i] = init_graph(numOfVertices, problem.numOfmutations, strlen(problem.starting_word));
        graph[i] = aloc_adjList(graph[i], dict_head);

        numOfGraphs++;
    }

    fclose(fpIn);
    fclose(fpOut);
    free(file_out);

    for (int i = 0; i < numOfGraphs; i++)
    {
        freeGraph(graph[i]);
        free(graph[i]->adjList);
        free(graph[i]);
    }
    free(graph);
}

// criar nome do ficheiro de saida
char *createOutput(char *name)
{
    char *file_out = (char *)malloc(sizeof(char) * (strlen(name) + strlen(".paths") + 1));
    if (file_out == NULL)
    {
        exit(0);
    }
    strcpy(file_out, name);
    strcat(file_out, ".paths");

    return file_out;
}

// se o problema estiver bem definido retornamos 1, se nao 0, antes de retornamos 0 temos de fprintf antes
int checkIfProblemIsWellDef(dict *dict_head, problem problem, FILE *fpout, int *startWordIndex, int *destWordIndex, int *numOfVertices)
{
    dict *aux_dict = dict_head;
    int startWordSize = strlen(problem.starting_word), destWordSize = strlen(problem.arrival_word);

    // se as palavras tiverem tamanhos diferentes
    if (startWordSize != destWordSize)
    {
        fprintf(fpout, "%s -1\n%s", problem.starting_word, problem.arrival_word);
        return 0;
    }

    // o numero de mutações indicadas é inválido
    if (problem.numOfmutations < 1 && problem.numOfmutations > 3)
    {
        fprintf(fpout, "%s -1\n%s", problem.starting_word, problem.arrival_word);
        return 0;
    }

    // vamos correr a lista de dicionarios para encontrar a tabela com o tamanho das palavras pretendidas
    while (aux_dict != NULL)
    {
        // encontramos o dicionario certo
        if (aux_dict->word_size == startWordSize)
        {
            // vamos fazer procura binaria para encontrar o index das palavras, se nao existirem retorna -1
            *startWordIndex = binaryScr(aux_dict->table, 0, aux_dict->table_size - 1, problem.starting_word);
            *destWordIndex = binaryScr(aux_dict->table, 0, aux_dict->table_size - 1, problem.arrival_word);
            *numOfVertices = aux_dict->table_size;

            // pelo menos uma das palavras não está no dict, logo o problema está mal definido
            if (*startWordIndex == -1 || *destWordIndex == -1)
            {
                fprintf(fpout, "%s -1\n%s", problem.starting_word, problem.arrival_word);
                return 0;
            }

            // este é o caso de estarmos a procurar o caminho para a mesma palavra de chegada e partida, neste caso vamos dizer que o problema está mal definido para facilitar
            if ((*startWordIndex == *destWordIndex) && *startWordIndex != -1 && *destWordIndex != -1)
            {
                // as palavras sao iguais e existem no dict, logo o custo é 0
                fprintf(fpout, "%s 0\n%s", problem.starting_word, problem.arrival_word);
                return 0;
            }

            break;
        }

        aux_dict = aux_dict->next;
    }
    // percorremos o dict todo e nao encontramos o tamanho para as palavras do problema
    if (aux_dict == NULL)
    {
        fprintf(fpout, "%s -1\n%s", problem.starting_word, problem.arrival_word);
        return 0;
    }

    return 1;
}

/***************************************************
 * printResposta()
 *
 * argumets:
 *          resultado: contem:
 *                              vetor com os antecessores de cada vertice(index da palavra no dicionario)
 *                              custo do menor caminho
 *          origem:  index da origem relativamente ao dicionário
 *          destino: index da destino relativamente ao dicionário
 *          *output: ponteiro para o ficheiro de saida
 *          problem: problema em causa
 *          *dict_head: dicionario com o tamanho de palavras em causa
 *
 * return: void
 * side efects: dá print á resposta
 **************************************************/
void printResposta(Caminho resultado, int origem, int destino, FILE *output, problem problem, dict *dict_head){

    /* caso nao exista caminho */
    if (resultado.custo == -1){
        fprintf(output, "%s -1\n%s", problem.starting_word, problem.arrival_word);
    } else {
        printR(resultado, origem, destino, output, problem, dict_head);
        fprintf(output, "%s", dict_head->table[destino]);
    }
    
    return;
}
/**************************************************************
 * printR()
 *
 * descricao: funcao recursiva que escreve todos os resulados de
 *            um caminho mais curto menos o ultimo
 ********************************************************************/
void printR(Caminho resultado, int origem, int destino, FILE *output, problem problem, dict *dict_head){

    if (resultado.ant[destino] == origem){
        fprintf(output, "%s %i", dict_head->table[resultado.ant[destino]], resultado.custo);
    } else {
        printR(resultado, origem, resultado.ant[destino], output, problem, dict_head);
        fprintf(output, "%s", dict_head->table[resultado.ant[destino]]);
    }

    return;
}

#include "headers.h"
#include "dicionario.h"
#include "graph.h"
#include <math.h>

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
        exit(0);
    }

    return fp;
}

void solveProblem(dict *dict_head, char *name_of_output_file, char *file_pals)
{
    problem problem;
    Graph **graph = NULL;
    FILE *fpIn = NULL, *fpOut = NULL;
    int startWordIndex = 0, destWordIndex = 0, numOfGraphs = 0, numOfVertices = 0, i = 0, diferentChar = 0, wordSize = 0;
    char *file_out = createOutput(name_of_output_file);
    dict *dict_aux = dict_head;
    Caminho result;
    int numOfMutations[MAX_LEN_WORDS];

    result.custos = NULL;
    result.ant = NULL;

    fpIn = openFile(file_pals, "r");
    fpOut = openFile(file_out, "w");

    for (i = 0; i < MAX_LEN_WORDS; i++)
    {
        numOfMutations[i] = 0;
    }

    // vamos percorrer o ficheiro de problemas par sabermos de antemao os grafos e o numero de mutaçoes que temos de alocar
    while ((fscanf(fpIn, "%s %s %d", problem.starting_word, problem.arrival_word, &problem.numOfmutations)) == 3)
    {
        // se o problema estiver mal definido nem temos de fazer as próximas verificações
        if (checkIfProblemIsWellDef(dict_head, problem, fpOut, &startWordIndex, &destWordIndex, &numOfVertices, 0) == 0)
            continue;

        // se o numero de mutaçoes indicada no problema for superior ao numero que temos guardado ate agora, temos de avaliar se é preciso atualizar
        wordSize = strlen(problem.starting_word);

        if (numOfMutations[wordSize] < problem.numOfmutations)
        {
            // vamos contar o numero de caracteres diferentes entre as duas palavras, isto serve para evitar alocar um numero de mutações excessiva
            diferentChar = 0;

            for (i = 0; i < wordSize; i++)
            {
                if (problem.arrival_word[i] != problem.starting_word[i])
                {
                    diferentChar++;
                }
            }

            // se a diferença entre as duas palavras for de 1 char e existirem no dict, o caminho é direto, nao temos de alocar grafo
            if (diferentChar == 1)
                continue;

            /*se o numero de mutaçoes for superior ou igual ao numero de caracteres diferentes temos de atualizar para que o numero de  mutaçoes
            seja apenas igual ao numero de caracteres diferentes*/
            if (problem.numOfmutations >= diferentChar)
                if (diferentChar > numOfMutations[wordSize])
                    problem.numOfmutations = diferentChar;

            // caso o numero de mutaçoes seja inferior ou igual ao numero de caracteres diferentes entao podemos atualizar o numero de mutaçoes
            if (problem.numOfmutations <= diferentChar)
                numOfMutations[wordSize] = problem.numOfmutations;
        }
    }

    // para sabermos o numero de grafos que temos de alocar
    for (i = 0; i < MAX_LEN_WORDS; i++)
    {

        if (numOfMutations[i] != 0)
            numOfGraphs++;
    }

    // alocar ponteiro para os ponteiros para grafos
    graph = (Graph **)malloc(numOfGraphs * sizeof(Graph *));
    if (graph == NULL)
        exit(0);

    numOfGraphs = 0;

    // agora vamos percorrer o vetor que guardou quais os grafos e o numero de mutaçoes que temos de alocar
    for (i = 0; i < MAX_LEN_WORDS; i++)
    {

        // o vetor numOfMutations tem o numero de mutaçoes possiveis por tamanho de palavra, o index corresponde ao tamanho da palavra
        if (numOfMutations[i] != 0)
        {
            // percorrer a lista de tabelas para encontrar o dicionario correspondente àquele tamanho de palavras
            while (dict_aux != NULL)
            {
                if (dict_aux->word_size == i)
                {
                    numOfVertices = dict_aux->table_size;
                    break;
                }

                dict_aux = dict_aux->next;
            }

            // alocar um novo grafo de acordo com o tamanho da palavra e o número de mutações
            graph[numOfGraphs] = init_graph(numOfVertices, numOfMutations[i], i);
            graph[numOfGraphs] = aloc_adjList(graph[numOfGraphs], dict_head);
            numOfGraphs++;
        }
    }

    // voltar ao inicio do ficheiro de problemas
    fseek(fpIn, 0, SEEK_SET);

    while ((fscanf(fpIn, "%s %s %d", problem.starting_word, problem.arrival_word, &problem.numOfmutations)) == 3)
    {
        // se o problema estiver mal definido passamos ao próximo problema
        if (checkIfProblemIsWellDef(dict_head, problem, fpOut, &startWordIndex, &destWordIndex, &numOfVertices, 1) == 0)
            continue;

        // vamos contar o numero de caracteres diferentes entre as duas palavras, se esse numero for 1, a resposta é direta
        wordSize = strlen(problem.starting_word);
        diferentChar = 0;
        for (int i = 0; i < wordSize; i++)
        {
            if (problem.starting_word[i] != problem.arrival_word[i])
                diferentChar++;
        }

        if (diferentChar == 1)
        {
            fprintf(fpOut, "%s 1\n%s\n\n", problem.starting_word, problem.arrival_word);
            continue;
        }

        // percorrer o vetor de grafos
        for (i = 0; i < numOfGraphs; i++)
        {
            // encontrar o grafo correspondente ao tamanho das palavras do problema
            if (graph[i]->wordSize == wordSize)
            {
                // dar free no vetor ant e dos custos do dijkstra do problema anterior
                if (result.ant != NULL)
                    free(result.ant);
                if (result.custos != NULL)
                    free(result.custos);

                result.ant = (int *)malloc(sizeof(int) * graph[i]->numOfVertices);
                if (result.ant == NULL)
                    exit(0);

                result.custos = (float *)malloc(sizeof(float) * graph[i]->numOfVertices);
                if (result.custos == NULL)
                    exit(0);

                // encontrar o caminho mais curto entre as duas palavras
                dijkstra(graph[i], startWordIndex, destWordIndex, result.ant, result.custos, problem.numOfmutations);

                // dar print na resposta
                printResposta(result, startWordIndex, destWordIndex, fpOut, problem, dict_head);
                fprintf(fpOut, "\n");
            }
        }
    }

    fclose(fpIn);
    fclose(fpOut);
    free(file_out);

    free(result.ant);
    free(result.custos);

    for (int i = 0; i < numOfGraphs; i++)
    {
        freeGraph(graph[i]);
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

// se o problema estiver bem definido retornamos 1, se nao 0, antes de retornamos 0 temos de fprintf antes, caso o printResult = 1
int checkIfProblemIsWellDef(dict *dict_head, problem problem, FILE *fpout, int *startWordIndex, int *destWordIndex, int *numOfVertices, int printResult)
{
    dict *aux_dict = dict_head;
    int startWordSize = strlen(problem.starting_word), destWordSize = strlen(problem.arrival_word);

    // se as palavras tiverem tamanhos diferentes
    if (startWordSize != destWordSize)
    {
        if (printResult)
            fprintf(fpout, "%s -1\n%s\n\n", problem.starting_word, problem.arrival_word);

        return 0;
    }

    // o numero de mutações indicadas é inválido
    if (problem.numOfmutations < 0)
    {
        if (printResult)
            fprintf(fpout, "%s -1\n%s\n\n", problem.starting_word, problem.arrival_word);
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
                if (printResult)
                    fprintf(fpout, "%s -1\n%s\n\n", problem.starting_word, problem.arrival_word);
                return 0;
            }

            // este é o caso de estarmos a procurar o caminho para a mesma palavra de chegada e partida, neste caso vamos dizer que o problema está mal definido para facilitar
            if ((*startWordIndex == *destWordIndex) && *startWordIndex != -1 && *destWordIndex != -1)
            {
                // as palavras sao iguais e existem no dict, logo o custo é 0
                if (printResult)
                    fprintf(fpout, "%s 0\n%s\n\n", problem.starting_word, problem.arrival_word);
                return 0;
            }

            break;
        }

        aux_dict = aux_dict->next;
    }
    // percorremos o dict todo e nao encontramos o tamanho para as palavras do problema
    if (aux_dict == NULL)
    {
        if (printResult)
            fprintf(fpout, "%s -1\n%s\n\n", problem.starting_word, problem.arrival_word);
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
void printResposta(Caminho resultado, int origem, int destino, FILE *output, problem problem, dict *dict_head)
{
    dict *dict_aux = dict_head;
    int custo = (int)resultado.custos[destino];
    // encontrar o dicionario certo
    while (dict_aux->word_size != strlen(problem.arrival_word))
    {
        dict_aux = dict_aux->next;
    }

    /* caso nao exista caminho */
    if (resultado.custos[destino] == HUGE_VAL)
    {
        fprintf(output, "%s -1\n%s\n", problem.starting_word, problem.arrival_word);
    }
    else
    {
        printR(resultado, origem, destino, output, problem, dict_aux, custo);
        fprintf(output, "%s\n", dict_aux->table[destino]);
    }

    return;
}

/**************************************************************
 * printR()
 *
 * descricao: funcao recursiva que escreve todos os resulados de
 *            um caminho mais curto menos o ultimo
 ********************************************************************/
void printR(Caminho resultado, int origem, int destino, FILE *output, problem problem, dict *dict_head, int custo)
{

    if (resultado.ant[destino] == origem)
    {
        fprintf(output, "%s %d\n", dict_head->table[resultado.ant[destino]], custo);
    }
    else
    {
        printR(resultado, origem, resultado.ant[destino], output, problem, dict_head, custo);
        fprintf(output, "%s\n", dict_head->table[resultado.ant[destino]]);
    }

    return;
}

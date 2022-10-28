#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graph.h"

/*******************************************************
 *  *newNode()
 *
 * arguments:
 *              int vertex:     vertice que vai ficar guardado naquele nó
 *              node *next:     cabeça de lista de ajacencias antes de entrar na fução
 *              short int cost: custo associado àquele nó
 *              location *custosLocations : guarda a localização do ultimo elemento
 *              do de custo igual ao index
 *
 * return: retorna o novo nó inserido na lista do nó ao qual o queriamos adionar
 *
 *
 * *****************************************************/
node *newNode(int vertex, node *next, short int cost)
{
    node *x = (node *)malloc(sizeof(node));
    if (x == NULL)
        exit(0);

    // x é do tipo node
    x->vertex = vertex;
    x->cost = cost;
    x->next = next;
    return x;
}

// inicializar o grafo
Graph *init_graph(int numOfVertices, int numOfMutations, int wordSize)
{
    Graph *G = (Graph *)malloc(sizeof(Graph));
    G->numOfVertices = numOfVertices;
    G->numOfMutations = numOfMutations;
    G->wordSize = wordSize;
    G->adjList = (node **)malloc(numOfVertices * sizeof(node *));
    if (G->adjList == NULL)
        exit(0);

    for (int v = 0; v < numOfVertices; v++)
    {
        G->adjList[v] = NULL;
    }

    return G;
}
/***********************************************
 * insert_Edge()
 *
 * arguments:
 *         Graph *g: grafo ao qual queremos adionar uma nova aresta
 *         edge e: informações a cerca da aresta que queremos inserir no grafo
 *
 * return: void
 *
 * ********************************************/
void insert_edge(Graph *g, Edge e)
{

    int start = e.start;
    int dest = e.dest;

    g->adjList[start] = newNode(dest, g->adjList[start], e.cost);
    g->adjList[dest] = newNode(start, g->adjList[dest], e.cost);
}

/**********************************************
 * aloc_adjList()
 *
 * arguments:
 *          Graph *g: recebe o grafo em que queremos alocar a lista de adjacências
 *          dict *dict_head: cabeça de lista da lista de tabelas correspondente ao dicionário
 *
 * Nesta função vamos percorrer a tabela do dicionario do tamanho correspondente, e vamos comparar palavra a palavra e ver
 * quantos caracteres diferem entre si, se esse valor for inferior ou igual ao numero de mutações permitidas, então inserimos
 * uma aresta entre os indexes dessas duas palavras.
 *
 *********************************************/
Graph *aloc_adjList(Graph *g, dict *dict_head)
{
    dict *aux_dict = dict_head;
    int cost = 0;
    Edge edge;

    // descobrir o dicionario em que temos o tamanho de palavras correspondente
    while (aux_dict != NULL)
    {

        if (aux_dict->word_size == g->wordSize)
        {
            // vamos percorrer palavra a palavra e comparar com todas as outras e descobrir as que estao conectadas
            for (int i = 0; i < aux_dict->table_size; i++)
            {
                for (int j = i + 1; j < aux_dict->table_size; j++)
                {
                    // se as palavras difererem menos ou igual ao num de mutações entao temos de conecta-las
                    if (compareTwoWords(aux_dict->table[i], aux_dict->table[j], g->numOfMutations, aux_dict->word_size, &cost) == 1)
                    {
                        edge.start = i;
                        edge.dest = j;
                        edge.cost = cost;
                        insert_edge(g, edge);
                    }
                }
            }
        }

        aux_dict = aux_dict->next;
    }

    return g;
}

/****************************************
 * compareTwoWords()
 *
 * arguments:
 * char *word1: palavra
 * char *word2: palavra
 * int numOfMutations: número de mutações permitidas
 * int wordSize: tamanho das palavras
 * int *cost: custo associado sem a mutação for permitida
 *
 * return: 0 se as palavras não tiverem conectas e 1 se estiverem
 *
 ****************************************/

int compareTwoWords(char *word1, char *word2, int numOfMutations, int wordSize, int *cost)
{
    // temos de ver se as palavras diferem em menos ou igual caracteres do que o numero de mutaçoes
    int diferentChar = 0;
    *cost = 0;

    for (int i = 0; i < wordSize; i++)
    {
        if (word1[i] != word2[i])
        {
            diferentChar++;
            if (diferentChar > numOfMutations)
            {
                return 0;
            }
        }
    }

    // o custo é quadratico no numero de caracteres substituidos
    *cost = diferentChar * diferentChar;
    return 1;
}

void freeGraph(Graph *g)
{
    node *node_aux = NULL, *tmp = NULL;

    for (int i = 0; i < g->numOfVertices; i++)
    {
        node_aux = g->adjList[i];

        while (node_aux != NULL)
        {
            tmp = node_aux;
            node_aux = tmp->next;
            free(tmp);
        }
    }
    free(g->adjList);
    free(g);
}

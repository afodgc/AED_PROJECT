#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graph.h"

node *newNode(int vertex, node *next)
{
    node *x = (node *)malloc(sizeof(node));
    // x é do tipo node
    x->vertex = vertex;
    x->next = next;
    return x;
}

// inicializar o grafo
Graph *init_graph(int numOfVertices, int numOfMutations, int wordSize)
{
    Graph *G = (Graph *)malloc(sizeof(Graph));
    G->numOfVertices = numOfVertices;
    G->numOfEdges = 0;
    G->numOfMutations = numOfMutations;
    G->wordSize = wordSize;
    G->adjList = (node **)malloc(numOfVertices * sizeof(node *));

    for (int v = 0; v < numOfVertices; v++)
    {
        G->adjList[v] = NULL;
    }
    return G;
}

void insert_edge(Graph *g, edge *e)
{

    int start = e->start;
    int dest = e->dest;

    g->adjList[start] = newNode(dest, g->adjList[start]);
    g->adjList[dest] = newNode(start, g->adjList[dest]);
}

/*
Nesta função vamos alocar a lista de adjacencias
*/
Graph *aloc_adjList(Graph *g, dict *dict_head)
{
    dict *aux_dict = dict_head;

    // descobrir o dicionario em que temos o tamanho de palavras correspondente
    while (aux_dict != NULL)
    {

        if (aux_dict->word_size == g->wordSize)
        {
            // vamos percorrer palavra a palavra e comparar com todas as outras e descobrir as que estao conectadas
            for (int i = 0; i < aux_dict->table_size - 1; i++)
            {
                for (int j = i + 1; j < aux_dict->table_size - 1; j++)
                {

                    if (compareTwoWords(aux_dict->table[i], aux_dict->table[j], g->numOfMutations) == 1)
                    {
                    }
                }
            }
        }

        aux_dict = aux_dict->next;
    }

    return g;
}

int compareTwoWords(char *word1, char *word2, int numOfMutations)
{
}
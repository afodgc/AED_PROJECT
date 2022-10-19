#ifndef GRAPH_H
#define GRAPH_H

#include "dicionario.h"

typedef struct myedge
{
    int start;
    int dest;
} edge;

typedef struct _node
{
    int vertex;
    short int cost;
    struct _node *next;
} node;

typedef struct mygraph
{
    int numOfVertices;
    int numOfEdges;
    int wordSize;
    int numOfMutations;
    node **adjList;

} Graph;

typedef struct caminho
{
    int *ant;
    int custo;
} Caminho;

Graph *init_graph(int, int, int);
void insert_edge(Graph *, edge *);
void freeGraph(Graph *);

Graph *aloc_adjList(Graph *, dict *dict_head);
int compareTwoWords(char *word1, char *word2, int numOfMutations);

node *newNode(int, node *);

void dijkstra(int origem, int destino, Graph *grafo, Caminho *resultado, int numOfmutations);

#endif
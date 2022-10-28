#ifndef GRAPH_H
#define GRAPH_H

#include "dicionario.h"
#include <math.h>

typedef struct myedge
{
    int start;
    int dest;
    short int cost;
} Edge;

typedef struct _node
{
    int vertex;
    short int cost;
    struct _node *next;
} node;

typedef struct mygraph
{
    int numOfVertices;
    int wordSize;
    int numOfMutations;
    node **adjList;
} Graph;

typedef struct caminho
{
    int *ant;
    float *custos;
} Caminho;

typedef struct _Heap
{
    int *queu;  // fila
    int *pos;   // position of the  elemts
    int PQsize; // tamanho atual da queu
} Heap;

Graph *init_graph(int, int, int);
void insert_edge(Graph *, Edge);
void freeGraph(Graph *);

Graph *aloc_adjList(Graph *, dict *dict_head);
int compareTwoWords(char *word1, char *word2, int numOfMutations, int wordSize, int *cost);

node *newNode(int vertex, node *next, short int cost);

void dijkstra(Graph *G, int origem, int destino, int *st, float *wt, int numOfMutations);
void exch(Heap *Queue, int index1, int index2);
void PQinit(Heap *Queue, int size);
int PQisInQueu(Heap Queue, int index);
void FixUp(Heap *Queue, int indiceChange, float *wt);
void fixDown(Heap *Queue, int indiceChange, float *wt);
int less(Heap Queue, int index1, int index2, float *wt);
int PQempty(Heap queue);
void PQinsert(Heap *Queue, int index, float *wt);
int PQdelmin(Heap *queue, float *wt);
void PQfree(Heap *queue);

#endif
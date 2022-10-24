#ifndef GRAPH_H
#define GRAPH_H

#include "dicionario.h"

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

Graph *init_graph(int, int, int);
void insert_edge(Graph *, Edge);
void freeGraph(Graph *);

Graph *aloc_adjList(Graph *, dict *dict_head);
int compareTwoWords(char *word1, char *word2, int numOfMutations, int wordSize, int *cost);

node *newNode(int, node *, short int);

void dijkstra(int origem, int destino, Graph *grafo, Caminho *resultado, int numOfmutations);

void GRAPHpfs(Graph *G, int s, int *st, float *wt, int numOfMutations);

void exch(int i, int j, int *pq, int *qp);
void PQinit(int *PQsize);
int PQempty(int PQsize);
void fixUp(int *pq, int k, int *qp, float *wt);
void fixDown(int *pq, int k, int N, int *qp, float *wt);
int less(int i, int j, float *wt);
void PQinsert(int k, int *pq, int *qp, int *PQsize, float *wt);
void PQchange(int k, int PQsize, int *pq, int *qp, float *wt);
int PQdelmin(int *PQsize, int *pq, int *qp, float *wt);

#endif
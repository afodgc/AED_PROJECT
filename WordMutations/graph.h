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

typedef struct Queu{
    int *queu;  // fila
    int *pos;   // position of the  elemts
    int PQsize; // tamanho atual da queu
} Queu;

Graph *init_graph(int, int, int);
void insert_edge(Graph *, Edge);
void freeGraph(Graph *);

Graph *aloc_adjList(Graph *, dict *dict_head);
int compareTwoWords(char *word1, char *word2, int numOfMutations, int wordSize, int *cost);

node *newNode(int, node *, short int);

void dijkstra(Graph *G, int origem, int destino, int *st, float *wt, int numOfMutations);
void exch(Queu *Queu, int index1, int index2);
void PQinit(Queu *Queu, int size);
int PQisInQueu(Queu Queu, int index);
void FixUp(Queu *Queu, int indiceChange, float *wt);
void fixDown(Queu *Queu, int indiceChange, float *wt);
int less(Queu Queu, int index1, int index2, float *wt);
int PQempty(Queu queu);
void PQinsert(Queu *Queu, int index, float *wt);
int PQdelmin(Queu *queu, float *wt);
void PQfree(Queu *queu);

#endif
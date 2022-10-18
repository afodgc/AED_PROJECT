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
graph *init_graph(int numOfVertices)
{
    int v;
    graph *G = (graph *)malloc(sizeof(graph));
    G->numOfVertices = numOfVertices;
    G->numOfEdges = 0;
    G->adjList = (node **)malloc(numOfVertices * sizeof(node *));

    for (int v = 0; v < numOfVertices; v++)
    {
        G->adjList[v] = NULL;
    }
    return G;
}

void insert_edge(graph *g, edge *e)
{

    int start = e->start;
    int dest = e->dest;

    g->adjList[start] = newNode(dest, g->adjList[start]);
    g->adjList[dest] = newNode(start, g->adjList[dest]);
}
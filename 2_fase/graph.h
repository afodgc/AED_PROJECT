#ifndef GRAPH_H
#define GRAPH_H

typedef struct myedge
{
    int start;
    int dest;
} edge;

typedef struct mygraph
{
    int numOfVertices;
    int numOfEdges;
    int wordSize;
    int numOfMutations;
    node **adjList;
} graph;

typedef struct _node
{
    int vertex;
    struct _node *next;
} node;

graph *init_graph(int);
void insert_edge(graph *, edge *);
void freeGraph(graph *);

node *newNode(int, node *);

#endif
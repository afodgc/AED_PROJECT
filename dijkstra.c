#include "headers.h"
#include "dicionario.h"
#include "graph.h"
#include <math.h>




/************************************************************************************************************************
 * 
 * dijkstra() - função que realiza o algoritmo dijkstra
 * arguments: 
 *          int origem:     index do vertice de origem do problema
 *          int destino:    index do vertice de destino do problema
 *          graph *grafo:   grafo com:(numOfVertices, numOfEdges, wordSize, numOfMutations, **adjList)
 *                      
 * return: void
 * 
 *************************************************************************************************************************/
void dijkstra(int origem,int destino,graph *grafo)
{   int i,v,                           /* variáveis auxiliares */
        ant[grafo->numOfVertices];     /* vetor dos antecessores */
    short int z[grafo->numOfVertices]; /* vértices para os quais se conhece o caminho mínimo */
    float dist[grafo->numOfVertices];  /* vetor com os custos dos caminhos */
    double min;                        /* variável auxiliar */
    node *no_aux;                      /*no auxiliar*/


    /* Inicializacoes */
    for (int i=0;i<grafo->numOfVertices;i++){
        /* distancias inicalmente a infinito */
        dist[i] = HUGE_VAL;
        /* desconhecido o caminho minimo (z[vertice]=0) */
        z[i] = 0;
        /* inicialmente ningem tem antecessor */
        ant[i] = -1;
    }

    /* carrega os custos dos vertices que estao ligados a origem*/
    no_aux = grafo->adjList[origem];
    while (no_aux != NULL)
    {
        dist[no_aux->vertex] = no_aux->cost;

        /* todos os que estiverem nesta lista de adjacencias tem a origem como antecessor */
        ant[no_aux->vertex] = origem;

        no_aux = no_aux->next;
    }

    z[origem]=1;    // inicialmente só se conhece o caminho minimo para a origem
    dist[origem]=0; // a distancia da origem a ela mesma é zero


    /* Laço principal */

    do {

        /* ja sabemos as distancias ate aos vizinhos de z */
        /* Encontrando o vertice que deve entrar em z */
        min=HUGE_VAL;
        for (i = 0; i < grafo->numOfVertices; i++)
            /* se o vertice ainda nao esta blockeado entra no if*/
            if (!z[i]){
                if (dist[i]>=0 && dist[i]<min){
                    min=dist[i];
                    v=i;
                }
            }

        /* Calculando as distâncias dos novos vizinhos de z */
        if (min!=HUGE_VAL && v!=destino) {
            z[v]=1; // bloqueia o vertice v
            no_aux = grafo->adjList[v];
            while (no_aux != NULL)
            {
                /* se o vertice ainda nao esta blockeado entra no if*/
                if (!z[i]) {
                    /*compara a distancia do ate ao nó blockeado mais 
                    a distancia do nó ate ao outro no de adjacencia com a distancia guardada*/
                    if (dist[v] + no_aux->cost < dist[no_aux->vertex]){
                        dist[no_aux->vertex] = dist[v] + no_aux->cost;
                        ant[no_aux->vertex]=v;
                    }
                }

                no_aux = no_aux->next;
            }
        }
    } while (v!=destino && min!=HUGE_VAL);
}
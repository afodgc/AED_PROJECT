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
 *          struct caminho_mais_curto resultado: contem o custo do caminho e um vetor de antecessores
 *
 * return: uma estrotura com o custo e um vetor com os antecessore de cada vertice
 *         se nao existir caminho o custo será -1
 * side efects: encontra o caminho mais curto entre dois vertices(neste caso entre duas palavras) 
 *              e o seu respetivo custo
 *
 *************************************************************************************************************************/
void dijkstra(int origem, int destino, Graph *grafo, struct caminho_mais_curto *resultado)
{
    int i, v;                          /* variáveis auxiliares */  
    short int z[grafo->numOfVertices]; /* vértices para os quais se conhece o caminho mínimo */
    float dist[grafo->numOfVertices];  /* vetor com os custos dos caminhos */
    double min;                        /* variável auxiliar */
    node *no_aux;                      /*no auxiliar*/

    resultado->ant = (int *)malloc(sizeof(int)*grafo->numOfVertices); /* vetor dos antecessores */
    

    /* Inicializacoes */
    for (int i = 0; i < grafo->numOfVertices; i++)
    {
        /* distancias inicalmente a infinito */
        dist[i] = HUGE_VAL;
        /* desconhecido o caminho minimo (z[vertice]=0) */
        z[i] = 0;
        /* inicialmente ningem tem antecessor */
        resultado->ant[i] = -1;
    }

    /* carrega os custos dos vertices que estao ligados a origem*/
    no_aux = grafo->adjList[origem];
    while (no_aux != NULL)
    {
        dist[no_aux->vertex] = no_aux->cost;

        /* todos os que estiverem nesta lista de adjacencias tem a origem como antecessor */
        resultado->ant[no_aux->vertex] = origem;

        no_aux = no_aux->next;
    }

    z[origem] = 1;    // inicialmente só se conhece o caminho minimo para a origem
    dist[origem] = 0; // a distancia da origem a ela mesma é zero

    /* Laço principal */

    do
    {

        /* ja sabemos as distancias ate aos vizinhos de z */
        /* Encontrando o vertice que deve entrar em z */
        min = HUGE_VAL;
        for (i = 0; i < grafo->numOfVertices; i++)
            /* se o vertice ainda nao esta blockeado entra no if*/
            if (!z[i])
            {
                if (dist[i] >= 0 && dist[i] < min)
                {
                    min = dist[i];
                    v = i;
                }
            }

        /* Calculando as distâncias dos novos vizinhos de z */
        if (min != HUGE_VAL && v != destino)
        {
            z[v] = 1; // bloqueia o vertice v
            no_aux = grafo->adjList[v];
            while (no_aux != NULL)
            {
                /* se o vertice ainda nao esta blockeado entra no if*/
                if (!z[i])
                {
                    /*compara a distancia do ate ao nó blockeado mais
                    a distancia do nó ate ao outro no de adjacencia com a distancia guardada*/
                    if (dist[v] + no_aux->cost < dist[no_aux->vertex])
                    {
                        dist[no_aux->vertex] = dist[v] + no_aux->cost;
                        resultado->ant[no_aux->vertex] = v;
                    }
                }

                no_aux = no_aux->next;
            }
        }
    } while (v != destino && min != HUGE_VAL);

    // se não existir caminho min é inifinito
    // para facilitar retornamos apenas -1
    if (min == HUGE_VAL){
        min = -1;
    }
    resultado->custo = min;

    /*retorna uma estrotura que foi passada por argumentos*/
    return;
}
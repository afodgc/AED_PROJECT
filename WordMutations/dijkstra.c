#include "headers.h"
#include "dicionario.h"
#include "graph.h"
#include <math.h>

#define P (wt[v] + t->cost)

void GRAPHpfs(Graph *G, int s, int *st, float *wt, int numOfMutations)
{
    int PQsize;
    int *pq, *qp;
    int custo_max = numOfMutations * numOfMutations;

    pq = (int *)calloc(G->numOfVertices + 1, sizeof(int));
    qp = (int *)calloc(G->numOfVertices + 1, sizeof(int));

    int v, w;
    node *t;
    PQinit(&PQsize);
    for (v = 0; v < G->numOfVertices; v++)
    {
        st[v] = -1;
        wt[v] = HUGE_VAL;
        PQinsert(v, pq, qp, &PQsize, wt);
    }

    wt[s] = 0.0;
    PQchange(s, PQsize, pq, qp, wt);
    while (!PQempty(PQsize))
        if (wt[v = PQdelmin(&PQsize, pq, qp, wt)] != HUGE_VAL)
            for (t = G->adjList[v]; t != NULL; t = t->next)
                if (wt[w = t->vertex] > P && t->cost <= custo_max)
                {
                    wt[w] = P;
                    PQchange(w, PQsize, pq, qp, wt);
                    st[w] = v;
                }

    free(qp);
    free(pq);
}

void exch(int i, int j, int *pq, int *qp)
{
    int t;

    t = qp[i];
    qp[i] = qp[j];
    qp[j] = t;

    pq[qp[i]] = i;
    pq[qp[j]] = j;
}

void PQinit(int *PQsize)
{
    *PQsize = 0;

    return;
}

void PQinsert(int k, int *pq, int *qp, int *PQsize, float *wt)
{
    qp[k] = ++(*PQsize);
    pq[*PQsize] = k;
    fixUp(pq, k, qp, wt);
}

void fixDown(int *pq, int k, int N, int *qp, float *wt)
{
    int j;
    while (2 * k <= N - 1)
    {
        j = 2 * k;
        if (j < (N - 1) && less(pq[j], pq[j + 1], wt))
            j++;
        if (!less(pq[k], pq[j], wt))
            break;
        exch(pq[k], pq[j], pq, qp);
        k = j;
    }
}

// tem de comparar com os weights
int less(int i, int j, float *wt)
{
    if (wt[i] < wt[j])
        return 1;
    return 0;
}

void PQchange(int k, int PQsize, int *pq, int *qp, float *wt)
{
    fixUp(pq, qp[k], qp, wt);
    fixDown(pq, qp[k], PQsize, qp, wt);
}

int PQdelmin(int *PQsize, int *pq, int *qp, float *wt)
{
    exch(pq[0], qp[*PQsize - 1], pq, qp);
    fixDown(pq, 0, *PQsize - 1, qp, wt);
    return pq[--(*PQsize)];
}

/************************************************************************************************************************
 *
 * dijkstra() - função que realiza o algoritmo dijkstra
 * arguments:
 *          int origem:     index do vertice de origem do problema
 *          int destino:    index do vertice de destino do problema
 *          graph *grafo:   grafo com:(numOfVertices, numOfEdges, wordSize, numOfMutations, **adjList)
 *          struct caminho_mais_curto resultado: contem o custo do caminho e um vetor de antecessores
 *          int numOfmutations:   numero de caracteres que são permitidos trocar
 *
 * return: uma estrotura com o custo e um vetor com os antecessore de cada vertice
 *         se nao existir caminho o custo será -1
 * side efects: encontra o caminho mais curto entre dois vertices(neste caso entre duas palavras)
 *              e o seu respetivo custo
 *
 *************************************************************************************************************************/
// void dijkstra(int origem, int destino, Graph *grafo, Caminho *resultado, int numOfmutations)

// {
//     int i = 0, v = 0;                                /* variáveis auxiliares */
//     short int z[grafo->numOfVertices];               /* vértices para os quais se conhece o caminho mínimo */
//     float dist[grafo->numOfVertices];                /* vetor com os custos dos caminhos */
//     double min;                                      /* variável auxiliar */
//     node *no_aux;                                    /* no auxiliar */
//     int custo_max = numOfmutations * numOfmutations; /* custo máximo que cada aresta pode ter */

//     resultado->ant = (int *)malloc(sizeof(int) * grafo->numOfVertices); /* vetor dos antecessores */

//     /* Inicializacoes */
//     for (int i = 0; i < grafo->numOfVertices; i++)
//     {
//         /* distancias inicalmente a infinito */
//         dist[i] = HUGE_VAL;
//         /* desconhecido o caminho minimo (z[vertice]=0) */
//         z[i] = 0;
//         /* inicialmente ningem tem antecessor */
//         resultado->ant[i] = -1;
//     }

//     /* carrega os custos dos vertices que estao ligados a origem*/
//     no_aux = grafo->adjList[origem];
//     while (no_aux != NULL)
//     {
//         // verifiacar se a aresta tem o custo permitido
//         if (no_aux->cost > custo_max)
//         {
//             no_aux = no_aux->next;
//             continue;
//         }

//         dist[no_aux->vertex] = no_aux->cost;

//         /* todos os que estiverem nesta lista de adjacencias tem a origem como antecessor */
//         resultado->ant[no_aux->vertex] = origem;

//         no_aux = no_aux->next;
//     }

//     z[origem] = 1;    // inicialmente só se conhece o caminho minimo para a origem
//     dist[origem] = 0; // a distancia da origem a ela mesma é zero

//     /* Laço principal */

//     do
//     {

//         /* ja sabemos as distancias ate aos vizinhos de z */
//         /* Encontrando o vertice que deve entrar em z */
//         min = HUGE_VAL;
//         for (i = 0; i < grafo->numOfVertices; i++)
//         {
//             /* se o vertice ainda nao esta blockeado entra no if*/
//             if (!z[i])
//             {
//                 if (dist[i] > 0 && dist[i] < min)
//                 {
//                     min = dist[i];
//                     v = i;
//                 }
//             }
//         }

//         /* Calculando as distâncias dos novos vizinhos de z */
//         if (min != HUGE_VAL && v != destino)
//         {
//             z[v] = 1; // bloqueia o vertice v
//             no_aux = grafo->adjList[v];
//             while (no_aux != NULL)
//             {
//                 /* se o vertice ainda nao esta blockeado entra no if*/
//                 if (!z[no_aux->vertex])
//                 {
//                     /*compara a distancia do ate ao nó blockeado mais
//                     a distancia do nó ate ao outro no de adjacencia com a distancia guardada*/
//                     /* verifiacar se a aresta tem o custo permitido */
//                     if (dist[v] + no_aux->cost < dist[no_aux->vertex] && no_aux->cost <= custo_max)
//                     {
//                         dist[no_aux->vertex] = dist[v] + no_aux->cost;
//                         resultado->ant[no_aux->vertex] = v;
//                     }
//                 }

//                 no_aux = no_aux->next;
//             }
//         }
//     } while (v != destino && min != HUGE_VAL);

//     // se não existir caminho min é inifinito
//     // para facilitar retornamos apenas -1
//     if (min == HUGE_VAL)
//     {
//         min = -1;
//     }
//     resultado->custo = min;

//     /*retorna uma estrutura que foi passada por argumentos*/
//     return;
// }
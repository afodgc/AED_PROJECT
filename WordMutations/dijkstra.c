#include "headers.h"
#include "dicionario.h"
#include "graph.h"
#include <math.h>

#define P (wt[v] + t->cost) // soma da distancia de um vertice com o custo de uma aresta

void dijkstra(Graph *G, int origem, int destino, int *st, float *wt, int numOfMutations)
{
    Queue queue;
    int custo_max = numOfMutations * numOfMutations;
    int v, w; // variaveis auxiliares
    node *t;  // node auxiliar

    // inicialização da fila
    PQinit(&queue, G->numOfVertices);

    // inicializa o vetor de antecessores e as distancias a infinito
    for (int v = 0; v < G->numOfVertices; v++)
    {
        st[v] = -1;
        wt[v] = HUGE_VAL;
    }

    wt[origem] = 0.0; // a distancia da origem a ela propria é 0
    PQinsert(&queue, origem, wt);

    /* percorre este ciclo até a fila de prioridades ficar vazia
       ou até ser descoberto o caminho mais curto até ao destino*/

    while ((PQempty(queue) != 0) && queue.pos[destino] != -2)
    {
        v = PQdelmin(&queue, wt);
        // percorre a lista de adjacencias do vertice com maior prioridade
        for (t = G->adjList[v]; t != NULL; t = t->next)
        {
            /* a distancia tem de ser menor que a distancia já calculada e do que a maxima */
            if ((wt[w = t->vertex] > P) && (t->cost <= custo_max))
            {
                wt[w] = P; // atualizar a distancia

                // se não estiver na fila tem de se adicionar primeiro
                if (!PQisInQueu(queue, w))
                {
                    PQinsert(&queue, w, wt);
                } else {
                    FixUp(&queue, w, wt);
                }
                st[w] = v;
            }
        }
    }

    PQfree(&queue);
}

/******************************************************
 * exch()
 *
 * argumets:
 *          Queu : fila
 *          index1 : index(heap) do primeiro elemnto na fila
 *          index2 : index(heap) do segundo elemto na fila
 *
 * side efects: troca dois elemntos numa lista de prioridades
 *******************************************************/
void exch(Queue *Queu, int index1, int index2)
{
    // esta está certa!
    int buffer;

    // alterar a fila de prioridades
    buffer = Queu->queu[index1];
    Queu->queu[index1] = Queu->queu[index2];
    Queu->queu[index2] = buffer;

    // alterar a pos(vetor position)
    Queu->pos[Queu->queu[index1]] = index1;
    Queu->pos[Queu->queu[index2]] = index2;
}

/*****************************************************************
 * inicializar a queu
 * argumets:
 *          Queu : fila
 *          size : numero de vertices do grafo
 *
 * side efects: aloca memoria para a fila e inicializa os seus valores
 *****************************************************************/
void PQinit(Queue *Queu, int size)
{
    // está certa
    Queu->queu = (int *)calloc(size, sizeof(int));
    Queu->pos = (int *)malloc(sizeof(int) * size);

    for (int i = 0; i < size; i++)
    {
        Queu->pos[i] = -1;
    }

    Queu->PQsize = 0;

    return;
}
/***********************************************************
 * PQfree()
 *
 * side efects: liberta a memoria usada para a fila
 ****************************************************************/
void PQfree(Queue *queu)
{
    free(queu->pos);
    free(queu->queu);
}

/**************************************************************
 * PQisInQueu()
 * 
 * argumets:
 *          Queu : fila de prioridades
 *          index : vertice
 *
 * return: retorna 1 se estiver na fila
 *         retorna 0 se não estiver na fila
 ***************************************************************/
int PQisInQueu(Queue Queu, int index)
{
    // se o pos[index] == -1 ou -2 quer dizer que não esstá na fila
    if (Queu.pos[index] == -1 || Queu.pos[index] == -2)
        return 0;

    return 1;
}

/****************************************************************************************
 * FixUp()
 *
 * arguments:
 *          Queu : fila
 *          indiceChange : indice do (vertice) que pode ter mudado de prioridade
 *          wt : vetor de distancias
 *
 * side efects: ajusta a prioridade de um elemento quando a sua prioridade aumenta
 ****************************************************************************************/
void FixUp(Queue *Queu, int indiceChange, float *wt)
{
    int indexNaQueu = Queu->pos[indiceChange];
    // int indexNaQueu = indiceChange;

    while (indexNaQueu > 0 && less(*Queu, ((indexNaQueu - 1) / 2), indexNaQueu, wt))
    {
        exch(Queu, indexNaQueu, ((indexNaQueu - 1) / 2));
        indexNaQueu = (indexNaQueu - 1) / 2; // subir um andar
    }
}

/***************************************************************************************************
 * fixDown()
 *
 * arguments:
 *          Queu : fila
 *          indiceChange : indice(vertice) do vertice que pode ter mudado de prioridade
 *          wt : vetor de distancias
 *
 * side efects: ajusta a prioridade de um elemento quando a sua prioridade diminui
 *****************************************************************************************************/
void fixDown(Queue *Queu, int indiceChange, float *wt)
{
    int child;                                 // indice do nó a descender
    int indexNaQueu = Queu->pos[indiceChange]; // valor do index que está a ser movido na queue

    while (2 * indexNaQueu < Queu->PQsize - 1) // irá fazer este ciclo até chegar ás folhas
    {
        child = 2 * indexNaQueu + 1; // index do seu primeiro filho na lista de prioridades

        if (child < (Queu->PQsize - 1))            // verifica se o elemento de index "child" não é o unico filho
            if (less(*Queu, child, child + 1, wt)) // se a prioridade do child for menor que o child + 1 vai comparar o child +1 com o pai
                child++;
        if (!less(*Queu, indexNaQueu, child, wt)) // compara a prioridade do pai com o filho de maior prioridade
            break;

        exch(Queu, indexNaQueu, child); // troca os elementos se chegar aqui
        indexNaQueu = child;            // muda o index para o index do filho para ser verificdo na proxima iteração
    }
}

/***************************************************************************************
 * less
 *
 * arguments:
 *           Queu : fila
 *           index1 : index(heap) do primeiro elemento na fila
 *           index2 : index(heap) do segundo elemento na fila
 *           wt : vetor com as distancias á origem
 *
 * side efects: retorna 1 se a distancia á origem do index1 for menor que o index2
 *************************************************************************************/
int less(Queue Queue, int index1, int index2, float *wt)
{
    if (wt[Queue.queu[index1]] > wt[Queue.queu[index2]])
        return 1;
    return 0;
}

/***************************************************************
 * PQempty()
 *
 * argumets:    queu : lista
 *
 * return: numero de elementos na fila
 *         se o a lista empty retorna 0
 ************************************************************/
int PQempty(Queue queu)
{
    return queu.PQsize;
}

/*****************************************************************
 * PQinsert()
 *
 * argumets:
 *          Queu: fila
 *          index: index(vertice) vertice que vai ser indserido
 *          wt: vetor das distancias à origem
 *
 * side efects: insere um elemento na fila
 ******************************************************************/
void PQinsert(Queue *Queu, int vertex, float *wt)
{
    Queu->pos[vertex] = Queu->PQsize;

    Queu->queu[Queu->PQsize] = vertex;

    Queu->PQsize++;
    FixUp(Queu, Queu->PQsize, wt);
}

/******************************************************************************
 * PQdelmin()
 *
 * argumets:
 *          queu: fila
 *          wt: vetor com as distancias à origem de todos os elementos
 *
 * retorna o index do elemento com mais prioridade da fila de prioridades
 *********************************************************************************/
int PQdelmin(Queue *queu, float *wt)
{
    int result = queu->queu[0]; // retirar o resultado

    exch(queu, 0, queu->PQsize - 1);

    queu->PQsize--;

    fixDown(queu, queu->queu[0], wt); // AQUI O FIX DOWN NAO SERIA COM 0??

    queu->pos[result] = -2; // mete o pos a -2 para indicar que já se sabe o caminho mais curto

    return result;
}

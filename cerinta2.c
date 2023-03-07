#include "graph.h"
#include "heap.h"


void decreaseKey(MinHeap *heap, int v, int dist)
{
    int i = heap->poz[v];
    heap->arr[i]->distanta = dist;
    while(i && (heap->arr[i]->distanta < heap->arr[(i-1)/2]->distanta))
    {
        HeapNode *iNode = heap->arr[i];
        HeapNode *pNode = heap->arr[(i-1)/2];
        heap->poz[iNode->v] = (i-1)/2;
        heap->poz[pNode->v] = i;
        HeapNode *aux = iNode;
        iNode = pNode;
        pNode = aux;
        i=(i-1)/2;
    }
}

/**
 *  Implementati Algoritmul Dijkstra folosindu-va de MinHeap-ul creat in fisierul heap.c
 * @param  g: graful dat
 * @param source : varful sursa pentru care se aplica algoritmul
 * @retval None
 */

DijkstraPath* Dijkstra(Graph *g, int source)
{
  int V = g->V;
  DijkstraPath *path = (DijkstraPath *) malloc(sizeof(DijkstraPath));
  if(path==NULL)
   return NULL;
  path->dist = (int *) malloc(V*sizeof(int));
  path->pred = (int *) malloc(V*sizeof(int));
  if((path->dist==NULL) || (path->pred==NULL))
    return NULL;
  for(int i=0; i<V; i++)
   {
       path->dist[i] = INT_MAX;
       path->pred[i] = -1;
   }
   MinHeap *heap = create(V);
   for(int i=0; i<V; i++)
   {
       heap->arr[i] = createHeapNode(i, path->dist[i]);
       heap->poz[i] = i;
   }
   heap->arr[source] = createHeapNode(source, path->dist[source]);
   heap->poz[source] = source;
   path->dist[source] = 0;
   decreaseKey(heap, source, 0);
   heap->size = V;
   while(heap->size>0)
   {
       HeapNode *root = deleteNode(heap);
       int u = root->v;
       for(int u1=0; u1<g->V; u1++)
       {
         int weight = g->mat[u][u1];
         if(weight>0 && heap->poz[u1]<heap->size)
         {
             if(path->dist[u]!=INT_MAX && weight+path->dist[u]<path->dist[u1])
             {
                 path->dist[u1] = path->dist[u]+weight;
                 path->pred[u1] = u;
                 decreaseKey(heap, u1, path->dist[u1]);
             }
         }
       }
   }
   return path;
}

/**
 *  Implementati Algoritmul Dijkstra folosindu-va de MinHeap-ul creat in fisierul heap.c
 * @param vectorPath : vectorul cailor
 * @param index : [optional pentru recursivitate]
 * @param vector_precedesori : vectorul de predecesori 
 * @param destinatie : varful destinatie pentru care se cauta path-ul
 * @param output : fisierul in care se face scrierea vectorului de predecesori (path.txt)
 * @note : se poate implementa atat recursiv, cat si iterativ
 *         nu mai trebuie facute alocari pentru vectorPath, vector_predecesori
 *         fisierul de output este deschis 
 * @retval None
 */
void printPath(int *vectorPath, int index, int *vector_precedesori, int destinatie, FILE *output) 
{
   int i=0;
   int node = destinatie;
   vectorPath[i] = destinatie;
   fprintf(output, "%d ", vectorPath[i]);
   while(vector_precedesori[node]!=-1)
   {
       i++;
       vectorPath[i] = vector_precedesori[node];
       fprintf(output, "%d ", vectorPath[i]);
       node = vector_precedesori[node];
   }
}

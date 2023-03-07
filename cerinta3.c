#include "graph.h"
#include "heap.h"
/**
 *  Implementati algoritmul Floyd-Warshall pentru un graf cu matricea de adiacenta data
 * @param  g: graful dat
 * @retval - Matricea costurilor pentru toate nodurile
 */
int **Floyd_Warshall(Graph *g)
{
    int V=g->V, i,j, k;
    int **dist1 = (int **) malloc(V*sizeof(int *));
    for(int l=0; l<V; l++)
      dist1[l] = (int *) malloc(V*sizeof(int));
   for(i=0; i<V; i++)
     for(j=0; j<V; j++)
     {
      if(g->mat[i][j]!=0)
        dist1[i][j] = g->mat[i][j];
       else
       dist1[i][j] = 99999;
     }
   for(k=0; k<g->V; k++)
    for(i=0; i<g->V; i++)
     for(j=0; j<g->V; j++)
     {
         if(dist1[i][j]>(dist1[i][k]+dist1[k][j]) && (dist1[i][k]!=0 && dist1[k][j]!=0))
          dist1[i][j] = dist1[i][k] + dist1[k][j];
     }
     return dist1;
}

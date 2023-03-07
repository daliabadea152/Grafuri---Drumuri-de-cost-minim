#include "graph.h"
#include "heap.h"
/**
 *  Implementati o functie care citeste dintr-un fisier de intrare
 * nr-ul de varfuri, muchii, iar pe urmatoarele linii
 * nod u, nod v si distanta[u][v], pentru a putea reprezenta ulterior matricea de adiacenta
 * @param  input: fisierul de intrare
 * @note   -Atentie! Nu redeschideti fisierul de intrare
 * @retval - Graful in reprezentarea matrice de adiacenta
 */
Graph* createGraph(FILE *input)
{
  int V,E,d,u1,u2;
  fscanf(input, "%d", &V);
  fscanf(input, "%d", &E);
  Graph *g = (Graph *) malloc(sizeof(Graph));
  g->V=V;
  g->E=E;
  g->mat = (int **) malloc(V*sizeof(int *));
  for(int i=0; i<V; i++)
   g->mat[i] = (int *) malloc(V*sizeof(int));
   for(int i=0; i<V; i++)
    for(int j=0; j<V; j++)
      g->mat[i][j] = 0;
   while(fscanf(input,"%d %d %d", &u1, &u2, &d)!=EOF)
     if(d!=0)
     {
         g->mat[u1][u2] = d;
         g->mat[u2][u1] = d;
     }
    return g;
}
/**
 * Implementati functia de afisare a matricei de adiacenta
 * @param  g: graful creat anterior
 * @note : Nice to have
 * @retval - None
 */
void printMat(Graph *g)
{
   for(int i=0; i<g->V; i++)
   {
       for(int j=0; j<g->V; j++)
        printf("%d ", g->mat[i][j]);
        printf("\n");
   }
}
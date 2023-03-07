#include "heap.h"
/**
 * Implementati functia de creare MinHeap avand o capacitate data
 * @param  capacitate: capacitatea heap-ului
 * @retval - heap-ul creat
 */
MinHeap* create(int capacitate) 
{
  MinHeap *minHeap = (MinHeap *) malloc(sizeof(MinHeap));
  minHeap->poz = (int *) malloc(capacitate*sizeof(int));
  minHeap->size = 0;
  minHeap->capacity = capacitate;
  minHeap->arr = (HeapNode **) malloc(capacitate*sizeof(HeapNode *));
  return minHeap;
}

/**
 * Implementati functia de creare HeapNode 
 * @param  v:  varful care trebuie adaugat
 * @param dist: distanta rezultata in urma implementarii algoritmului Dijkstra
 * @retval - HeapNode-ul creat
 */
HeapNode *createHeapNode(int v, int dist) 
{
  HeapNode *node = (HeapNode *) malloc(sizeof(HeapNode));
  node->v = v;
  node->distanta = dist;
  return node;
}

/**
 * Implementati functia de returnare a index-ului
 * parintelui unui nod din MinHeap
 * @param  heap: MinHeap-ul
 * @param  i: index-ul copilului
 * @retval - parintele copilului i
 */

int parent(MinHeap *heap, int i) 
{
  if(heap!=NULL)
  {
	  if(i>heap->size || i<=0)
	   return -1;
	return (i-1)/2;
  }
  return -1;
}
/**
 * Implementati functia de returnare a index-ului
 * copilului stang al unui nod
 * @param  heap: MinHeap-ul
 * @param  i: parintele i
 * @retval - copilul din stanga al parintelui i
 */

int leftChild(MinHeap *heap, int i) 
{
  if(heap!=NULL)
  {
	  int poz = 2*i+1;
	  if(poz>heap->size-1 || i<0)
	    return -1;
	  return poz;
  }
  else
    return -1;
  
}

/**
 * Implementati functia de returnare a index-ului
 * copilului drept al unui nod
 * @param  heap: MinHeap-ul
 * @param  i: parintele i
 * @retval - copilul din dreapta al parintelui i
 */
int rightChild(MinHeap *heap, int i) 
{
  if(heap!=NULL)
  {
	  int poz = 2*i+2;
	  if(poz>heap->size-1 || i<0)
	    return -1;
	  return poz;
  }
  else
   return -1;
}

/**
 * Implementati functia de returnare a radacinii
 * unui heap   
 * @param  heap: MinHeap-ul
 * @retval - HeapNode-ul in care este stocata radacina
 */
HeapNode* returnRoot(MinHeap *heap) 
{
  if(heap!=NULL)
  {
	  if(heap->size == 0)
	   return NULL;
	  if(heap->arr!=NULL)
	   return heap->arr[0];
  }
  else
   return NULL;
}

/**
 * Implementati functia heapify
 * @param  heap: MinHeap-ul
 * @param  i: pozitia de pe care se doreste
 * @retval None
 */
void heapify(MinHeap *heap, int i) 
{
  int l,r,min=i;
  l=2*i+1;
  r=2*i+2;
  if(l<heap->size && heap->arr[l]->distanta < heap->arr[i]->distanta)
    min=l;
  if(r<heap->size && heap->arr[r]->distanta < heap->arr[min]->distanta)
    min=r;
  if(min!=i)
  {
    HeapNode *minNode = heap->arr[min];
    HeapNode *iNode = heap->arr[i];
    heap->poz[minNode->v]=i;
    heap->poz[iNode->v]=min;
    HeapNode *aux=minNode;
    minNode=iNode;
    iNode=aux;
    heapify(heap, min);
  }
}
/**
 * Implementati functia de redimensionare a MinHeap-ului  
 * @param  heap: MinHeap-ul
 * @retval None
 */
void resize(MinHeap *heap) 
{
  int *poz1 = (int *) malloc(heap->capacity*sizeof(int));
  HeapNode **arr1 = (HeapNode **) malloc(heap->capacity*sizeof(HeapNode *));
  if(poz1==NULL)
   return;
  if(arr1==NULL)
    return;
  if(heap->poz!=NULL)
    free(heap->poz);
  if(heap->arr!=NULL)
    free(heap->arr);
   heap->poz = poz1;
   heap->arr = arr1;
}
/**
 * Implementati functia de inserare a unui nod in heap
 * @param  heap: MinHeap-ul
 * @param  x: HeapNode-ul care urmeaza a fi inserat
 * @retval None
 */
 
void insert(MinHeap *heap, HeapNode *x)
{ 
	int i;
	if(heap->size == heap->capacity)
	 resize(heap);
	i = heap->size;
	heap->size++;
	while(i>0 && x->distanta<heap->arr[(i-1)/2]->distanta)
	{
		heap->arr[i] = heap->arr[(i-1)/2];
		i = (i-1)/2;
	}
	heap->arr[i] = x;
	heap->poz[i] = x->v; 
}




/**
 * Implementati functia stergere a unui heap
 * @param  h: MinHeap-ul
 * @retval None
 */
void deleteMinHeap(MinHeap **heap)
{
  if((*heap)->poz!=NULL)
    free((*heap)->poz);
  if((*heap)->arr!=NULL)
    free((*heap)->arr);
  *heap=NULL;
	
}
/**
 * Implementati functia de afisare a unui heap
 * @param  heap: MinHeap-ul
 * @note : se va afisa si pozitia HeapNode-urilor, pe langa componentele HeapNode-ului
 * @retval None
 */
void printHeap(MinHeap *heap)
{
	//nice to have
}
/**
 * Implementati functia de stergere a radacinii
 * @param  heap: MinHeap-ul
 * @retval HeapNode-ul care s-a sters, fosta radacina
 */
HeapNode* deleteNode(MinHeap *heap)
{
  if(heap==NULL)
    return NULL;
  HeapNode *root = heap->arr[0];
  HeapNode *lastNode = heap->arr[heap->size-1];
  heap->arr[0] = lastNode;
  heap->poz[root->v] = heap->size-1;
  heap->poz[lastNode->v] = 0;
  heap->size = heap->size-1;
  heapify(heap, 0);
  return root;
}

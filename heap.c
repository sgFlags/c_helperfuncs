#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef char * HeapType;

typedef struct {
	HeapType *values;
	int size;
	int maxSize;
} Heap;

/*int _heapCompare(HeapType *first, HeapType *second)
{
	return (int)(*first - *second);
}*/
static inline int _heapCompare(HeapType *first, HeapType *second)
{
	int i;
	for (i = 0; (*first)[i] != '\0' && (*second)[i] != '\0'; i++) {
		if ((*first)[i] != (*second)[i])
			return (int)((*first)[i] - (*second)[i]);
	}
	if ((*first)[i] != '\0')
		return 1;
	else if ((*second)[i] != '\0')
		return -1;
	else
		return 0;
}

Heap *heapCreate(int size)
{
	Heap *heap = (Heap *)malloc(sizeof(Heap));
	heap->maxSize = size;
	heap->values = (HeapType *)malloc(sizeof(HeapType) * heap->maxSize);
	heap->size = 0;
	return heap;
}

void heapDestroy(Heap *heap)
{
	free(heap->values);
	free(heap);
}

static inline int getSize(Heap *heap)
{
	return heap->size;
}

void heapInsert(Heap *heap, HeapType val)
{
	int i;
	HeapType *temp = NULL;
	if (heap->size >= heap->maxSize) {
		heap->maxSize += 20;
		temp = heap->values;
		heap->values = (HeapType *)malloc(sizeof(HeapType) * heap->maxSize);
		memcpy(heap->values, temp, sizeof(HeapType) * heap->size);
		free(temp);
	}
	i = heap->size;
	heap->size++;
	while (i != 0) {
		int j = (i - 1) / 2;
		if (_heapCompare(&val, &heap->values[j]) >= 0)
			break;
		heap->values[i] = heap->values[j];
		i = j;
	}
	heap->values[i] = val;
}

void heapPop(Heap *heap)
{
	HeapType val;
	int i, j;
	if (!heap->size) {
		printf("error: in pop_heap, heap is empty!!\n");
		exit(1);
	}
	heap->size--;
	if (!heap->size)
		return;
	val = heap->values[heap->size];
	i = 0;
	j = 2 * i + 1;
	while (j <= heap->size - 1) {
		if (j < heap->size - 1 && _heapCompare(&heap->values[j], &heap->values[j + 1]) >= 0)
			j = j + 1;
		if (_heapCompare(&val, &heap->values[j]) < 0)
			break;
		heap->values[i] = heap->values[j];
		i = j;
		j = 2 * i + 1;
	}
	heap->values[i] = val;
}

static inline HeapType heapPeek(Heap *heap)
{
	return heap->values[0];
}

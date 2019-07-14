#pragma once
#include<stdio.h>
#include<stdlib.h>
#define HEAPMAXSIZE		100
typedef int HeapType;

typedef struct heap_t {
	HeapType values[HEAPMAXSIZE];
	int size;
	int maxSize;
} Heap;

int heap_compare(HeapType *first, HeapType *second)
{
	return (int)(*first - *second);
}

Heap *heap_create()
{
	Heap *heap = (Heap *)malloc(sizeof(Heap));
	heap->maxSize = HEAPMAXSIZE;
	heap->size = 0;
	return heap;
}

void heap_destroy(Heap *heap)
{
	free(heap);
}

int get_size(Heap *heap)
{
	return heap->size;
}

void heap_insert(Heap *heap, HeapType val)
{
	int i;
	//heap->values[heap->size++] = val;
	i = heap->size;
	heap->size++;
	while (i != 0) {
		int j = (i - 1) / 2;
		if (heap_compare(&val, &heap->values[j]) >= 0)
			break;
		heap->values[i] = heap->values[j];
		i = j;
	}
	heap->values[i] = val;
}

void heap_pop(Heap *heap)
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
		if (j < heap->size - 1 && heap_compare(&heap->values[j], &heap->values[j + 1]) >= 0)
			j = j + 1;
		if (heap_compare(&val, &heap->values[j]) < 0)
			break;
		heap->values[i] = heap->values[j];
		i = j;
		j = 2 * i + 1;
	}
	heap->values[i] = val;
}

HeapType heap_peek(Heap *heap)
{
	return heap->values[0];
}
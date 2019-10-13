#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef int VectorType;

typedef struct {
	VectorType *values;
	int maxSize;
	int size;
} Vector;

Vector *vectorCreate(int size)
{
	Vector *vector = (Vector *)malloc(sizeof(Vector));
	vector->values = (VectorType *)malloc(sizeof(VectorType) * size);
	vector->size = 0;
	vector->maxSize = size;
	return vector;
}

static inline void vectorDestroy(Vector *vector)
{
	free(vector->values);
	free(vector);
}

static inline void vectorAdd(Vector *vector, VectorType value)
{
	VectorType *temp = NULL;
	if (vector->size >= vector->maxSize) {
		vector->maxSize += 20;
		temp = vector->values;
		vector->values = (VectorType *)malloc(sizeof(VectorType) * vector->maxSize);
		memcpy(vector->values, temp, sizeof(VectorType) * vector->size);
		free(temp);
	}
	vector->values[vector->size++] = value;
}

static inline VectorType vectorGet(Vector *vector, int index)
{
	return vector->values[index];
}

static inline VectorType vectorPeek(Vector *vector)
{
	return vector->values[vector->size - 1];
}

static inline void vectorPop(Vector *vector)
{
	vector->size--;
}

static inline int getSize(Vector *vector)
{
	return vector->size;
}

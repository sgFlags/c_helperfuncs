#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef char * VECTORTYPE;

typedef struct {
	VECTORTYPE *values;
	int maxSize;
	int size;
} Vector;

Vector *vectorCreate(int size)
{
	Vector *vector = (Vector *)malloc(sizeof(Vector));
	vector->values = (VECTORTYPE *)malloc(sizeof(VECTORTYPE) * size);
	vector->size = 0;
	vector->maxSize = size;
	return vector;
}

inline void vectorAdd(Vector *vector, VECTORTYPE value)
{
	VECTORTYPE *temp;
	if (vector->size >= vector->maxSize) {
		vector->maxSize += 20;
		temp = vector->values;
		vector->values = (VECTORTYPE *)malloc(sizeof(VECTORTYPE) * vector->maxSize);
		memcpy(vector->values, temp, sizeof(VECTORTYPE) * vector->size);
	}
	vector->values[vector->size++] = value;
}

inline VECTORTYPE vectorGet(Vector *vector, int index)
{
	return vector->values[index];
}

inline VECTORTYPE vectorPeek(Vector *vector)
{
	return vector->values[vector->size - 1];
}

inline void vectorPop(Vector *vector)
{
	vector->size--;
}

inline int getSize(Vector *vector)
{
	return vector->size;
}

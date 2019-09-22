#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	int left;
	int right;
} Range;



typedef Range VectorType;

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

inline void vectorDestroy(Vector *vector)
{
	free(vector->values);
	free(vector);
}

inline void vectorAdd(Vector *vector, VectorType value)
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

inline VectorType vectorGet(Vector *vector, int index)
{
	return vector->values[index];
}

inline VectorType vectorPeek(Vector *vector)
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





int m1, m2, n;
int *a;
int left = 0;
int right = 0;
int minValue, minIndex, maxValue, maxIndex;
int maxLength = 0;
Vector *rangeVector = NULL;

int updateBorder(int index)
{
	if (a[index] > maxValue) {
		maxValue = a[index];
		maxIndex = index;
	}
	else if (a[index] < minValue) {
		minValue = a[index];
		minIndex = index;
	}
	return maxValue - minValue;
}

void findStart()
{
	int diff;
	while (right < n) {
		diff = updateBorder(right);
		if (diff <= m2 && diff >= m1) {
			maxLength = right - left + 1;
			return;
		}
		if (diff > m2)
			left = right;
		right++;
	}
}

void reallocVector()
{
	vectorDestroy(rangeVector);
	rangeVector = vectorCreate(n);
}

int updateMin(int start)
{
	int i;
	int minV = maxValue;
	int minI = start;
	for (i = start; i <= right; i++) {
		if (a[i] < minV) {
			minV = a[i];
			minI = i;
		}
	}
	minValue = minV;
	minIndex = minI;
	return maxValue - minValue;
}

void updateVector()
{
	int currLength;
	Range rg;
	currLength = right - 1 - left + 1;
	if (currLength > maxLength) {
		reallocVector();
		maxLength = currLength;
	}
	if (maxLength == currLength) {
		rg = { left, right - 1 };
		vectorAdd(rangeVector, rg);
	}
}

int main()
{
	int i;
	int diff;
	int currLength;
	scanf_s("%d %d %d", &m1, &m2, &n);
	rangeVector = vectorCreate(n);
	a = (int *)malloc(sizeof(int) * n);
	for (i = 0; i < n; i++) {
		scanf_s("%d", &a[i]);
	}
	minValue = maxValue = a[0];
	minIndex = maxIndex = 0;
	findStart();
	while (right < n) {
		diff = updateBorder(right);
		while (diff <= m2) {
			right++;
			diff = updateBorder(right);
		}
		
		updateVector();

		while (diff > m2) {
			left = minIndex + 1;
			diff = updateMin(left);
		}
	}

	updateVector();

	for (i = 0; i < getSize(rangeVector); i++) {
		printf("%d %d\n", vectorGet(rangeVector, i).left, vectorGet(rangeVector, i).right);
	}
	system("pause");
}

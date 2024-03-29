#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef int DequeType;

typedef struct {
	DequeType *values;
	int maxSize;
	int size;
	int head;
	int tail;
} Deque;

Deque *dequeCreate(int size)
{
	Deque *deque = (Deque *)malloc(sizeof(Deque));
	deque->maxSize = size;
	deque->size = 0;
	deque->head = 0;
	deque->tail = deque->maxSize - 1;
	deque->values = (DequeType *)malloc(sizeof(DequeType) * deque->maxSize);
	return deque;
}

static inline int _formalize(int number, int max)
{
	return (number + max) % max;
}

static inline void _dequeRealloc(Deque *deque)
{
	DequeType *temp = NULL;
	int firstHalf = deque->head;
	int secondHalf = deque->maxSize - deque->head;
	deque->maxSize += 100;
	temp = deque->values;
	deque->values = (DequeType *)malloc(sizeof(DequeType) * deque->maxSize);
	/* bai change */
	memcpy(deque->values, &temp[deque->head], secondHalf * sizeof(DequeType));
	memcpy(&deque->values[secondHalf], temp, firstHalf * sizeof(DequeType));
	deque->head = 0;
	deque->tail = deque->size - 1;
	free(temp);
}

static inline void dequeAddHead(Deque *deque, DequeType value)
{
	if (deque->size >= deque->maxSize) {
		_dequeRealloc(deque);
	}
	deque->head = _formalize(deque->head - 1, deque->maxSize);
	deque->values[deque->head] = value;
	deque->size++;
}

static inline void dequeAddTail(Deque *deque, DequeType value)
{
	if (deque->size >= deque->maxSize) {
		_dequeRealloc(deque);
	}
	deque->tail = _formalize(deque->tail + 1, deque->maxSize);
	deque->values[deque->tail] = value;
	deque->size++;
}

static inline DequeType dequePeekHead(Deque *deque)
{
	return deque->values[deque->head];
}

static inline DequeType dequePeekTail(Deque *deque)
{
	return deque->values[deque->tail];
}

static inline void dequePopHead(Deque *deque)
{
	deque->head = _formalize(deque->head + 1, deque->maxSize);
	deque->size--;
}

static inline void dequePopTail(Deque *deque)
{
	deque->tail = _formalize(deque->tail - 1, deque->maxSize);
	deque->size--;
}

static inline DequeType dequeGet(Deque *deque, int index)
{
	return deque->values[(deque->head + index) % deque->maxSize];
}

static inline int getSize(Deque *deque)
{
	return deque->size;
}

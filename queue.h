#pragma once
#include <stdlib.h>
#include <stdio.h>
#define QUEUEMAXSIZE	5
typedef struct bai2 {
	int a;
	char str[10];
} QueueType;

typedef struct queue_t {
	QueueType values[QUEUEMAXSIZE];
	int size;
	int head;
	int tail;
	int maxSize;
} Queue;

Queue * queue_create()
{
	Queue *queue = (Queue *)malloc(sizeof(Queue));
	queue->size = 0;
	queue->head = 0;
	queue->tail = 0;
	queue->maxSize = QUEUEMAXSIZE;
	return queue;
}

void queue_add(Queue *queue, QueueType val)
{
	queue->values[queue->tail++ % queue->maxSize] = val;
	queue->size++;
}

QueueType queue_peek(Queue *queue)
{
	if (!queue->size)
		printf("error: in peek_queue, queue is empty!!\n");
	return queue->values[queue->head % queue->maxSize];
}

void queue_pop(Queue *queue)
{
	if (!queue->size)
		printf("error: in pop_queue, queue is empty!!\n");
	queue->size--;
	queue->head++;
}

void queue_destroy(Queue *queue)
{
	free(queue);
}

int get_size(Queue *queue)
{
	return queue->size;
}
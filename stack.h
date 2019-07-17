#include <stdlib.h>
#include <stdio.h>
#define STACKMAXSIZE	100

typedef char StackType;

typedef struct stack_t {
	StackType *values;
	int maxSize;
	int size;
} Stack;

Stack * stack_create()
{
	Stack *stack = (Stack *)malloc(sizeof(struct stack_t));
	stack->maxSize = STACKMAXSIZE;
	stack->values = (StackType *)malloc(sizeof(StackType) * stack->maxSize);
	stack->size = 0;
	//stack->values = (StackType *)malloc(sizeof(StackType) * maxSize);
	return stack;
}

void stack_destroy(Stack *stack)
{
	//free(stack->values);
	free(stack);
}

void stack_push(Stack *stack, StackType val)
{
	if (stack->size >= stack->maxSize) {
		stack->maxSize += 20;
		stack->values = (StackType *)realloc(stack->values, sizeof(StackType) * stack->maxSize);
	}
	stack->values[stack->size++] = val;
}

StackType stack_peek(Stack *stack)
{
	if (!stack->size)
		printf("error: in peek_stack, stack is empty!!\n");
	return stack->values[stack->size - 1];
}

void stack_pop(Stack *stack)
{
	if (!stack->size)
		printf("error: int pop_stack, stack is empty!!\n");
	stack->size--;
}

int get_size(Stack *stack)
{
	return stack->size;
}


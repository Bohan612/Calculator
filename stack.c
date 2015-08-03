#include "main.h"

Item stack[MAXLEN];
int top = 0;

void push(Item i)
{
	if (top > MAXLEN -1)
		printf("Error: Stack overflowed."), exit(1);
	
	stack[top] = i;
	++top;
}

Item* pop()
{
	if (top == 0)
		printf("Error: stack empty, can't pop."), exit(1);
	
	--top;
	return &stack[top];
}

int isEmpty()
{
	return top == 0 ? 1 : 0;
}

Item* peek()
{
	if (top == 0)
		printf("Error: stack empty, can't peek."), exit(1);
		
	return &stack[top - 1];
}

int height()
{
	return top;
}


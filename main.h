#include <stdio.h>
#include <stdlib.h>

#define MAXLEN 1000

typedef struct 
{
	char exprL, exprR[MAXLEN];	
	double lr, rr;
	char op;
	int lf, rf = 0;
} Item;

int mgetline(char s[], int lim);
void push(Item i);
Item pop();
int isEmpty();
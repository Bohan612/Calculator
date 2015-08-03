#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 1000

typedef struct 
{
	char exprL[MAXLEN], exprR[MAXLEN];	
	double lr, rr;
	char op;
	int ld, rd;		//// left, right done.
	int resOf;		//// Result of 0 -> left, 1 -> right.
} Item;

int mgetline(char s[], int lim);
void push(Item i);
Item* pop();
int isEmpty();
Item* peek();
int parseExpr(char expr[], int resOf);
void print(char s[]);
int height();
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAXLEN 1000
#define STACKHEIGHT 10

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
void print(char form[], char s[]);
int height();
void mstrncpy(char s1[], char s2[], int n);
char * cleanExpr(char expr[]);
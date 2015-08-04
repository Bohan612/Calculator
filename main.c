//// Hours: 8 + 1.5 + 1 + 1 + 1 + 4
//// Resolve strncpy, strcpy
//// MS A: only integer, no parensis, only positive number, only basic operations.
//// MS B: Support double.
//// MS C: Support parensis.

#include "main.h"

char line[MAXLEN];

int main()
{
	int len;
	while (len = mgetline(line, MAXLEN) > 0)
	{
		int isNum = parseExpr(line, -1);
		if (isNum)
		{
			printf("= %s\n", line);
		}
		
		print("%s\n", "FW.");
		
		while (!isEmpty())
		{
			//printf("SW. top: %d\n", height());
			
			Item* item = peek();
			
			if (item->ld == 0)
			{
				print("%s\n", "a");
				//// push left onto stack
				//printf("item->exprL : %s\n", item->exprL);
				int isNum = parseExpr(item->exprL, 0);
				//printf("isNum : %d\n", isNum);
				if (isNum)
				{
					double res = atof(item->exprL);
					//printf("res : %d\n", res);
					item->lr = res;
					item->ld = 1;
				}
			}
			else if (item->rd == 0)
			{
				print("%s\n", "b");
				int isNum = parseExpr(item->exprR, 1);
				if (isNum)
				{
					double res = atof(item->exprR);
					//printf("res : %d\n", res);
					item->rr = res;
					item->rd = 1;					
				}
			}
			else
			{
				print("%s\n", "c");
				//// Both right left done, perform operation.
				double value;
				if (item->op == '+')
					value = item->lr + item->rr;
				else if (item->op == '-')
					value = item->lr - item->rr;
				else if (item->op == '*')
					value = item->lr * item->rr;
				else if (item->op == '/')
					value = item->lr / item->rr;
					
				//printf("expr: %f, %c, %f\n", item->lr, item->op, item->rr);
				//printf("value: %d\n", value);
					
				Item* justPop = pop();
				
				if (!isEmpty())
				{
					Item* newItem = peek();
					if (item->resOf == 0)
					{
						newItem->lr = value;
						newItem->ld = 1;
					}
					else if (item->resOf == 1)
					{
						newItem->rr = value;
						newItem->rd = 1;
					}
				}
				else
				{
					printf("= %f\n", value);
				}
			}
		}
	}
	
	return 0;
}

//// return 1 if Expr is a number, 0 if not. If is number, nothing gets pushed to stack.
int parseExpr(char expr[], int resOf)
{
	//printf("expr %s\n", expr);
		int op_1 = 0;
		int op_2 = 0;
		int opToUse = 0;
		int skip = 0;
		int skipL = 0;
		
		//// Get rid of parensis.
		if (expr[0] == '(' && expr[strlen(expr) - 1] == ')')
		{
			expr = &expr[1];
			expr[strlen(expr) - 1] = '\0';
		}
		
		//// Determine operation.
		int i;
		for(i = 0; expr[i] != '\0'; ++i)
		{
			char ch = expr[i];
			
			if (ch == '(')
				skip = 1, ++skipL;
			else if (ch == ')')
			{
				--skipL;
				if (skipL == 0)
					skip = 0;
			}
			
			if (!skip)
			{
				if (ch == '-' || ch == '+')
					op_1 = i;
				else if (ch == '*' || ch == '/')
					op_2 = i;
			}
		}
		
		//// Determine priority.
		if (op_1 > 0)
			opToUse = op_1;
		else if (op_2 > 0)
			opToUse = op_2;
		else
			opToUse = 0;
		
		if (opToUse > 0)
		{
			//printf("opToUse %d\n", opToUse);
			Item newItem;
			mstrncpy(newItem.exprL, expr, opToUse);
			strcpy(newItem.exprR, &expr[opToUse + 1]); 
			//printf("L: %s, R: %s\n\n", newItem.exprL, newItem.exprR);
			newItem.op = expr[opToUse]; 
			newItem.ld = 0; 
			newItem.rd = 0; 
			newItem.resOf = resOf;
			push(newItem);
			return 0;
		}
		else
		{
			//// Whole string is a number.
			return 1;
		}
}

void print(char form[], char s[])
{
	return;
	printf(form, s);
}

void mstrncpy(char s1[], char s2[], int n)
{
	int i = 0;
	for (;i < n; ++i)
	{
		s1[i] = s2[i];
	}
	
	s1[i] = '\0';
}




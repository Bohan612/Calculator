//// Hours: 8 + 1.5 + 1 + 1 + 1
//// Resolve strncpy, strcpy
//// Draft A: no parensis, only integer, only basic operations.

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
		
		print("First while.");
		
		while (!isEmpty())
		{
			printf("second while. top: %d\n", height());
			
			Item* item = peek();
			
			if (item->ld == 0)
			{
				print("a");
				//// push left onto stack
				int isNum = parseExpr(item->exprL, 0);
				printf("isNum : %d\n", isNum);
				if (isNum)
				{
					int res = atoi(item->exprL);
					printf("res : %d\n", res);
					item->lr = res;
					item->ld = 1;
				}
			}
			else if (item->rd == 0)
			{
				print("b");
				int isNum = parseExpr(item->exprR, 1);
				if (isNum)
				{
					int res = atoi(item->exprR);
					item->rr = res;
					item->rd = 1;					
				}
			}
			else
			{
				print("c");
				//// Both right left done, perform operation.
				int value;
				if (item->op == '+')
					value = item->lr + item->rr;
				else if (item->op == '-')
					value = item->lr - item->rr;
				else if (item->op == '*')
					value = item->lr * item->rr;
				else if (item->op == '/')
					value = item->lr / item->rr;
					
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
					printf("= %d\n", value);
				}
			}
		}
	}
	
	return 0;
}

//// return 1 if Expr is a number, 0 if not. If is number, nothing gets pushed to stack.
int parseExpr(char expr[], int resOf)
{
		int op_1 = 0;
		int op_2 = 0;
		int opToUse = 0;
		int i;
		for(i = 0; expr[i] != '\0'; ++i)
		{
			char ch = expr[i];
			if (ch == '-' || ch == '+')
				op_1 = i;
			else if (ch == '*' || ch == '/')
				op_2 = i;
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
			Item newItem;
			strncpy(newItem.exprL, expr, opToUse - 1);
			strcpy(newItem.exprR, &expr[opToUse + 1]); 
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

void print(char s[])
{
	printf("%s\n", s);
}




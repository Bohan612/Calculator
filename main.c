//// Hours: 8 + 1.5 + 1 + 1 + 1 + 4 + 2 + 1 + 1 + 1.5
//// Resolve strncpy, strcpy
//// MS A: only integer, no parensis, only positive number, only basic operations.
//// MS B: Support double.
//// MS C: Support parensis.
//// MS D: Support negative number.
//// MS E: Add ^ operation.

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
				char * ptrL = cleanExpr(item->exprL);
				int isNum = parseExpr(ptrL, 0);
				//printf("isNum : %d\n", isNum);
				if (isNum)
				{
					double res = atof(ptrL);
					//printf("ptrL: %s,res : %f\n", ptrL, res);
					item->lr = res;
					item->ld = 1;
				}
			}
			else if (item->rd == 0)
			{
				print("%s\n", "b");
				char * ptrR = cleanExpr(item->exprR);
				int isNum = parseExpr(ptrR, 1);
				if (isNum)
				{
					double res = atof(ptrR);
					//printf("ptrR: %s,res : %f\n", ptrR, res);
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

char * cleanExpr(char expr[])
{
	//// Get rid of white spaces, return symbols, then parensis.
	int j = 0;
	while(expr[j] == ' ')
		++j;
		
	expr = &expr[j];
	
	char * ptr = &expr[strlen(expr) - 1];
	while (*ptr == ' '  || *ptr == '\r' || *ptr == '\n')
		--ptr;
	
	*(ptr + 1) = '\0';
	
	//printf("expr[0] %c, *ptr %c\n", expr[0], *ptr);
	
	if (expr[0] == '(' && *ptr == ')')
	{
		int notTrimYet = 0;
		int k; 
		for(k=1; k<strlen(expr)-1;++k)
			if (expr[k] == '(')
				break;
			else if (expr[k] == ')')
				notTrimYet = 1;
			
		if (!notTrimYet)
		{
			expr = &expr[1];
			*ptr = '\0';
		}
	}
	
	return expr;
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
	
	//printf("%s\n", expr);
	
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
			else if (skipL < 0)
				printf("Error: unbalanced parensis."), exit(1);
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
		//printf("expr str: %s\n", expr);
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




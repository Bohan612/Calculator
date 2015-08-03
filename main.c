#include "main.h"

char line[MAXLEN];
int pl = 0;		//// parensis level.

int main()
{
	int len;
	while (len = mgetline(line, MAXLEN) > 0)
	{
		
		int priOp_1 = 0;
		int priOp_2 = 0;
		int i;
		for(i = 0; line[i] != '\0'; ++i)
		{
			char ch = line[i];
			if (ch == '-' || ch == '+')
				priOp_1 = i;
			else if (ch == '*' || ch == '/')
				priOp_2 = i;
		}
		
		if (priOp_1 > 0)
		{
			Item priItem_1;
			priItem_1.exprR = "": ////... 
		}
		else if (priOp_2 > 0)
		{
		}
		else
		{
		}
	}
	
	return 0;
}
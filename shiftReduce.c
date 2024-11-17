#include <stdio.h>
#include <stdbool.h>
#include <string.h>

void main() {
	char buff[100];
	char rules[4][10] = {"E+E", "E*E", "(E)","a"};
	char stack[100];
	int top = -1;

	printf("Input String: ");
		scanf("%s", buff);
	strcat(buff, "$");

	int index = 0;
    printf("Stack\t\tInput\t\tProcess\n");
	do {
		if (top != -1) {
			int i;
			for (i = 0; i < 4; ++i)
				if (strstr(stack, rules[i]) != NULL)
					break;
			if (i < 4) {
				// Reduce
				char *p;
				p = strstr(stack, rules[i]);
				p[0] = 'E';
				p[1] = '\0';
				top = (int)(p - stack);
				printf("%s\t\t%s\t\tReduced E->%s \n",stack,&buff[index],rules[i]);
			}
			else {
				// Shift
				int before=index;
				stack[++top] = buff[index++];
				stack[top + 1] = '\0';
				if(strcmp(stack,"E$")!=0)
				    printf("%s\t\t%s\t\tShift->%c \n",stack,&buff[index],buff[before]);
            
			}
		}
		else {
			// Input is finished
			if (buff[index] == '$')
				break;

			// Else shift again...
			int before=index;
			stack[++top] = buff[index++];
			stack[top + 1] = '\0';
			if(strcmp(stack,"E$")!=0)
			    printf("%s\t\t%s\t\tShift->%c \n",stack,&buff[index],buff[before]);
			
		}
	} while (index > 0 && buff[index - 1] != '$');

	if (strcmp(stack, "E$") == 0)
		printf("String Accepted\n");
	else
		printf("String Rejected\n");
}

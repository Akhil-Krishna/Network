#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

char stack[60][10];  // Stack now stores strings to handle temporary variable names
int top=-1;

void push(char item[]) {
    strcpy(stack[++top], item);
}

char* pop() {
    return stack[top--];
}

int isOperator(char item) {
    return (item == '+' || item == '-' || item == '*' || item == '/' || item == '^');
}

int precedence(char item) {
    if (item == '^')
        return 3;
    else if (item == '/' || item == '*')
        return 2;
    else if (item == '+' || item == '-')
        return 1;
    else
        return 0;
}

void InfixtoPostfix(char infix[], char postfix[]) {
    int i = 0, j = 0;
    char item, x;
    push("(");
    strcat(infix, ")");
    item = infix[i];
    while (item != '\0') {
        if (item == '(')
            push("(");
        else if (isalnum(item)) {
            postfix[j++] = item;
        }
        else if (isOperator(item)) {
            x = pop()[0]; // Pop top of stack
            while (isOperator(x) && precedence(x) >= precedence(item)) {
                postfix[j++] = x;
                x = pop()[0];
            }
            char temp[2] = {x, '\0'};
            push(temp);  // Push back lower precedence operator
            char operatorTemp[2] = {item, '\0'};
            push(operatorTemp);
        }
        else if (item == ')') {
            x = pop()[0];
            while (x != '(') {
                postfix[j++] = x;
                x = pop()[0];
            }
        }
        else {
            printf("\nInvalid expression");
            return;
        }
        i++;
        item = infix[i];
    }
    postfix[j] = '\0';
}

int main() {
    int i = 0, tempVarCounter = 1;
    char x[10], y[10], temp[10];
    char infix[30], postfix[30], item;

    printf("\nEnter the expression: ");
    scanf("%s", infix);

    InfixtoPostfix(infix, postfix);
    printf("\nINTERMEDIATE CODE:");

    item = postfix[i];
    while (item != '\0') {
        if (isalpha(item)) {
            char operand[2] = {item, '\0'};
            push(operand);  // Push operands to the stack
        } else if (isOperator(item)) {
            strcpy(x, pop());  // Pop top operand
            strcpy(y, pop());  // Pop second operand

            // Generate intermediate code
            printf("\n%c\t%s\t%s\tt%d", item, y, x, tempVarCounter);

            // Push temporary variable (e.g., t1, t2) back to the stack
            sprintf(temp, "t%d", tempVarCounter++);
            push(temp);
        }
        i++;
        item = postfix[i];
    }

    return 0;
}

#include <stdio.h>
#include <ctype.h>

#define MAX 100

int stack[MAX];
int top = -1;

void push(int value) {
    stack[++top] = value;
}

int pop() {
    return stack[top--];
}

int isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

int evaluatePostfix(char postfix[]) {

    int i;

    for (i = 0; postfix[i] != '\0'; i++) {

        char c = postfix[i];

        if (c == ' ')
            continue;

        // Operand
        if (isdigit(c)) {

            int value = c - '0';

            push(value);

            printf("Push %d\n", value);
        }

        // Operator
        else if (isOperator(c)) {

            int b = pop();
            int a = pop();
            int result;

            switch (c) {

                case '+':
                    result = a + b;
                    break;

                case '-':
                    result = a - b;
                    break;

                case '*':
                    result = a * b;
                    break;

                case '/':
                    result = a / b;
                    break;
            }

            printf("%d %c %d = %d\n", a, c, b, result);

            push(result);
        }
    }

    return pop();
}

int main() {

    char postfix[] = "8 3 2 * + 6 2 / -";

    printf("Postfix Expression : %s\n\n", postfix);

    printf("Evaluation Steps:\n");

    int result = evaluatePostfix(postfix);

    printf("\nFinal Result = %d\n", result);

    return 0;
}

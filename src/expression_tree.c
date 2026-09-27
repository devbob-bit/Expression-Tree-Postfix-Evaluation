#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX 100

typedef struct Node
{
    char data;
    struct Node *left;
    struct Node *right;
} Node;

Node *stack[MAX];
int top = -1;

Node *createNode(char data)
{
    Node *newNode = (Node *)malloc(sizeof(Node));

    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

void push(Node *node)
{
    stack[++top] = node;
}

Node *pop()
{
    return stack[top--];
}

int isOperator(char c)
{
    return (c == '+' || c == '-' ||
            c == '*' || c == '/');
}

Node *buildExpressionTree(char postfix[])
{
    int i;

    for (i = 0; postfix[i] != '\0'; i++)
    {
        char c = postfix[i];

        if (c == ' ')
            continue;

        if (isdigit(c))
        {
            push(createNode(c));
        }
        else if (isOperator(c))
        {
            Node *right = pop();
            Node *left = pop();

            Node *operatorNode = createNode(c);

            operatorNode->left = left;
            operatorNode->right = right;

            push(operatorNode);
        }
    }

    return pop();
}

void inorder(Node *root)
{
    if (root == NULL)
        return;

    if (root->left)
        printf("(");

    inorder(root->left);

    printf("%c", root->data);

    inorder(root->right);

    if (root->right)
        printf(")");
}

void preorder(Node *root)
{
    if (root == NULL)
        return;

    printf("%c ", root->data);

    preorder(root->left);
    preorder(root->right);
}

void postorder(Node *root)
{
    if (root == NULL)
        return;

    postorder(root->left);
    postorder(root->right);

    printf("%c ", root->data);
}

int evaluate(Node *root)
{
    int left, right;

    if (root->left == NULL && root->right == NULL)
        return root->data - '0';

    left = evaluate(root->left);
    right = evaluate(root->right);

    switch (root->data)
    {
        case '+':
            return left + right;

        case '-':
            return left - right;

        case '*':
            return left * right;

        case '/':
            return left / right;
    }

    return 0;
}

int main()
{
    char postfix[] = "8 3 2 * + 6 2 / -";

    Node *root;

    printf("Postfix Expression: %s\n", postfix);

    root = buildExpressionTree(postfix);

    printf("\nInorder   : ");
    inorder(root);

    printf("\nPreorder  : ");
    preorder(root);

    printf("\nPostorder : ");
    postorder(root);

    printf("\n\nExpression Tree Evaluation = %d\n",
           evaluate(root));

    return 0;
}

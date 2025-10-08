#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

struct Node {
    char data;
    struct Node *left, *right;
};

struct Node* newNode(char c) {
    struct Node *n = malloc(sizeof(struct Node));
    n->data = c;
    n->left = n->right = NULL;
    return n;
}

struct Node* stack[50];
int top = -1;

void push(struct Node* n) { stack[++top] = n; }
struct Node* pop() { return stack[top--]; }

void preorder(struct Node* t) {
    if (t) {
        printf("%c ", t->data);
        preorder(t->left);
        preorder(t->right);
    }
}

void postorder(struct Node* t) {
    if (t) {
        postorder(t->left);
        postorder(t->right);
        printf("%c ", t->data);
    }
}

int main() {
    char exp[50];
    printf("Enter postfix expression: ");
    scanf("%s", exp);

    for (int i = 0; exp[i] != '\0'; i++) {
        if (isalnum(exp[i])) push(newNode(exp[i]));
        else {
            struct Node *n = newNode(exp[i]);
            n->right = pop();
            n->left = pop();
            push(n);
        }
    }

    struct Node *root = pop();

    printf("Prefix expression: ");
    preorder(root);

    printf("\nPostfix expression: ");
    postorder(root);
    printf("\n");
}
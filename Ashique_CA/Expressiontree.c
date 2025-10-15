#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

struct Node {
    char data;
    struct Node *left, *right;
};

struct Node* newNode(char data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

int precedence(char op) {
    if (op == '^') return 3;
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

int isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

// Stack for operators (char)
char opStack[MAX];
int opTop = -1;
void pushOp(char c) { opStack[++opTop] = c; }
char popOp() { return opStack[opTop--]; }
char peekOp() { return opStack[opTop]; }
int isEmptyOp() { return opTop == -1; }

// Stack for tree nodes
struct Node* nodeStack[MAX];
int nodeTop = -1;
void pushNode(struct Node* n) { nodeStack[++nodeTop] = n; }
struct Node* popNode() { return nodeStack[nodeTop--]; }

// Convert infix to postfix
void infixToPostfix(char* infix, char* postfix) {
    int j = 0;
    for (int i = 0; infix[i]; i++) {
        char c = infix[i];
        if (isalnum(c)) {
            postfix[j++] = c;
        } else if (c == '(') {
            pushOp(c);
        } else if (c == ')') {
            while (!isEmptyOp() && peekOp() != '(') {
                postfix[j++] = popOp();
            }
            popOp(); // remove '('
        } else if (isOperator(c)) {
            while (!isEmptyOp() && precedence(peekOp()) >= precedence(c)) {
                postfix[j++] = popOp();
            }
            pushOp(c);
        }
    }
    while (!isEmptyOp()) {
        postfix[j++] = popOp();
    }
    postfix[j] = '\0';
}

// Build expression tree from postfix
struct Node* buildTreeFromPostfix(char* postfix) {
    for (int i = 0; postfix[i]; i++) {
        char c = postfix[i];
        if (isalnum(c)) {
            pushNode(newNode(c));
        } else if (isOperator(c)) {
            struct Node* right = popNode();
            struct Node* left = popNode();
            struct Node* opNode = newNode(c);
            opNode->left = left;
            opNode->right = right;
            pushNode(opNode);
        }
    }
    return popNode();
}

// Preorder traversal (Prefix)
void preorder(struct Node* root) {
    if (root) {
        printf("%c", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

// Postorder traversal (Postfix)
void postorder(struct Node* root) {
    if (root) {
        postorder(root->left);
        postorder(root->right);
        printf("%c", root->data);
    }
}

int main() {
    char infix[MAX], postfix[MAX];
    printf("Enter infix expression: ");
    scanf("%s", infix);

    infixToPostfix(infix, postfix);

    struct Node* root = buildTreeFromPostfix(postfix);

    printf("Prefix expression: ");
    preorder(root);
    printf("\n");

    printf("Postfix expression: ");
    postorder(root);
    printf("\n");

    return 0;
}
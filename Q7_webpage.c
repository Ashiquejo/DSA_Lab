#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Node {
    char url[100];
    struct Node *prev;
    struct Node *next;
} Node;

Node *cur = NULL;

Node* create(char *u) {
    Node *n = (Node*)malloc(sizeof(Node));
    strcpy(n->url, u);
    n->prev = n->next = NULL;
    return n;
}

void visit(char *u) {
    Node *n = create(u);
    if(cur) {
        cur->next = n;
        n->prev = cur;
    }
    cur = n;
    printf("Visited: %s\n", cur->url);
}

void back() {
    if(cur && cur->prev) {
        cur = cur->prev;
        printf("Back to: %s\n", cur->url);
    } else {
        printf("No previous page.\n");
    }
}

void forward() {
    if(cur && cur->next) {
        cur = cur->next;
        printf("Forward to: %s\n", cur->url);
    } else {
        printf("No next page.\n");
    }
}

void current() {
    if(cur) {
        printf("Current page: %s\n", cur->url);
    } else {
        printf("No page visited yet.\n");
    }
}

int main() {
    int ch;
    char url[100];
    while(1) {
        printf("\n1. Visit\n2. Back\n3. Forward\n4. Current\n5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &ch);
        switch(ch) {
            case 1:
                printf("Enter URL: ");
                scanf("%s", url);
                visit(url);
                break;
            case 2:
                back();
                break;
            case 3:
                forward();
                break;
            case 4:
                current();
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }
    return 0;
}

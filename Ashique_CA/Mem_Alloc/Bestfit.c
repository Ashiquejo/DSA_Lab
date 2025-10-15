#include <stdio.h>
#include <stdlib.h>

typedef struct Block {
    int id;
    int size;
    struct Block *prev, *next;
} Block;

Block* createBlocks(int sizes[], int n) {
    Block *head = NULL, *tail = NULL;
    for (int i = 0; i < n; i++) {
        Block *newNode = (Block*)malloc(sizeof(Block));
        newNode->id = i + 1;
        newNode->size = sizes[i];
        newNode->prev = tail;
        newNode->next = NULL;
        if (tail) tail->next = newNode;
        else head = newNode;
        tail = newNode;
    }
    return head;
}

void bestFit(Block *head, int processSize[], int n) {
    int allocation[n];
    for (int i = 0; i < n; i++) allocation[i] = -1;

    for (int i = 0; i < n; i++) {
        Block *curr = head;
        Block *bestBlock = NULL;
        while (curr) {
            if (curr->size >= processSize[i]) {
                if (!bestBlock || curr->size < bestBlock->size) {
                    bestBlock = curr;
                }
            }
            curr = curr->next;
        }
        if (bestBlock) {
            allocation[i] = bestBlock->id;
            bestBlock->size -= processSize[i];
        }
    }

    printf("\nBest Fit Allocation:\n");
    for (int i = 0; i < n; i++) {
        if (allocation[i] != -1)
            printf("Process %d -> Block %d\n", i + 1, allocation[i]);
        else
            printf("Process %d -> Not Allocated\n", i + 1);
    }
}

void freeBlocks(Block *head) {
    while (head) {
        Block *temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    int m, n;
    printf("Enter number of blocks: ");
    scanf("%d", &m);
    int blockSize[m];
    printf("Enter size of each block:\n");
    for (int i = 0; i < m; i++) scanf("%d", &blockSize[i]);

    printf("Enter number of processes: ");
    scanf("%d", &n);
    int processSize[n];
    printf("Enter size of each process:\n");
    for (int i = 0; i < n; i++) scanf("%d", &processSize[i]);

    Block *head = createBlocks(blockSize, m);
    bestFit(head, processSize, n);
    
    printf("\nRemaining space in blocks after allocation:\n");
    Block *curr = head;
    while (curr) {
        printf("Block %d -> %d\n", curr->id, curr->size);
        curr = curr->next;
    }

    freeBlocks(head);

    return 0;
}

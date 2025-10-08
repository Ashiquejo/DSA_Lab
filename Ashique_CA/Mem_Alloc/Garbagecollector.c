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

void garbageCollector(Block **headRef) {
    Block *head = *headRef;
    int totalFree = 0;

    Block *curr = head;
    while (curr) {
        totalFree += curr->size;
        Block *toDelete = curr;
        curr = curr->next;
        free(toDelete);
    }

    // Now create a single block with totalFree size
    Block *newBlock = (Block*)malloc(sizeof(Block));
    newBlock->id = 1;
    newBlock->size = totalFree;
    newBlock->prev = NULL;
    newBlock->next = NULL;

    *headRef = newBlock;

    printf("\nGarbage Collector (Compaction):\n");
    printf("All free space collected into one block = %d\n", totalFree);
}

void printBlocks(Block *head) {
    printf("\nCurrent blocks after compaction:\n");
    Block *curr = head;
    while (curr) {
        printf("Block %d: Size %d\n", curr->id, curr->size);
        curr = curr->next;
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
    int m;
    printf("Enter number of blocks: ");
    scanf("%d", &m);
    int blockSize[m];
    printf("Enter size of each block:\n");
    for (int i = 0; i < m; i++) scanf("%d", &blockSize[i]);

    Block *head = createBlocks(blockSize, m);

    garbageCollector(&head);
    printBlocks(head);

    freeBlocks(head);

    return 0;
}

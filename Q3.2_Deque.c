#include <stdio.h>

int deque[100];
int front = -1, rear = -1, size = 0;

int isFull() {
    return (front == 0 && rear == size - 1) || (front == rear + 1);
}

int isEmpty() {
    return front == -1;
}

void insertFront(int value) {
    if (isFull()) {
        printf("Deque Overflow\n");
        return;
    }
    if (isEmpty()) front = rear = 0;
    else if (front == 0) front = size - 1;
    else front--;
    deque[front] = value;
    printf("%d inserted at front\n", value);
}

void insertRear(int value) {
    if (isFull()) {
        printf("Deque Overflow\n");
        return;
    }
    if (isEmpty()) front = rear = 0;
    else if (rear == size - 1) rear = 0;
    else rear++;
    deque[rear] = value;
    printf("%d inserted at rear\n", value);
}

void deleteFront() {
    if (isEmpty()) {
        printf("Deque Underflow\n");
        return;
    }
    printf("%d deleted from front\n", deque[front]);
    if (front == rear) front = rear = -1;
    else if (front == size - 1) front = 0;
    else front++;
}

void deleteRear() {
    if (isEmpty()) {
        printf("Deque Underflow\n");
        return;
    }
    printf("%d deleted from rear\n", deque[rear]);
    if (front == rear) front = rear = -1;
    else if (rear == 0) rear = size - 1;
    else rear--;
}

void display() {
    if (isEmpty()) {
        printf("Deque is empty\n");
        return;
    }
    printf("Deque: ");
    int i = front;
    while (1) {
        printf("%d ", deque[i]);
        if (i == rear) break;
        i = (i + 1) % size;
    }
    printf("\n");
}

int main() {
    int choice, value;
    printf("Enter the size of the deque (max 100): ");
    scanf("%d", &size);
    if (size <= 0 || size > 100) {
        printf("Invalid size.\n");
        return 1;
    }
    printf("\nDeque Operations:\n");
    printf("1. Insert at Front\n2. Insert at Rear\n3. Delete from Front\n4. Delete from Rear\n5. Display\n6. Exit\n");

    while (1) {
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: printf("Enter value: "); scanf("%d", &value); insertFront(value); break;
            case 2: printf("Enter value: "); scanf("%d", &value); insertRear(value); break;
            case 3: deleteFront(); break;
            case 4: deleteRear(); break;
            case 5: display(); break;
            case 6: printf("Exiting the program...\n"); return 0;
            default: printf("Invalid choice\n");
        }
    }
}

#include <stdio.h>
#define MAX_CAPACITY 100

int stackArr[MAX_CAPACITY] = {0};
int topIndex = -1;

void pushElement() {
    if (topIndex + 1 >= MAX_CAPACITY) {
        printf("\nCannot push: Stack is full!\n");
        return;
    }
    int val;
    printf("Enter value to push onto stack: ");
    scanf("%d", &val);
    while (getchar() != '\n');  

    topIndex++;
    stackArr[topIndex] = val;
    printf("✅ Value %d added to stack.\n", val);
}

void popElement() {
    if (topIndex < 0) {
        printf("\n Cannot pop: Stack is empty!\n");
        return;
    }
    int removed = stackArr[topIndex];
    topIndex--;
    printf("\nRemoved top element: %d\n\n", removed);
}

void peekElement() {
    if (topIndex < 0) {
        printf("\nStack is empty. No elements to show.\n\n");
        return;
    }
    printf("\nTop element: %d\n\n", stackArr[topIndex]);
}

void displayStack() {
    if (topIndex < 0) {
        printf("\nStack is empty.\n\n");
        return;
    }
    printf("\n--- Current Stack ---\n");
    for (int i = 0; i <= topIndex; i++) {
        printf("[%d] = %d\n", i, stackArr[i]);
    }
    printf("\n");
}

int main() {
    int choice;

    do {
        printf("\n=== Stack Manager ===\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Peek\n");
        printf("4. Display\n");
        printf("5. Exit\n");
        printf("Choose operation (1-5): ");
        scanf("%d", &choice);
        while (getchar() != '\n');

        switch (choice) {
            case 1:
                pushElement();
                break;
            case 2:
                popElement();
                break;
            case 3:
                peekElement();
                break;
            case 4:
                displayStack();
                break;
            case 5:
                printf("\nThanks for using Stack Manager!\n");
                break;
            default:
                printf("\nInvalid option. Try again.\n");
        }
    } while (choice != 5);

    return 0;
}

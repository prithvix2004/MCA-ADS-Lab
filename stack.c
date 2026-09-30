#include <stdio.h>

#define SIZE 5

int stack[SIZE];
int top = -1;

void push(int ele) 
{
    if (top == SIZE - 1) {
        printf("Overflow! Stack is full.\n");
    } else {
        top++;
        stack[top] = ele;
        printf("%d inserted\n", stack[top]);
    }
}

void pop() 
{
    if (top == -1) {
        printf("Underflow! Stack is empty.\n");
    } else {
        printf("%d deleted\n", stack[top]);
        top--;
    }
}

void display() 
{
    if (top == -1) {
        printf("Stack is empty.\n");
    } else {
        printf("Stack elements: ");
        for (int i = top; i >= 0; i--) {
            printf("%d ", stack[i]);
        }
        printf("\n");
    }
}

int main() 
{
    int choice, ele;

    while (1) {
        printf("\n--- Stack Menu ---\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Display\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter element to push: ");
                scanf("%d", &ele);
                push(ele);
                break;
            case 2:
                pop();
                break;
            case 3:
                display();
                break;
            case 4:
                return 0;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}

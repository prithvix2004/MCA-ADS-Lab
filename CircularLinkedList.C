#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

int main() {
    struct node *head = NULL;
    struct node *newnode, *temp;
    int choice = 1;

    while (choice == 1) {
        newnode = (struct node *)malloc(sizeof(struct node));

        printf("Enter data: ");
        scanf("%d", &newnode->data);

        newnode->next = NULL;

        if (head == NULL) {
            head = newnode;
            temp = newnode;
        } else {
            temp->next = newnode;
            temp = newnode;
        }

        temp->next = head;

        printf("Do you want to continue? (1/0): ");
        scanf("%d", &choice);
    }

    if (head != NULL) {
        temp = head;

        printf("Circular Linked List: ");

        do {
            printf("%d -> ", temp->data);
            temp = temp->next;
        } while (temp != head);

        printf("(back to head)\n");
    }

    return 0;
}
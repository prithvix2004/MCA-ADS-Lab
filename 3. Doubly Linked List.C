#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
    struct node *prev;
};

struct node *head = NULL, *temp = NULL;

void create() {
    struct node *newnode = (struct node *)malloc(sizeof(struct node));
    if (newnode == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }
    
    printf("Enter the data: ");
    scanf("%d", &newnode->data);
    newnode->prev = NULL;
    newnode->next = NULL;

    if (head == NULL) {
        head = temp = newnode;
    } 
    else
    {
        temp->next = newnode;
        newnode->prev = temp;
        temp = newnode;
    }
}

void display() {
    struct node *ptr = head;
    printf("\nDoubly Linked List elements: ");
    while (ptr != NULL) {
        printf("%d <-> ", ptr->data);
        ptr = ptr->next;
    }
    printf("NULL\n");
}

int main() {
    int choice;
    do {
        create();
        printf("Do you want to add another node? (1 for yes, 0 for no): ");
        scanf("%d", &choice);
    } while (choice == 1);

    display();
    return 0;
}

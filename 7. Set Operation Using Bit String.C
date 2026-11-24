#include <stdio.h>

#define MAX 8

//Display
void display(int set[])
{
    int i, empty = 1;

    printf("{ ");
    for (i = 0; i < MAX; i++)
    {
        if (set[i] == 1)
        {
            printf("%d ", i + 1);
            empty = 0;
        }
    }

    if (empty)
        printf("Empty");

    printf("}\n");
}

//Add
void add(int set[], int element)
{
    if (element >= 1 && element <= MAX)
    {
        set[element - 1] = 1;
        printf("%d added successfully.\n", element);
    }
    else
        printf("Invalid element!\n");
}

//Remove
void removeElement(int set[], int element)
{
    if (element >= 1 && element <= MAX)
    {
        set[element - 1] = 0;
        printf("%d removed successfully.\n", element);
    }
    else
        printf("Invalid element!\n");
}

//Union Set
void unionSet(int A[], int B[], int C[])
{
    int i;

    for (i = 0; i < MAX; i++)
        C[i] = A[i] | B[i];
}

//Intersection
void intersectionSet(int A[], int B[], int C[])
{
    int i;

    for (i = 0; i < MAX; i++)
        C[i] = A[i] & B[i];
}

//Difference
void differenceSet(int A[], int B[], int C[])
{
    int i;

    for (i = 0; i < MAX; i++)
        C[i] = A[i] & (~B[i]);
}

int main()
{
    int A[MAX] = {0};
    int B[MAX] = {0};
    int C[MAX] = {0};

    int choice, element, i, n, x;

    // Read Set A
    printf("Enter number of elements in Set A: ");
    scanf("%d", &n);

    if (n < 0 || n > MAX)
    {
        printf("Invalid number of elements!\n");
        return 1;
    }

    printf("Enter elements of Set A (1 to %d): ", MAX);

    for (i = 0; i < n; i++)
    {
        scanf("%d", &x);

        if (x >= 1 && x <= MAX)
            A[x - 1] = 1;
        else
            printf("Invalid element %d ignored.\n", x);
    }

    // Read Set B
    printf("\nEnter number of elements in Set B: ");
    scanf("%d", &n);

    if (n < 0 || n > MAX)
    {
        printf("Invalid number of elements!\n");
        return 1;
    }

    printf("Enter elements of Set B (1 to %d): ", MAX);

    for (i = 0; i < n; i++)
    {
        scanf("%d", &x);

        if (x >= 1 && x <= MAX)
            B[x - 1] = 1;
        else
            printf("Invalid element %d ignored.\n", x);
    }

    do
    {
        printf("\n----- SET ADT USING BIT STRINGS -----\n");
        printf("1. Display Sets\n");
        printf("2. Add Element to Set A\n");
        printf("3. Remove Element from Set A\n");
        printf("4. Union (A U B)\n");
        printf("5. Intersection (A n B)\n");
        printf("6. Difference (A - B)\n");
        printf("7. Difference (B - A)\n");
        printf("8. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                printf("Set A = ");
                display(A);

                printf("Set B = ");
                display(B);
                break;

            case 2:
                printf("Enter element to add: ");
                scanf("%d", &element);
                add(A, element);
                break;

            case 3:
                printf("Enter element to remove: ");
                scanf("%d", &element);
                removeElement(A, element);
                break;

            case 4:
                unionSet(A, B, C);
                printf("Union = ");
                display(C);
                break;

            case 5:
                intersectionSet(A, B, C);
                printf("Intersection = ");
                display(C);
                break;

            case 6:
                differenceSet(A, B, C);
                printf("Difference (A-B) = ");
                display(C);
                break;

            case 7:
                differenceSet(B, A, C);
                printf("Difference (B-A) = ");
                display(C);
                break;

            case 8:
                printf("Exiting program...\n");
                break;

            default:
                printf("Invalid choice! Try again.\n");
        }

    } while (choice != 8);

    return 0;
}

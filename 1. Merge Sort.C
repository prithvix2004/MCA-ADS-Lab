#include <stdio.h>

int main() {
    int arr1[100], arr2[100], arr3[200];
    int m, n, i = 0, j = 0, k = 0;

    printf("Enter the size of first array: ");
    scanf("%d", &m);

    printf("Enter the elements of sorted first array:\n");
    for (i = 0; i < m; i++) {
        scanf("%d", &arr1[i]);
    }

    printf("Enter the size of second array: ");
    scanf("%d", &n);

    printf("Enter the elements of sorted second array:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &arr2[i]);
    }

    i = 0;
    j = 0;

    while (i < m && j < n) {
        if (arr1[i] < arr2[j]) {
            arr3[k++] = arr1[i++];
        } else {
            arr3[k++] = arr2[j++];
        }
    }

    while (i < m) {
        arr3[k++] = arr1[i++];
    }

    while (j < n) {
        arr3[k++] = arr2[j++];
    }

    printf("Merged sorted array:\n");
    for (i = 0; i < m + n; i++) {
        printf("%d ", arr3[i]);
    }
    printf("\n");

    return 0;
}

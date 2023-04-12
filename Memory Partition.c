#include <stdio.h>
#include <stdlib.h>

int main() {
    int* ptr1;
    int* ptr2;
    int* ptr3;

    // Allocate memory blocks of different sizes
    ptr1 = (int*) malloc(10 * sizeof(int));
    ptr2 = (int*) malloc(20 * sizeof(int));
    ptr3 = (int*) malloc(30 * sizeof(int));

    // Check if allocation was successful
    if (ptr1 == NULL || ptr2 == NULL || ptr3 == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    // Use the allocated memory blocks
    for (int i = 0; i < 10; i++) {
        ptr1[i] = i;
    }

    for (int i = 0; i < 20; i++) {
        ptr2[i] = i * 2;
    }

    for (int i = 0; i < 30; i++) {
        ptr3[i] = i * 3;
    }

    // Free the allocated memory blocks
    free(ptr1);
    free(ptr2);
    free(ptr3);

    return 0;
}

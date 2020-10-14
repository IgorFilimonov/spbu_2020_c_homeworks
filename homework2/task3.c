#include "../library/commonUtils/numericOperations.h"
#include <stdio.h>
#include <stdlib.h>

int* readInputData(int* n)
{
    printf("Enter n:\n");
    scanf("%d", n);

    printf("Enter an array:\n");
    int* array = (int*)calloc(*n, sizeof(int));
    for (int i = 0; i < *n; ++i)
        scanf("%d", &array[i]);
    return array;
}

void printOutput(int* array, int n)
{
    printf("Here is the changed array:\n");
    for (int i = 0; i < n; ++i)
        printf("%d ", array[i]);
    printf("\n");
}

int main()
{
    int n = 0;
    int* array = readInputData(&n);

    int indexOfNextZero = n - 1;
    for (int i = 0; i < indexOfNextZero;) {
        if (array[i] != 0) {
            ++i;
            continue;
        }
        swap(&array[i], &array[indexOfNextZero]);
        --indexOfNextZero;
    }

    printOutput(array, n);

    free(array);
    return 0;
}
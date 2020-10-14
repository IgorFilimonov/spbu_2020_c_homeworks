#include "../library/commonUtils/numericOperations.h"
#include <stdio.h>
#include <stdlib.h>

void readInputData(int* n, int* array)
{
    printf("Enter n:\n");
    scanf("%d", n);

    printf("Enter an array:\n");
    array = (int*)calloc(*n, sizeof(int));
    for (int i = 0; i < *n; ++i)
        scanf("%d", &array[i]);
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
    int* array = NULL;
    readInputData(&n, array);

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
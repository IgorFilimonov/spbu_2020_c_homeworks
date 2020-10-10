#include "../library/commonUtils/numericOperations.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n = 0;
    printf("Enter n:\n");
    scanf("%d", &n);

    int* array = (int*)calloc(n, sizeof(int));
    printf("Enter an array:\n");
    scanIntegerArray(array, n);

    int indexOfNextZero = n - 1;
    for (int i = 0; i < indexOfNextZero;) {
        if (array[i] != 0) {
            ++i;
            continue;
        }
        swap(&array[i], &array[indexOfNextZero]);
        --indexOfNextZero;
    }

    printf("Here is the changed array:\n");
    printIntegerArray(array, n);

    free(array);
    return 0;
}
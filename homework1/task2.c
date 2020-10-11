#include "../library/commonUtils/numericOperations.h"
#include <stdio.h>
#include <stdlib.h>

void reverseAnArray(int* array, int numberOfElements)
{
    for (int i = 0; i < numberOfElements / 2; ++i)
        swap(&array[i], &array[numberOfElements - 1 - i]);
}

int main()
{
    int m = 0, n = 0;
    printf("Enter m and n:\n");
    scanf("%d%d", &m, &n);
    int* array = (int*)calloc((m + n), sizeof(int));
    printf("Enter an array:\n");
    for (int i = 0; i < m + n; ++i)
        scanf("%d", &array[i]);

    reverseAnArray(array, m);
    reverseAnArray(&array[m], n);
    reverseAnArray(array, m + n);

    printf("Here is a result:\n");
    for (int i = 0; i < m + n; ++i)
        printf("%d ", array[i]);

    free(array);
    return 0;
}
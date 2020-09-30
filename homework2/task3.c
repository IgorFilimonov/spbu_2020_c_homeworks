#include <stdio.h>
#include <stdlib.h>
#include "../library/commonUtils/numericOperations.h"

int main()
{
    int n = 0;
    printf("Enter n:\n");
    scanf("%d", &n);
    int* array = (int*)calloc(n, sizeof(int));
    printf("Enter an array:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &array[i]);

    int indexOfNextZero = n - 1;
    for (int i = 0; i < indexOfNextZero;) {
        if (array[i] != 0) {
            i++;
            continue;
        }
        for (int j = i; j < indexOfNextZero; j++) {
            swap(&array[j], &array[j + 1]);
        }
        indexOfNextZero--;
    }

    for (int i = 0; i < n; i++)
        printf("%d ", array[i]);
    free(array);
    return 0;
}
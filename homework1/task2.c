#include <stdio.h>
#include <stdlib.h>
#include "../library/commonUtils/numericOperations.h"

int main()
{
    int m = 0, n = 0;
    printf("Enter n and m:\n");
    scanf("%d%d", &m, &n);
    int* array = (int*)malloc((m + n) * sizeof(int));
    printf("Enter an array:\n");
    for (int i = 0; i < m + n; i++)
        scanf("%d", &array[i]);

    int firstSegment = m, secondSegment = n, startIndex = 0;
    while (firstSegment != secondSegment) {
        if (firstSegment < secondSegment) {
            for (int i = 0; i < firstSegment; i++)
                swap(&array[startIndex + i], &array[startIndex + secondSegment + i]);
            secondSegment -= firstSegment;
        }
        if (firstSegment > secondSegment) {
            for (int i = 0; i < secondSegment; i++)
                swap(&array[startIndex + i], &array[startIndex + firstSegment + i]);
            startIndex += secondSegment;
            firstSegment -= secondSegment;
        }
    }
    for (int i = 0; i < firstSegment; i++)
        swap(&array[startIndex + i], &array[startIndex + secondSegment + i]);
    for (int i = 0; i < m + n; i++)
        printf("%d ", array[i]);
    free(array);
    return 0;
}
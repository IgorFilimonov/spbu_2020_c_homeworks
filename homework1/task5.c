#include "../library/commonUtils/numericOperations.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int n = 0;
    printf("Enter n:\n");
    scanf("%d", &n);
    int minimum = 0, maximum = 0;
    printf("Enter an array:\n");
    int* array = (int*)calloc(n, sizeof(int));
    for (int i = 0; i < n; ++i) {
        scanf("%d", &array[i]);
        if (i == 0) {
            minimum = array[i];
            maximum = array[i];
        }
        minimum = min(minimum, array[i]);
        maximum = max(maximum, array[i]);
    }

    int range = maximum - minimum + 1;
    bool* isNumber = (bool*)malloc(range * sizeof(bool));
    memset(isNumber, false, range * sizeof(bool));
    int maximumSeveralTimes = -1;
    for (int i = 0; i < n; ++i) {
        if (isNumber[array[i] - minimum])
            maximumSeveralTimes = max(maximumSeveralTimes, array[i] - minimum);
        isNumber[array[i] - minimum] = true;
    }

    printf("%d", minimum + maximumSeveralTimes);
    free(array);
    free(isNumber);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
    int n, *array, *isNumber;
    scanf("%d", &n);
    array = (int*)malloc(n * sizeof(int));
    int minimum = 0, maximum = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d", &array[i]);
        if (!i) {
            minimum = array[i];
            maximum = array[i];
        }
        if (array[i] < minimum)
            minimum = array[i];
        if (array[i] > maximum)
            maximum = array[i];
    }
    int range = maximum - minimum + 1;
    isNumber = (int*)malloc(range * sizeof(int));
    memset(isNumber, 0, range * sizeof(int));
    int answer = -1;
    for (int i = 0; i < n; i++) {
        if (isNumber[array[i] - minimum] && array[i] - minimum > answer)
            answer = array[i] - minimum;
        isNumber[array[i] - minimum] = 1;
    }
    printf("%d", minimum + answer);
    return 0;
}
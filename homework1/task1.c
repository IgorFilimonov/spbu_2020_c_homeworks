#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n = 0;
    printf("Enter n:\n");
    scanf("%d", &n);
    int** array = (int**)malloc(n * sizeof(int*));
    printf("Enter an array:\n");
    for (int i = 0; i < n; ++i) {
        array[i] = (int*)calloc(n, sizeof(int));
        for (int j = 0; j < n; ++j)
            scanf("%d", &array[i][j]);
    }

    int lineNumber = n / 2, columnNumber = lineNumber, numberOfSteps = 1;
    while (true) {
        int stepsLeft = numberOfSteps;
        while (stepsLeft != 0 && columnNumber != n - 1) {
            printf("%d ", array[lineNumber][columnNumber]);
            ++columnNumber;
            --stepsLeft;
        }

        if (lineNumber == 0 && columnNumber == n - 1) {
            printf("%d", array[lineNumber][columnNumber]);
            break;
        }

        stepsLeft = numberOfSteps;
        while (stepsLeft != 0) {
            printf("%d ", array[lineNumber][columnNumber]);
            ++lineNumber;
            --stepsLeft;
        }

        ++numberOfSteps;
        stepsLeft = numberOfSteps;
        while (stepsLeft != 0) {
            printf("%d ", array[lineNumber][columnNumber]);
            --columnNumber;
            --stepsLeft;
        }

        stepsLeft = numberOfSteps;
        while (stepsLeft != 0) {
            printf("%d ", array[lineNumber][columnNumber]);
            --lineNumber;
            --stepsLeft;
        }
        ++numberOfSteps;
    }

    for (int i = 0; i < n; ++i)
        free(array[i]);
    free(array);
    return 0;
}
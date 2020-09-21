#include<stdio.h>
#include<stdlib.h>
int main()
{
    int n = 0, **A;
    scanf("%d", &n);
    A = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        A[i] = (int*)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++)
            scanf("%d", &A[i][j]);
    }
    int lineNumber = n / 2, columnNumber = lineNumber;
    int numberOfSteps = 1;
    for ( ; ; ) {
        int stepsLeft = numberOfSteps;
        while (stepsLeft && columnNumber != n - 1) {
            printf("%d ", A[lineNumber][columnNumber]);
            columnNumber++;
            stepsLeft--;
        }
        if (!lineNumber && columnNumber == n - 1) {
            printf("%d", A[lineNumber][columnNumber]);
            return 0;
        }
        stepsLeft = numberOfSteps;
        while (stepsLeft) {
            printf("%d ", A[lineNumber][columnNumber]);
            lineNumber++;
            stepsLeft--;
        }
        numberOfSteps++;
        stepsLeft = numberOfSteps;
        while (stepsLeft) {
            printf("%d ", A[lineNumber][columnNumber]);
            columnNumber--;
            stepsLeft--;
        }
        stepsLeft = numberOfSteps;
        while (stepsLeft) {
            printf("%d ", A[lineNumber][columnNumber]);
            lineNumber--;
            stepsLeft--;
        }
        numberOfSteps++;
    }
}

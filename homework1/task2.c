#include <stdio.h>
#include <stdlib.h>
void swap(int* a, int* b)
{
    int c = *a;
    *a = *b;
    *b = c;
}
int main()
{
    int m = 0, n = 0, *A;
    scanf("%d%d", &m, &n);
    A = (int*)malloc((m + n) * sizeof(int));
    for (int i = 0; i < m + n; i++)
        scanf("%d", &A[i]);
    int firstSegment = m, secondSegment = n, startIndex = 0;
    while (firstSegment != secondSegment) {
        if (firstSegment < secondSegment) {
            for (int i = 0; i < firstSegment; i++)
                swap(&A[startIndex + i], &A[startIndex + secondSegment + i]);
            secondSegment -= firstSegment;
        }
        if (firstSegment > secondSegment) {
            for (int i = 0; i < secondSegment; i++)
                swap(&A[startIndex + i], &A[startIndex + firstSegment + i]);
            startIndex += secondSegment;
            firstSegment -= secondSegment;
        }
    }
    for (int i = 0; i < firstSegment; i++)
        swap(&A[startIndex + i], &A[startIndex + secondSegment + i]);
    for (int i = 0; i < m + n; i++)
        printf("%d ", A[i]);
    return 0;
}
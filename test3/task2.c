#include "../library/matrix.h"
#include <stdio.h>

int main()
{
    printf("Enter a dimensions of the array:\n");
    int countLines = 0, countColumns = 0;
    scanf("%d%d", &countLines, &countColumns);
    Matrix* matrix = createMatrix(countLines, countColumns);
    printf("Enter an array:\n");
    readMatrix(matrix);

    findSaddlePoints(matrix);

    destroyMatrix(matrix);
    return 0;
}

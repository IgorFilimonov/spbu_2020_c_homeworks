#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

struct Matrix {
    int** matrix;
    int countLines;
    int countColumns;
};

Matrix* createMatrix(int countLines, int countColumns)
{
    Matrix* newMatrix = (Matrix*)malloc(sizeof(Matrix));
    newMatrix->matrix = (int**)malloc(countLines * sizeof(int*));
    for (int i = 0; i < countLines; ++i)
        newMatrix->matrix[i] = (int*)calloc(countColumns, sizeof(int));
    newMatrix->countLines = countLines;
    newMatrix->countColumns = countColumns;
    return newMatrix;
}

void readMatrix(Matrix* matrix)
{
    for (int i = 0; i < matrix->countLines; ++i) {
        for (int j = 0; j < matrix->countColumns; ++j)
            scanf("%d", &matrix->matrix[i][j]);
    }
}

void printMatrix(Matrix* matrix)
{
    for (int i = 0; i < matrix->countLines; ++i) {
        for (int j = 0; j < matrix->countColumns; ++j)
            printf("%d ", matrix->matrix[i][j]);
        printf("\n");
    }
}

void findMinimumsInLines(Matrix* matrix, int** minimumsInLines);

void findMaximumsInColumns(Matrix* matrix, int** maximumsInColumns);

void findSaddlePoints(Matrix* matrix)
{
    int* minimumsInLines = (int*)malloc(matrix->countLines * sizeof(int));
    findMinimumsInLines(matrix, &minimumsInLines);
    int* maximumsInColumns = (int*)malloc(matrix->countColumns * sizeof(int));
    findMaximumsInColumns(matrix, &maximumsInColumns);

    printf("Saddle points:\n");
    for (int i = 0; i < matrix->countLines; ++i) {
        for (int j = 0; j < matrix->countColumns; ++j) {
            if (matrix->matrix[i][j] == minimumsInLines[i] && matrix->matrix[i][j] == maximumsInColumns[j])
                printf("%d (line %d, column %d)\n", matrix->matrix[i][j], i + 1, j + 1);
        }
    }

    free(minimumsInLines);
    free(maximumsInColumns);
}

void findMinimumsInLines(Matrix* matrix, int** minimumsInLines)
{
    for (int i = 0; i < matrix->countLines; ++i) {
        (*minimumsInLines)[i] = matrix->matrix[i][0];
        for (int j = 1; j < matrix->countColumns; ++j) {
            if (matrix->matrix[i][j] < (*minimumsInLines)[i])
                (*minimumsInLines)[i] = matrix->matrix[i][j];
        }
    }
}

void findMaximumsInColumns(Matrix* matrix, int** maximumsInColumns)
{
    for (int i = 0; i < matrix->countColumns; ++i) {
        (*maximumsInColumns)[i] = matrix->matrix[0][i];
        for (int j = 1; j < matrix->countLines; ++j) {
            if (matrix->matrix[j][i] > (*maximumsInColumns)[i])
                (*maximumsInColumns)[i] = matrix->matrix[j][i];
        }
    }
}

void destroyMatrix(Matrix* matrix)
{
    for (int i = 0; i < matrix->countLines; ++i)
        free(matrix->matrix[i]);
    free(matrix->matrix);
    free(matrix);
}

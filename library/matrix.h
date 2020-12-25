#ifndef SPBU_2020_C_HOMEWORKS_MATRIX_H
#define SPBU_2020_C_HOMEWORKS_MATRIX_H

typedef struct Matrix Matrix;

Matrix* createMatrix(int countLines, int countColumns);

void readMatrix(Matrix* matrix);

void printMatrix(Matrix* matrix);

void findSaddlePoints(Matrix* matrix);

void destroyMatrix(Matrix* matrix);

#endif //SPBU_2020_C_HOMEWORKS_MATRIX_H

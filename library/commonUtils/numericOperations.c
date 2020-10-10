#include "numericOperations.h"
#include <stdio.h>

int min(int a, int b)
{
    return a > b ? b : a;
}

int max(int a, int b)
{
    return a > b ? a : b;
}

void swap(int* a, int* b)
{
    int c = *a;
    *a = *b;
    *b = c;
}

void scanIntegerArray(int* array, int size)
{
    for (int i = 0; i < size; ++i)
        scanf("%d", &array[i]);
}

void printIntegerArray(int* array, int size)
{
    for (int i = 0; i < size; ++i)
        printf("%d ", array[i]);
    printf("\n");
}
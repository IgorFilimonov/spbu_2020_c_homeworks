#include "../library/commonUtils/numericOperations.h"
#include <stdio.h>
#include <stdlib.h>

int* convertToArrayOfDigits(long long number, int numberOfDigits)
{
    int* digits = (int*)calloc(numberOfDigits, sizeof(int));
    for (int i = numberOfDigits - 1; i >= 0; --i) {
        digits[i] = number % 10;
        number /= 10;
    }
    return digits;
}

int compare(const void* a, const void* b)
{
    return *((int*)a) - *((int*)b);
}

int countNumberOfDigits(long long number)
{
    int numberOfDigits = 0;
    while (number != 0) {
        ++numberOfDigits;
        number /= 10;
    }
    return numberOfDigits;
}

void makeNumberNotStartingAtZero(int* digits, int numberOfDigits)
{
    for (int i = 0; i < numberOfDigits; ++i) {
        if (digits[i] != 0) {
            swap(&digits[0], &digits[i]);
            return;
        }
    }
}

void printOutput(int* digits, int sizeOfNumber)
{
    printf("Here is the required number:\n");
    for (int i = 0; i < sizeOfNumber; ++i)
        printf("%d", digits[i]);
}

int main()
{
    long long number = 0;
    printf("Enter a natural number:\n");
    scanf("%lld", &number);
    if (number <= 0) {
        printf("Number isn't natural.");
        return 0;
    }

    int sizeOfNumber = countNumberOfDigits(number);
    int* digits = convertToArrayOfDigits(number, sizeOfNumber);
    qsort(digits, sizeOfNumber, sizeof(int), compare);
    makeNumberNotStartingAtZero(digits, sizeOfNumber);

    printOutput(digits, sizeOfNumber);

    free(digits);
    return 0;
}
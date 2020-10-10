#include "../library/commonUtils/numericOperations.h"
#include <stdio.h>
#include <stdlib.h>

int* convertToArrayOfDigits(int number, int* numberOfDigits)
{
    int copyOfNumber = number;
    while (copyOfNumber != 0) {
        ++(*numberOfDigits);
        copyOfNumber /= 10;
    }
    int* digits = (int*)calloc(*numberOfDigits, sizeof(int));
    for (int i = *numberOfDigits - 1; i >= 0; --i) {
        digits[i] = number % 10;
        number /= 10;
    }
    return digits;
}

int compare(const void* a, const void* b)
{
    return *((int*)a) - *((int*)b);
}

int main()
{
    int number = 0;
    printf("Enter the number:\n");
    scanf("%d", &number);

    int numberOfDigits = 0;
    int* digits = convertToArrayOfDigits(number, &numberOfDigits);
    qsort(digits, numberOfDigits, sizeof(int), compare);
    for (int i = 0; i < numberOfDigits; ++i) {
        if (digits[i] != 0) {
            swap(&digits[0], &digits[i]);
            break;
        }
    }

    printf("Here is the required number:\n");
    for (int i = 0; i < numberOfDigits; ++i)
        printf("%d", digits[i]);

    free(digits);
    return 0;
}
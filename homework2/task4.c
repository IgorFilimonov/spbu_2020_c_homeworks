#include <stdio.h>
#include <stdlib.h>
#include "../library/commonUtils/numericOperations.h"

int* convertToArrayOfDigits(int number, int* numberOfDigits)
{
    int copyOfNumber = number;
    while (copyOfNumber != 0) {
        (*numberOfDigits)++;
        copyOfNumber /= 10;
    }
    int* digits = (int*)calloc(*numberOfDigits, sizeof(int));
    for (int i = *numberOfDigits - 1; i >= 0; i--) {
        digits[i] = number % 10;
        number /= 10;
    }
    return digits;
}

void bubbleSort(int* array, int sizeOfArray)
{
    for (int i = sizeOfArray - 1; i > 0; i--) {
        int indexOfMaximum = 0;
        for (int j = 1; j <= i; j++) {
            if (array[j] > array[indexOfMaximum])
                indexOfMaximum = j;
        }
        swap(&array[indexOfMaximum], &array[i]);
    }
}

int main()
{
    int number = 0;
    printf("Enter the number:\n");
    scanf("%d", &number);

    int numberOfDigits = 0;
    int* digits = convertToArrayOfDigits(number, &numberOfDigits);
    bubbleSort(digits, numberOfDigits);
    for (int i = 0; i < numberOfDigits; i++) {
        if (digits[i]) {
            swap(&digits[0], &digits[i]);
            break;
        }
    }

    for (int i = 0; i < numberOfDigits; i++)
        printf("%d", digits[i]);
    free(digits);
    return 0;
}
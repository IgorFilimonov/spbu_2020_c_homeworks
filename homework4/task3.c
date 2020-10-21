#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

const int SIZE = sizeof(int) * 8;

bool* convertToTwosComplement(int number)
{
    bool* representation = (bool*)calloc(SIZE, sizeof(bool));
    if (number < 0) {
        representation[0] = true;
        number = -number;
    }
    for (int i = SIZE - 1; i >= 1; --i) {
        representation[i] = number % 2;
        number /= 2;
    }
    if (representation[0]) {
        for (int i = SIZE - 1; i >= 1; --i)
            representation[i] = !representation[i];
        for (int i = SIZE - 1; i >= 1; --i) {
            if (!representation[i]) {
                representation[i] = true;
                break;
            }
            representation[i] = false;
        }
    }

    return representation;
}

void printBinaryRepresentation(bool* representation)
{
    for (int i = 0; i < SIZE; ++i)
        printf("%d", representation[i] ? 1 : 0);
    printf("\n");
}

bool* addInTwosComplement(bool* firstNumber, bool* secondNumber)
{
    bool* sum = (bool*)calloc(SIZE, sizeof(bool));
    bool overflow = false;
    for (int i = SIZE - 1; i >= 0; --i) {
        sum[i] = (overflow + firstNumber[i] + secondNumber[i]) % 2;
        overflow = overflow + firstNumber[i] + secondNumber[i] >= 2;
    }

    return sum;
}

int convertToDecimal(bool* twosComplement)
{
    bool isNegative = twosComplement[0];
    if (isNegative) {
        for (int i = 0; i < SIZE; ++i)
            twosComplement[i] = !twosComplement[i];
        for (int i = SIZE - 1; i >= 1; --i) {
            if (!twosComplement[i]) {
                twosComplement[i] = true;
                break;
            }
            twosComplement[i] = false;
        }
    }
    int powerOfTwo = 1, number = 0;
    for (int i = SIZE - 1; i >= 0; i--) {
        if (twosComplement[i])
            number += powerOfTwo;
        powerOfTwo *= 2;
    }
    if (isNegative)
        number = -number;
    return number;
}

int main()
{
    printf("Enter two numbers:\n");
    int number1 = 0, number2 = 0;
    scanf("%d%d", &number1, &number2);

    bool* firstNumberTwosComplement = convertToTwosComplement(number1);
    bool* secondNumberTwosComplement = convertToTwosComplement(number2);
    printf("First number in two's complement notation:\n");
    printBinaryRepresentation(firstNumberTwosComplement);
    printf("Second number in two's complement notation:\n");
    printBinaryRepresentation(secondNumberTwosComplement);

    bool* sumTwosComplement = addInTwosComplement(firstNumberTwosComplement, secondNumberTwosComplement);
    printf("Sum in two's complement notation:\n");
    printBinaryRepresentation(sumTwosComplement);

    printf("Sum in decimal notation:\n%d", convertToDecimal(sumTwosComplement));

    free(firstNumberTwosComplement);
    free(secondNumberTwosComplement);
    free(sumTwosComplement);
    return 0;
}
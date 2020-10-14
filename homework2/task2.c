#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

const int numberOfDigits = 10;

bool isZeroTheFirstDigit(int position, int digit)
{
    return position == 0 && digit == 0;
}

int* generateSecretNumber(bool* isDigitUsed, int sizeOfSecretNumber)
{
    int* digitsOfSecretNumber = (int*)calloc(sizeOfSecretNumber, sizeof(int));
    for (int i = 0; i < sizeOfSecretNumber; ++i) {
        int newDigit = 0;
        do {
            newDigit = rand() % 10;
        } while (isDigitUsed[newDigit] || isZeroTheFirstDigit(i, newDigit));

        digitsOfSecretNumber[i] = newDigit;
        isDigitUsed[newDigit] = true;
    }

    return digitsOfSecretNumber;
}

bool isNumberCorrect(long long number, int sizeOfSecretNumber)
{
    if (number < 0)
        return false;

    bool isDigitUsed[numberOfDigits];
    memset(isDigitUsed, false, numberOfDigits * sizeof(bool));
    int sizeOfNumber = 0;
    while (number != 0) {
        if (isDigitUsed[number % 10])
            return false;

        isDigitUsed[number % 10] = true;
        ++sizeOfNumber;
        number /= 10;
    }

    return sizeOfNumber == sizeOfSecretNumber;
}

void countCowsAndBulls(long long number, int* digitsOfSecret, int sizeOfSecret, bool* isDigitUsedInSecret, int* cows, int* bulls)
{
    for (int i = 0; i < sizeOfSecret; ++i) {
        if (number % 10 == digitsOfSecret[sizeOfSecret - 1 - i])
            ++(*bulls);
        else if (isDigitUsedInSecret[number % 10])
            ++(*cows);

        number /= 10;
    }
}

void readSizeOfSecret(int* sizeOfSecretNumber)
{
    printf("Enter the size of the secret number (from 4 to 10):\n");
    do {
        scanf("%d", sizeOfSecretNumber);
        if (*sizeOfSecretNumber < 4 || *sizeOfSecretNumber > 10)
            printf("This number isn't from 4 to 10.\n");
    } while (*sizeOfSecretNumber < 4 || *sizeOfSecretNumber > 10);
}

int main()
{
    srand(time(0));

    int sizeOfSecretNumber = 0;
    readSizeOfSecret(&sizeOfSecretNumber);

    bool isDigitUsedInSecret[numberOfDigits];
    memset(isDigitUsedInSecret, false, numberOfDigits * sizeof(bool));
    int* digitsOfSecretNumber = generateSecretNumber(isDigitUsedInSecret, sizeOfSecretNumber);
    printf("The number is conceived. Try to guess. :)\n");
    printf("To do this, enter the natural numbers of the length you specified, in which the digits are not repeated.\n");

    int cows = 0, bulls = 0;
    while (bulls != sizeOfSecretNumber) {
        long long number = 0;
        scanf("%lld", &number);
        if (!isNumberCorrect(number, sizeOfSecretNumber)) {
            printf("Your number does not meet the requirements above.\n");
            continue;
        }

        countCowsAndBulls(number, digitsOfSecretNumber, sizeOfSecretNumber, isDigitUsedInSecret, &cows, &bulls);
        printf("%d cows, %d bulls\n", cows, bulls);
    }

    printf("You guessed right!");
    free(digitsOfSecretNumber);
    return 0;
}
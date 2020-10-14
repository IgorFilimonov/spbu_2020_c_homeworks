#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int* generateSecretNumber(bool* isDigitUsed, int sizeOfSecretNumber)
{
    int* digitsOfSecretNumber = (int*)calloc(sizeOfSecretNumber, sizeof(int));
    for (int i = 0; i < sizeOfSecretNumber; ++i) {
        int newDigit = 0;
        do
            newDigit = rand() % 10;
        while (isDigitUsed[newDigit] || i == 0 && newDigit == 0);

        digitsOfSecretNumber[i] = newDigit;
        isDigitUsed[newDigit] = true;
    }

    return digitsOfSecretNumber;
}

bool isNumberCorrect(long long number, int sizeOfSecretNumber)
{
    if (number < 0)
        return false;

    bool isDigitUsed[10] = { false };
    int sizeOfNumber = 0;
    while (number != 0) {
        if (isDigitUsed[number % 10])
            return false;

        isDigitUsed[number % 10] = true;
        ++sizeOfNumber;
        number /= 10;
    }

    if (sizeOfNumber != sizeOfSecretNumber)
        return false;
    return true;
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
    while (true) {
        scanf("%d", sizeOfSecretNumber);
        if (4 <= *sizeOfSecretNumber && *sizeOfSecretNumber <= 10)
            break;
        printf("This number isn't from 4 to 10.\n");
    }
}

int main()
{
    srand(time(0));

    int sizeOfSecretNumber = 0;
    readSizeOfSecret(&sizeOfSecretNumber);

    bool isDigitUsedInSecret[10] = { false };
    int* digitsOfSecretNumber = generateSecretNumber(isDigitUsedInSecret, sizeOfSecretNumber);
    printf("The number is conceived. Try to guess. :)\n");
    printf("To do this, enter the natural numbers of the length you specified, in which the digits are not repeated.\n");
    while (true) {
        long long number = 0;
        scanf("%lld", &number);
        if (!isNumberCorrect(number, sizeOfSecretNumber)) {
            printf("Your number does not meet the requirements above.\n");
            continue;
        }

        int cows = 0, bulls = 0;
        countCowsAndBulls(number, digitsOfSecretNumber, sizeOfSecretNumber, isDigitUsedInSecret, &cows, &bulls);
        printf("%d cows, %d bulls\n", cows, bulls);
        if (bulls == sizeOfSecretNumber) {
            printf("You guessed right!");

            free(digitsOfSecretNumber);
            return 0;
        }
    }
}
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

bool isNumberRight(long long number, int sizeOfSecretNumber)
{
    bool isDigitUsed[10] = {false};
    int sizeOfNumber = 0;
    while (number != 0) {
        if (isDigitUsed[number % 10])
            return false;
        ++sizeOfNumber;
        number /= 10;
    }
    if (sizeOfNumber != sizeOfSecretNumber)
        return false;
    return true;
}

void countCowsAndBulls()

int main()
{
    srand(time(0));
    int sizeOfSecretNumber = 0;
    scanf("%d", &sizeOfSecretNumber);
    bool isDigitUsedInSecret[10] = {false};
    int* digitsOfSecretNumber = generateSecretNumber(isDigitUsedInSecret, sizeOfSecretNumber);
    while (true) {
        long long number = 0;
        scanf("%lld", &number);
        if (!isNumberRight(number, sizeOfSecretNumber)) {
            continue;
        }
        int cows = 0, bulls = 0;
        for (int i = 0; i < sizeOfSecretNumber; ++i) {
            if (number % 10 == digitsOfSecretNumber[sizeOfSecretNumber - 1 - i])
                ++bulls;
            else if (isDigitUsedInSecret[number % 10])
                ++cows;
        }
        if (bulls == sizeOfSecretNumber) {
            free(digitsOfSecretNumber);
            return 0;
        }
    }
}
#include <stdio.h>

int factorialRecursive(int number)
{
    if (number == 0)
        return 1;
    return factorialRecursive(number - 1) * number;
}

int factorialIterative(int number)
{
    int factorial = 1;
    for (int i = 2; i <= number; i++)
        factorial *= i;
    return factorial;
}

int main()
{
    int number = 0;
    printf("Enter the number:\n");
    scanf("%d", &number);
    printf("FactorialRecursive: %d\n", factorialRecursive(number));
    printf("FactorialIterative: %d\n", factorialIterative(number));
    return 0;
}
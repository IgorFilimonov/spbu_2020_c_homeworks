#include <stdio.h>

long long findFibonacciNumberByNumber(int number)
{
    if (number == 0)
        return 0;
    if (number == 1)
        return 1;
    long long fibonacci1 = 0, fibonacci2 = 1, fibonacci3 = 0;
    for (int i = 2; i <= number; ++i) {
        fibonacci3 = fibonacci1 + fibonacci2;
        fibonacci1 = fibonacci2;
        fibonacci2 = fibonacci3;
    }
    return fibonacci3;
}

int main()
{
    printf("Enter the number of the Fibonacci number:\n");
    int numberOfFibonacciNumber = 0;
    scanf("%d", &numberOfFibonacciNumber);
    printf("Here's the number you need: %lld", findFibonacciNumberByNumber(numberOfFibonacciNumber));
    return 0;
}

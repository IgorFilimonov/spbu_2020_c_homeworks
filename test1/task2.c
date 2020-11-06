#include "../library/complexNumber.h"
#include <stdio.h>

int main()
{
    float realPartOfFirst = 0, imaginaryPartOfFirst = 0;
    printf("Enter the real and imaginary parts of the first complex number\n");
    scanf("%f%f", &realPartOfFirst, &imaginaryPartOfFirst);
    ComplexNumber* number1 = createComplexNumber(realPartOfFirst, imaginaryPartOfFirst);

    float realPartOfSecond = 0, imaginaryPartOfSecond = 0;
    printf("Enter the real and imaginary parts of the second complex number\n");
    scanf("%f%f", &realPartOfSecond, &imaginaryPartOfSecond);
    ComplexNumber* number2 = createComplexNumber(realPartOfSecond, imaginaryPartOfSecond);

    printf("Sum: ");
    ComplexNumber* sum = addComplexNumber(number1, number2);
    printComplexNumber(sum);
    destroyComplexNumber(sum);

    printf("Difference: ");
    ComplexNumber* difference = subtractComplexNumber(number1, number2);
    printComplexNumber(difference);
    destroyComplexNumber(difference);

    printf("Product: ");
    ComplexNumber* product = multiplyComplexNumber(number1, number2);
    printComplexNumber(product);
    destroyComplexNumber(product);

    printf("Quotient: ");
    ComplexNumber* quotient = divideComplexNumber(number1, number2);
    if (quotient == NULL)
        printf("You cannot divide by zero\n");
    else
        printComplexNumber(quotient);
    destroyComplexNumber(quotient);

    destroyComplexNumber(number1);
    destroyComplexNumber(number2);
    return 0;
}
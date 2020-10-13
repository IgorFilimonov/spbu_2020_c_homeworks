#include "complexNumber.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

struct ComplexNumber {
    float a, b; // a - real part, b - imaginary part
};

ComplexNumber* createComplexNumber(float realPart, float imaginaryPart)
{
    ComplexNumber* number = (ComplexNumber*)malloc(sizeof(ComplexNumber));
    number->a = realPart;
    number->b = imaginaryPart;
    return number;
}

void destroyComplexNumber(ComplexNumber* number)
{
    free(number);
}

ComplexNumber* addComplexNumber(ComplexNumber* number1, ComplexNumber* number2)
{
    float realPartOfSum = number1->a + number2->a;
    float imaginaryPartOfSum = number1->b + number2->b;
    ComplexNumber* sum = createComplexNumber(realPartOfSum, imaginaryPartOfSum);
    return sum;
}

ComplexNumber* subtractComplexNumber(ComplexNumber* minuend, ComplexNumber* subtrahend)
{
    float realPartOfDifference = minuend->a - subtrahend->a;
    float imaginaryPartOfDifference = minuend->b - subtrahend->b;
    ComplexNumber* difference = createComplexNumber(realPartOfDifference, imaginaryPartOfDifference);
    return difference;
}

ComplexNumber* multiplyComplexNumber(ComplexNumber* number1, ComplexNumber* number2)
{
    float realPartOfProduct = number1->a * number2->a - number1->b * number2->b;
    float imaginaryPartOfProduct = number1->b * number2->a + number1->a * number2->b;
    ComplexNumber* product = createComplexNumber(realPartOfProduct, imaginaryPartOfProduct);
    return product;
}

ComplexNumber* divideComplexNumber(ComplexNumber* dividend, ComplexNumber* divider)
{
    if (divider->a == 0 && divider->b == 0) // you cannot divide by zero
        return NULL;

    float realPartOfQuotient = dividend->a * divider->a + dividend->b * divider->b;
    realPartOfQuotient /= (pow(divider->a, 2) + pow(divider->b, 2));

    float imaginaryPartOfQuotient = dividend->b * divider->a - dividend->a * divider->b;
    imaginaryPartOfQuotient /= (pow(divider->a, 2) + pow(divider->b, 2));

    ComplexNumber* quotient = createComplexNumber(realPartOfQuotient, imaginaryPartOfQuotient);
    return quotient;
}

void printComplexNumber(ComplexNumber* number)
{
    if (number == NULL)
        printf("NULL\n");
    else
        printf("%f + %fi\n", number->a, number->b);
}
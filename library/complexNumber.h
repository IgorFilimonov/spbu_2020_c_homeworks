#ifndef SPBU_2020_C_HOMEWORKS_COMPLEXNUMBER_H
#define SPBU_2020_C_HOMEWORKS_COMPLEXNUMBER_H

typedef struct ComplexNumber ComplexNumber;

ComplexNumber* createComplexNumber(float realPart, float imaginaryPart);

void destroyComplexNumber(ComplexNumber* number);

ComplexNumber* addComplexNumber(ComplexNumber* number1, ComplexNumber* number2);

ComplexNumber* subtractComplexNumber(ComplexNumber* minuend, ComplexNumber* subtrahend);

ComplexNumber* multiplyComplexNumber(ComplexNumber* number1, ComplexNumber* number2);

ComplexNumber* divideComplexNumber(ComplexNumber* dividend, ComplexNumber* divider);

void printComplexNumber(ComplexNumber* number);

#endif //SPBU_2020_C_HOMEWORKS_COMPLEXNUMBER_H

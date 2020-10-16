#include "../library/commonUtils/arrayOperations.h"
#include "../library/stack.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

bool isDigit(char c)
{
    return '0' <= c && c <= '9';
}

double convertStringToNumber(char* string, int* firstDigitIndex)
{
    int i = *firstDigitIndex;
    double number = 0;
    for (; isDigit(string[i]); ++i) {
        number *= 10;
        number += string[i] - '0';
    }
    *firstDigitIndex = i;
    return number;
}

bool isOperation(char c)
{
    return '*' <= c && c <= '/';
}

void performNumericOperation(Stack* numbers, char operation)
{
    StackElement* number2 = pop(numbers);
    StackElement* number1 = pop(numbers);
    if (operation == '+')
        push(numbers, createStackElement(getValue(number1) + getValue(number2)));
    if (operation == '-')
        push(numbers, createStackElement(getValue(number1) - getValue(number2)));
    if (operation == '*')
        push(numbers, createStackElement(getValue(number1) * getValue(number2)));
    if (operation == '/')
        push(numbers, createStackElement(getValue(number1) / getValue(number2)));

    deleteStackElement(number1);
    deleteStackElement(number2);
}

double calculateExpressionValue(char* expression)
{
    Stack* numbers = createStack();
    for (int i = 0; i < strlen(expression); ++i) {
        if (isDigit(expression[i]))
            push(numbers, createStackElement(convertStringToNumber(expression, &i)));
        if (isOperation(expression[i]))
            performNumericOperation(numbers, expression[i]);
    }

    StackElement* element = pop(numbers);
    double expressionValue = getValue(element);
    deleteStackElement(element);
    deleteStack(numbers);
    return expressionValue;
}

int main()
{
    printf("Enter expression in postfix notation:\n");
    char* expression = readString();
    printf("Here is the value of your expression: %lf", calculateExpressionValue(expression));
    return 0;
}
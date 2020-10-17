#include "../library/commonUtils/arrayOperations.h"
#include "../library/stack.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

double convertStringToNumber(char* string, int* firstDigitIndex)
{
    int i = *firstDigitIndex;
    double number = 0;
    for (; isdigit(string[i]); ++i) {
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
    switch (operation) {
    case '+':
        push(numbers, createStackElement(getValue(number1) + getValue(number2)));
        break;
    case '-':
        push(numbers, createStackElement(getValue(number1) - getValue(number2)));
        break;
    case '*':
        push(numbers, createStackElement(getValue(number1) * getValue(number2)));
        break;
    case '/':
        push(numbers, createStackElement(getValue(number1) / getValue(number2)));
    }

    deleteStackElement(number1);
    deleteStackElement(number2);
}

double calculateExpressionValue(char* expression)
{
    Stack* numbers = createStack();
    for (int i = 0; i < strlen(expression); ++i) {
        if (isdigit(expression[i]))
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
    free(expression);
    return 0;
}
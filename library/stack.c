#include "stack.h"
#include <stdlib.h>

struct StackElement {
    double value;
    StackElement* next;
};

struct Stack {
    StackElement* top;
    int size;
};

StackElement* createStackElement(double value)
{
    StackElement* element = (StackElement*)malloc(sizeof(StackElement));
    element->value = value;
    element->next = NULL;
    return element;
}

Stack* createStack()
{
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->top = NULL;
    stack->size = 0;
    return stack;
}

void push(Stack* stack, StackElement* newElement)
{
    newElement->next = stack->top;
    stack->top = newElement;
    stack->size++;
}

bool isEmpty(Stack* stack)
{
    return stack->size == 0;
}

StackElement* pop(Stack* stack)
{
    if (isEmpty(stack))
        return NULL;

    StackElement* element = stack->top;
    stack->top = element->next;
    element->next = NULL;
    stack->size--;
    return element;
}

void deleteStackElement(StackElement* stackElement)
{
    free(stackElement);
}

void deleteStack(Stack* stack)
{
    while (!isEmpty(stack)) {
        StackElement* element = pop(stack);
        deleteStackElement(element);
    }
    free(stack);
}

int getSize(Stack* stack)
{
    return stack->size;
}

double getValue(StackElement* element)
{
    return element->value;
}
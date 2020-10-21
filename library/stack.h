#ifndef PSP_STACK_H
#define PSP_STACK_H

#include <stdbool.h>

typedef struct Stack Stack;

typedef struct StackElement StackElement;

Stack* createStack();

StackElement* createStackElement(double value);

void push(Stack* stack, StackElement* newElement);

StackElement* pop(Stack* stack);

bool isEmpty(Stack* stack);

void deleteStackElement(StackElement* stackELement);

void deleteStack(Stack* stack);

int getSize(Stack* stack);

double getValue(StackElement* element);

#endif //PSP_STACK_H

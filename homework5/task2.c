#include "../library/avl.h"
#include <stdio.h>

void displayHints()
{
    printf("What do you want to do?\n"
           "1. Add value to set\n"
           "2. Remove value\n"
           "3. Check if value belongs to set\n"
           "4. Print the elements of a set in ascending order\n"
           "5. Print the elements of the set in descending order\n"
           "6. Print the elements in a special form\n"
           "0. Shut down\n"
           "To select, enter the command number:\n");
}

void executeCommand(int typeOfCommand, AVLTree* setOfNumbers)
{
    switch (typeOfCommand) {
    case 1: {
        printf("Enter value:\n");
        int value = 0;
        scanf("%d", &value);
        if (!addValue(setOfNumbers, value))
            printf("The value is already in the set\n");
        break;
    }
    case 2: {
        if (isEmpty(setOfNumbers))
            printf("The tree is empty\n");
        else {
            printf("Enter value:\n");
            int value = 0;
            scanf("%d", &value);
            if (!deleteValue(setOfNumbers, value))
                printf("There is no such number in the set\n");
        }
        break;
    }
    case 3: {
        printf("Enter value:\n");
        int value = 0;
        scanf("%d", &value);
        if (isValueInTree(setOfNumbers, value))
            printf("The set has this number\n");
        else
            printf("The set hasn't this number\n");
        break;
    }
    case 4:
        printf("Here are the elements of the set in ascending order\n");
        printTreeInAscendingOrder(setOfNumbers);
        break;
    case 5:
        printf("Here are the elements of the set in descending order\n");
        printTreeInDescendingOrder(setOfNumbers);
        break;
    case 6:
        printf("Here are the elements of the set, output in a special form\n");
        printTree(setOfNumbers);
        break;
    default:
        if (typeOfCommand != 0)
            printf("Invalid command number entered\n");
    }
}

int main()
{
    AVLTree* setOfNumbers = createTree();
    int typeOfCommand = -1;
    while (typeOfCommand != 0) {
        displayHints();
        scanf("%d", &typeOfCommand);
        executeCommand(typeOfCommand, setOfNumbers);
    }
    destroyTree(setOfNumbers);
    return 0;
}

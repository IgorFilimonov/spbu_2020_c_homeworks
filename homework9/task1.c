#include "../library/commonUtils/arrayOperations.h"
#include "../library/parser/parser.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("Enter expression:\n");
    char* expression = readString();

    if (isCorrectForParser(expression))
        printf("This expression is valid");
    else
        printf("This expression is invalid");

    free(expression);
    return 0;
}
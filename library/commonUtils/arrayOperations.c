#include "arrayOperations.h"
#include <stdio.h>
#include <stdlib.h>

char* readString()
{
    int maxSize = 100;
    char* string = (char*)calloc(maxSize, sizeof(char));
    char currentChar = getchar();
    int realSize = 0;
    for (realSize = 0; currentChar != '\n'; ++realSize) {
        if (realSize == maxSize) {
            maxSize *= 2;
            string = (char*)realloc(string, maxSize);
        }

        string[realSize] = currentChar;
        currentChar = getchar();
    }

    if (realSize == maxSize)
        string = (char*)realloc(string, realSize + 1);
    string[realSize] = '\0';

    return string;
}
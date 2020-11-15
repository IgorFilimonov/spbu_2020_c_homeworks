#include "../library/hashtable.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

char* readNextWord(FILE* inputText, bool* isEndOfFileReached)
{
    int maxSize = 100;
    char* word = (char*)calloc(maxSize, sizeof(char));
    int realSize = 0;
    *isEndOfFileReached = false;
    for (; !*isEndOfFileReached; ++realSize) {
        if (realSize == maxSize) {
            maxSize *= 2;
            word = (char*)realloc(word, maxSize);
        }

        char currentChar = fgetc(inputText);
        if (!isalpha(currentChar)) {
            if (feof(inputText))
                *isEndOfFileReached = true;
            break;
        }
        word[realSize] = tolower(currentChar);
    }

    if (realSize == maxSize)
        word = (char*)realloc(word, realSize + 1);
    word[realSize] = '\0';

    return word;
}

int main()
{
    FILE* inputText = fopen("C:\\text.txt", "r");
    if (inputText == NULL) {
        printf("Couldn't open the file");
        return 0;
    }

    HashTable* hashTable = createHashTable(2);
    bool isEndOfFileReached = false;
    while (!isEndOfFileReached) {
        char* word = readNextWord(inputText, &isEndOfFileReached);
        if (word[0] != '\0')
            pushByKey(hashTable, word);
        free(word);
    }

    printHashTableStats(hashTable);

    fclose(inputText);
    destroyHashTable(hashTable);
    return 0;
}

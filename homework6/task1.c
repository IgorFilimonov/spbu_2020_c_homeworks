#include "../library/hashtable.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readNextWord(FILE* inputText, bool* isEndOfFileReached)
{
    int maxSize = 100;
    char* word = (char*)calloc(maxSize, sizeof(char));
    int realSize = 0;
    char currentChar = fgetc(inputText);
    while (isalpha(currentChar)) {
        word[realSize] = tolower(currentChar);
        ++realSize;

        if (realSize == maxSize) {
            maxSize *= 2;
            word = (char*)realloc(word, maxSize);
            memset(&word[realSize], '\0', maxSize - realSize);
        }
        currentChar = fgetc(inputText);
    }
    *isEndOfFileReached = feof(inputText) != 0;

    if (realSize == maxSize)
        word = (char*)realloc(word, realSize + 1);
    word[realSize] = '\0';

    return word;
}

int getHash(char* key, int polynomFactor, int module)
{
    int currentHash = 0;
    for (int i = 0; i < strlen(key); ++i)
        currentHash = ((currentHash * polynomFactor) + (key[i] - 'a')) % module;
    return currentHash;
}

int getNewIndex(int hash, int attempt, int module)
{
    return (hash + (attempt + attempt * attempt) / 2) % module;
}

int main()
{
    FILE* inputText = fopen("../homework6/text.txt", "r");
    if (inputText == NULL) {
        printf("Couldn't open the file");
        return 0;
    }

    HashTable* hashTable = createHashTable(2, getHash, getNewIndex);
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

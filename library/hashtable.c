#include "hashtable.h"
#include "commonUtils/numericOperations.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct HashElement {
    char* key;
    int amount;
    int attemptsToPush;
} HashElement;

enum CellType {
    empty,
    used,
    deleted
};

struct HashTable {
    HashElement** hashTable;
    enum CellType* types;
    int bucketCount;
    int elementCount;
    int polynomFactor;
    int (*getHash)(char*, int, int);
    int (*getNewIndex)(int, int, int);
};

HashElement* createHashElement(char* key)
{
    HashElement* newElement = (HashElement*)malloc(sizeof(HashElement));

    newElement->key = (char*)malloc(sizeof(char) * (strlen(key) + 1));
    strcpy(newElement->key, key);
    newElement->amount = 1;
    newElement->attemptsToPush = 0;

    return newElement;
}

void initializeHashTable(HashTable* table, int size, int polynomFactor, int (*getHash)(char*, int, int), int (*getNewIndex)(int, int, int));

HashTable* createHashTableWithSize(int size, int polynomFactor, int (*getHash)(char*, int, int), int (*getNewIndex)(int, int, int))
{
    HashTable* newTable = (HashTable*)malloc(sizeof(HashTable));
    initializeHashTable(newTable, size, polynomFactor, getHash, getNewIndex);
    return newTable;
}

void initializeHashTable(HashTable* table, int size, int polynomFactor, int (*getHash)(char*, int, int), int (*getNewIndex)(int, int, int))
{
    table->hashTable = (HashElement**)malloc(sizeof(HashElement*) * size);
    memset(table->hashTable, 0, size * sizeof(HashElement*));
    table->types = (enum CellType*)malloc(sizeof(enum CellType) * size);
    memset(table->types, (int)empty, size * sizeof(enum CellType));
    table->bucketCount = size;
    table->elementCount = 0;
    table->polynomFactor = polynomFactor;
    table->getHash = getHash;
    table->getNewIndex = getNewIndex;
}

HashTable* createHashTable(int polynomFactor, int (*getHash)(char*, int, int), int (*getNewIndex)(int, int, int))
{
    return createHashTableWithSize(1, polynomFactor, getHash, getNewIndex);
}

void destroyHashElement(HashElement* element)
{
    free(element->key);
    free(element);
}

void destroyHashTable(HashTable* table)
{
    for (int i = 0; i < table->bucketCount; ++i) {
        if (table->types[i] == used)
            destroyHashElement(table->hashTable[i]);
    }
    free(table->hashTable);
    free(table->types);
    free(table);
}

const float MAX_LOAD_FACTOR = 0.7;

float getLoadFactor(HashTable* hashTable)
{
    return (float)hashTable->elementCount / (float)hashTable->bucketCount;
}

int findPositionToPush(HashTable* table, HashElement* element);

void expandHashTable(HashTable* table);

void pushElement(HashTable* table, HashElement* element)
{
    int positionToPush = findPositionToPush(table, element);
    if (table->types[positionToPush] == used) {
        table->hashTable[positionToPush]->amount += element->amount;
        destroyHashElement(element);
    } else {
        table->hashTable[positionToPush] = element;
        table->types[positionToPush] = used;
        ++table->elementCount;

        if (getLoadFactor(table) > MAX_LOAD_FACTOR)
            expandHashTable(table);
    }
}

int findPositionToPush(HashTable* table, HashElement* element)
{
    int hash = table->getHash(element->key, table->polynomFactor, table->bucketCount);
    int currentIndex = hash;
    for (int attempt = 1; attempt <= table->bucketCount; ++attempt) {
        if (table->types[currentIndex] == used) {
            if (strcmp(table->hashTable[currentIndex]->key, element->key) == 0) {
                if (attempt > table->hashTable[currentIndex]->attemptsToPush)
                    table->hashTable[currentIndex]->attemptsToPush = attempt;
                break;
            }
            currentIndex = table->getNewIndex(hash, attempt, table->bucketCount);
        } else {
            if (attempt > element->attemptsToPush)
                element->attemptsToPush = attempt;
            break;
        }
    }
    return currentIndex;
}

void expandHashTable(HashTable* table)
{
    HashElement** oldElements = table->hashTable;
    enum CellType* oldTypes = table->types;
    int oldSize = table->bucketCount;
    int size = table->bucketCount * 2;
    initializeHashTable(table, size, table->polynomFactor, table->getHash, table->getNewIndex);

    for (int i = 0; i < oldSize; ++i) {
        if (oldTypes[i] != used)
            continue;
        pushElement(table, oldElements[i]);
    }

    free(oldElements);
    free(oldTypes);
}

void pushByKey(HashTable* table, char* key)
{
    pushElement(table, createHashElement(key));
}

bool deleteElement(HashTable* table, char* key)
{
    int hash = table->getHash(key, table->polynomFactor, table->bucketCount);
    int currentIndex = hash;
    for (int i = 0; i < table->bucketCount; ++i) {
        if (table->types[currentIndex] == empty)
            return false;
        else {
            if (table->types[currentIndex] == used) {
                if (strcmp(table->hashTable[currentIndex]->key, key) == 0) {
                    --table->hashTable[currentIndex]->amount;
                    if (table->hashTable[currentIndex]->amount == 0) {
                        table->types[currentIndex] = deleted;
                        destroyHashElement(table->hashTable[currentIndex]);
                        --table->elementCount;
                    }
                    return true;
                }
            }
            currentIndex = table->getNewIndex(hash, i, table->bucketCount);
        }
    }

    return false;
}

int getTotalNumberOfAttempts(HashTable* table);

int getMaximumNumberOfAttempts(HashTable* table);

void printElementsWithRequiredNumberOfAttempts(HashTable* table, int numberOfAttempts);

void printTheMostCommonElements(HashTable* table, int numberOfElement);

void printHashTableStats(HashTable* table)
{
    printf("Load factor: %f\n", getLoadFactor(table));

    int totalNumberOfAttempts = getTotalNumberOfAttempts(table);
    float averageNumberOfAttempts = 0;
    if (table->elementCount != 0)
        averageNumberOfAttempts = (float)totalNumberOfAttempts / (float)table->elementCount;
    printf("Average number of attempts to push: %f\n", averageNumberOfAttempts);

    int maximumNumberOfAttempts = getMaximumNumberOfAttempts(table);
    printf("Maximum number of attempts to push: %d\n", maximumNumberOfAttempts);
    printf("Elements with the maximum number of attempts to push:\n");
    printElementsWithRequiredNumberOfAttempts(table, maximumNumberOfAttempts);

    printf("Total number of added elements: %d\n", table->elementCount);
    printf("Number of empty table cells: %d\n", table->bucketCount - table->elementCount);

    printf("Top 10 most used words:\n");
    printTheMostCommonElements(table, 10);
}

int getTotalNumberOfAttempts(HashTable* table)
{
    int totalNumberOfAttempts = 0;
    for (int i = 0; i < table->bucketCount; ++i) {
        if (table->types[i] == used)
            totalNumberOfAttempts += table->hashTable[i]->attemptsToPush;
    }

    return totalNumberOfAttempts;
}

int getMaximumNumberOfAttempts(HashTable* table)
{
    int maximumNumberOfAttempts = 0;
    for (int i = 0; i < table->bucketCount; ++i) {
        if (table->types[i] == used) {
            if (table->hashTable[i]->attemptsToPush > maximumNumberOfAttempts)
                maximumNumberOfAttempts = table->hashTable[i]->attemptsToPush;
        }
    }

    return maximumNumberOfAttempts;
}

void printElementsWithRequiredNumberOfAttempts(HashTable* table, int numberOfAttempts)
{
    for (int i = 0; i < table->bucketCount; ++i) {
        if (table->types[i] == used && table->hashTable[i]->attemptsToPush == numberOfAttempts)
            printf("%s\n", table->hashTable[i]->key);
    }
}

void printTheMostCommonElements(HashTable* table, int numberOfElements)
{
    bool* isElementSelected = (bool*)calloc(table->bucketCount, sizeof(bool));
    for (int i = 1; i <= min(numberOfElements, table->elementCount); ++i) {
        int hashOfMostCommon = -1;
        for (int j = 0; j < table->bucketCount; ++j) {
            if (table->types[j] == used && isElementSelected[j] == false) {
                if (hashOfMostCommon == -1 || table->hashTable[j]->amount > table->hashTable[hashOfMostCommon]->amount)
                    hashOfMostCommon = j;
            }
        }
        isElementSelected[hashOfMostCommon] = true;
        printf("%d. %s (%d times)\n", i, table->hashTable[hashOfMostCommon]->key, table->hashTable[hashOfMostCommon]->amount);
    }

    free(isElementSelected);
}

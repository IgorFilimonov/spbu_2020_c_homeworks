#include "hashtable.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct HashElement {
    char* key;
    int amount;
    int attemptsToPush;
} HashElement;

enum CellType { empty,used };

struct HashTable {
    HashElement** hashTable;
    enum CellType* types;
    int bucketCount;
    int elementCount;
    int polynomFactor;
};

HashElement* createHashElement(char* key)
{
    HashElement* newElement = (HashElement*)malloc(sizeof(HashElement));

    newElement->key = (char*)malloc(sizeof(char) * strlen(key));
    strcpy(newElement->key, key);
    newElement->amount = 1;
    newElement->attemptsToPush = 0;

    return newElement;
}

void initializeHashTable(HashTable* table, int size, int polynomFactor);

HashTable* createHashTableWithSize(int size, int polynomFactor)
{
    HashTable* newTable = (HashTable*)malloc(sizeof(HashTable));
    initializeHashTable(newTable, size, polynomFactor);
    return newTable;
}

void initializeHashTable(HashTable* table, int size, int polynomFactor)
{
    table->hashTable = (HashElement**)malloc(sizeof(HashElement*) * size);
    memset(table->hashTable, 0, size * sizeof(HashElement*));
    table->types = (enum CellType*)malloc(sizeof(enum CellType) * size);
    memset(table->types, (int)empty, size * sizeof(enum CellType));
    table->bucketCount = size;
    table->elementCount = 0;
    table->polynomFactor = polynomFactor;
}

HashTable* createHashTable(int polynomFactor)
{
    return createHashTableWithSize(1, polynomFactor);
}

int getHash(char* key, int polynomFactor, int module)
{
    int currentHash = 0;
    for (int i = 0; i < strlen(key); ++i)
        currentHash = ((currentHash * polynomFactor) + (key[i] - 'a')) % module;
    return currentHash;
}

const float MAX_LOAD_FACTOR = 0.7;

float getLoadFactor(HashTable* hashTable)
{
    return (float)hashTable->elementCount / (float)hashTable->bucketCount;
}

int getNewIndex(int hash, int attempt, int module)
{
    return (hash + (attempt + attempt * attempt) / 2) % module;
}

void expandHashTable(HashTable* table);

void pushElement(HashTable* table, HashElement* element)
{
    int hash = getHash(element->key, table->polynomFactor, table->bucketCount);
    int currentIndex = hash;
    for (int attempt = 1; attempt <= table->bucketCount; ++attempt) {
        if (table->types[currentIndex] == used) {
            if (strcmp(table->hashTable[currentIndex]->key, element->key) == 0) {
                table->hashTable[currentIndex]->amount += element->amount;
                if (attempt > table->hashTable[currentIndex]->attemptsToPush)
                    table->hashTable[currentIndex]->attemptsToPush = attempt;
                return;
            }
            currentIndex = getNewIndex(hash, attempt, table->bucketCount);
        } else {
            if (attempt > element->attemptsToPush)
                element->attemptsToPush = attempt;
            table->hashTable[currentIndex] = element;
            table->types[currentIndex] = used;
            ++table->elementCount;

            if (getLoadFactor(table) > MAX_LOAD_FACTOR)
                expandHashTable(table);

            return;
        }
    }
}

void expandHashTable(HashTable* table)
{
    HashElement** oldElements = table->hashTable;
    enum CellType* oldTypes = table->types;
    int oldSize = table->bucketCount;
    int size = table->bucketCount * 2;
    initializeHashTable(table, size, table->polynomFactor);

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

void printTheMostCommonElements(HashTable* table);

void printHashTableStats(HashTable* table)
{
    printf("Load factor: %f\n", getLoadFactor(table));

    int totalNumberOfAttempts = 0;
    int maximumNumberOfAttempts = 0;
    for (int i = 0; i < table->bucketCount; ++i) {
        if (table->types[i] == used) {
            totalNumberOfAttempts += table->hashTable[i]->attemptsToPush;
            if (table->hashTable[i]->attemptsToPush > maximumNumberOfAttempts)
                maximumNumberOfAttempts = table->hashTable[i]->attemptsToPush;
        }
    }

    float averageNumberOfAttempts = 0;
    if (table->elementCount != 0)
        averageNumberOfAttempts = (float)totalNumberOfAttempts / (float)table->elementCount;
    printf("Average number of attempts to push: %f\n", averageNumberOfAttempts);
    printf("Maximum number of attempts to push: %d\n", maximumNumberOfAttempts);
    printf("Elements with the maximum number of attempts to push:\n");
    for (int i = 0; i < table->bucketCount; ++i) {
        if (table->types[i] == used && table->hashTable[i]->attemptsToPush == maximumNumberOfAttempts)
            printf("%s\n", table->hashTable[i]->key);
    }

    printf("Total number of added elements: %d\n", table->elementCount);
    printf("Number of empty table cells: %d\n", table->bucketCount - table->elementCount);

    printf("Top 10 most used words:\n");
    printTheMostCommonElements(table);
}

void printTheMostCommonElements(HashTable* table)
{
    bool* isElementSelected = (bool*)calloc(table->bucketCount, sizeof(bool));
    for (int i = 1; i <= 10 && i <= table->elementCount; ++i) {
        int hashOfMostCommon = -1;
        for (int j = 0; j < table->bucketCount; ++j) {
            if (table->types[j] == used
            && isElementSelected[j] == false
            && (hashOfMostCommon == -1 || table->hashTable[j]->amount > table->hashTable[hashOfMostCommon]->amount))
                hashOfMostCommon = j;
        }
        isElementSelected[hashOfMostCommon] = true;
        printf("%d. %s\n", i, table->hashTable[hashOfMostCommon]->key);
    }

    free(isElementSelected);
}

void destroyHashTable(HashTable* table)
{
    for (int i = 0; i < table->bucketCount; ++i)
        free(table->hashTable[i]);
    free(table->hashTable);
    free(table->types);
    free(table);
}

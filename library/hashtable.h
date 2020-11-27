#ifndef SPBU_2020_C_HOMEWORKS_HASHTABLE_H
#define SPBU_2020_C_HOMEWORKS_HASHTABLE_H

#include <stdbool.h>

typedef struct HashTable HashTable;

HashTable* createHashTableWithSize(int size, int polynomFactor, int (*getHash)(char*, int, int), int (*getNextIndex)(int, int, int));

HashTable* createHashTable(int polynomFactor, int (*getHash)(char*, int, int), int (*getNewIndex)(int, int, int));

void destroyHashTable(HashTable* table);

void pushByKey(HashTable* table, char* key);

bool deleteElement(HashTable* table, char* key);

void printHashTableStats(HashTable* table);

#endif //SPBU_2020_C_HOMEWORKS_HASHTABLE_H

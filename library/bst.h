#ifndef SPBU_2020_C_HOMEWORKS_BST_H
#define SPBU_2020_C_HOMEWORKS_BST_H

#include <stdbool.h>

typedef struct BinarySearchTree BinarySearchTree;

BinarySearchTree* createTree();

bool isEmpty(BinarySearchTree* tree);

bool addValue(BinarySearchTree* tree, int value);

void printTreeInAscendingOrder(BinarySearchTree* tree);

void printTreeInDescendingOrder(BinarySearchTree* tree);

void printTree(BinarySearchTree* tree);

bool isValueInTree(BinarySearchTree* tree, int value);

bool deleteValue(BinarySearchTree* tree, int value);

void destroyTree(BinarySearchTree* tree);

#endif //SPBU_2020_C_HOMEWORKS_BST_H

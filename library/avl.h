#ifndef IDIOT_AVL_H
#define IDIOT_AVL_H

#include <stdbool.h>

typedef struct AVLTree AVLTree;

AVLTree* createTree();

bool isEmpty(AVLTree* tree);

bool addValue(AVLTree* tree, int value);

void printTreeInAscendingOrder(AVLTree* tree);

void printTreeInDescendingOrder(AVLTree* tree);

void printTree(AVLTree* tree);

bool isValueInTree(AVLTree* tree, int value);

bool deleteValue(AVLTree* tree, int value);

void destroyTree(AVLTree* tree);

#endif //IDIOT_AVL_H

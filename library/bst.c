#include "bst.h"
#include "bst_node.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct BinarySearchTree {
    TreeNode* root;
};

BinarySearchTree* createTree()
{
    BinarySearchTree* newTree = (BinarySearchTree*)malloc(sizeof(BinarySearchTree));
    newTree->root = NULL;
    return newTree;
}

bool isEmpty(BinarySearchTree* tree)
{
    return tree != NULL && tree->root == NULL;
}

bool addValue(BinarySearchTree* tree, int value)
{
    if (tree == NULL)
        return false;

    if (isEmpty(tree)) {
        tree->root = createTreeNode(value);
        return true;
    }

    return addValueRecursive(tree->root, value);
}

void printTreeInAscendingOrder(BinarySearchTree* tree)
{
    if (tree == NULL) {
        printf("It's not a tree\n");
        return;
    }
    if (isEmpty(tree))
        printf("The tree is empty\n");
    else {
        printTreeInAscendingOrderRecursive(tree->root);
        printf("\n");
    }
}

void printTreeInDescendingOrder(BinarySearchTree* tree)
{
    if (tree == NULL) {
        printf("It's not a tree\n");
        return;
    }
    if (isEmpty(tree))
        printf("The tree is empty\n");
    else {
        printTreeInDescendingOrderRecursive(tree->root);
        printf("\n");
    }
}

void printTree(BinarySearchTree* tree)
{
    if (tree == NULL) {
        printf("It's not a tree\n");
        return;
    }
    if (isEmpty(tree))
        printf("The tree is empty\n");
    else {
        printTreeRecursive(tree->root);
        printf("\n");
    }
}

bool isValueInTree(BinarySearchTree* tree, int value)
{
    if (tree == NULL || isEmpty(tree))
        return false;
    return isValueInTreeRecursive(tree->root, value);
}

bool deleteValue(BinarySearchTree* tree, int value)
{
    if (tree == NULL || isEmpty(tree))
        return false;
    TreeNode* newRoot = NULL;
    bool isNeedToDeleteRoot = tree->root->value == value;
    if (deleteValueRecursive(tree->root, value, NULL, &newRoot, NULL)) {
        if (isNeedToDeleteRoot)
            tree->root = newRoot;
        return true;
    }
    return false;
}

void destroyTree(BinarySearchTree* tree)
{
    if (tree != NULL) {
        destroyTreeRecursive(tree->root);
        free(tree);
    }
}

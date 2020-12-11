#include "../commonUtils/numericOperations.h"
#include "avl.h"
#include "bst_node.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct AVLTree {
    TreeNode* root;
};

AVLTree* createTree()
{
    AVLTree* newTree = (AVLTree*)malloc(sizeof(AVLTree));
    newTree->root = NULL;
    return newTree;
}

int getHeight(TreeNode* node)
{
    return node == NULL ? 0 : node->height;
}

void updateHeight(TreeNode* node)
{
    if (node != NULL) {
        int leftChildHeight = getHeight(node->leftChild);
        int rightChildHeight = getHeight(node->rightChild);
        node->height = max(leftChildHeight, rightChildHeight) + 1;
    }
}

int getBalanceFactor(TreeNode* node);

TreeNode* rotateLeft(TreeNode* root);

TreeNode* rotateRight(TreeNode* root);

TreeNode* balance(TreeNode* root)
{
    if (root == NULL)
        return NULL;

    if (getBalanceFactor(root) == 2) {
        if (getBalanceFactor(root->rightChild) < 0)
            root->rightChild = rotateRight(root->rightChild);
        return rotateLeft(root);
    }
    if (getBalanceFactor(root) == -2) {
        if (getBalanceFactor(root->leftChild) > 0)
            root->leftChild = rotateLeft(root->leftChild);
        return rotateRight(root);
    }
    return root;
}

int getBalanceFactor(TreeNode* node)
{
    return getHeight(node->rightChild) - getHeight(node->leftChild);
}

TreeNode* rotateLeft(TreeNode* root)
{
    TreeNode* pivot = root->rightChild;
    root->rightChild = pivot->leftChild;
    pivot->leftChild = root;
    updateHeight(root);
    updateHeight(pivot);
    return pivot;
}

TreeNode* rotateRight(TreeNode* root)
{
    TreeNode* pivot = root->leftChild;
    root->leftChild = pivot->rightChild;
    pivot->rightChild = root;
    updateHeight(root);
    updateHeight(pivot);
    return pivot;
}

bool isEmpty(AVLTree* tree)
{
    return tree != NULL && tree->root == NULL;
}

void findNodeAndBalance(TreeNode* node, int desiredValue)
{
    if (node->value == desiredValue) {
        node->rightChild = balance(node->rightChild);
        node->leftChild = balance(node->leftChild);
    }

    if (node->value < desiredValue) {
        findNodeAndBalance(node->rightChild, desiredValue);
        node->rightChild = balance(node->rightChild);
    }

    if (node->value > desiredValue) {
        findNodeAndBalance(node->leftChild, desiredValue);
        node->leftChild = balance(node->leftChild);
    }

    updateHeight(node);
}

bool addValue(AVLTree* tree, int value)
{
    if (tree == NULL)
        return false;

    if (isEmpty(tree)) {
        tree->root = createTreeNode(value);
        return true;
    }

    if (addValueRecursive(tree->root, value)) {
        findNodeAndBalance(tree->root, value);
        tree->root = balance(tree->root);
        return true;
    } else
        return false;
}

void printTreeInAscendingOrder(AVLTree* tree)
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

void printTreeInDescendingOrder(AVLTree* tree)
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

void printTree(AVLTree* tree)
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

bool isValueInTree(AVLTree* tree, int value)
{
    if (tree == NULL || isEmpty(tree))
        return false;
    return isValueInTreeRecursive(tree->root, value);
}

bool deleteValue(AVLTree* tree, int value)
{
    if (tree == NULL || isEmpty(tree))
        return false;

    TreeNode* newRoot = NULL;
    TreeNode* nodeForBalancing = NULL;
    bool isNeedToDeleteRoot = tree->root->value == value;
    if (deleteValueRecursive(tree->root, value, NULL, &newRoot, &nodeForBalancing)) {
        if (isNeedToDeleteRoot)
            tree->root = newRoot;
        if (nodeForBalancing != NULL)
            findNodeAndBalance(tree->root, nodeForBalancing->value);
        tree->root = balance(tree->root);
        return true;
    }
    return false;
}

void destroyTree(AVLTree* tree)
{
    if (tree != NULL) {
        destroyTreeRecursive(tree->root);
        free(tree);
    }
}

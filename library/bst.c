#include "bst.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int value;
    struct TreeNode* leftChild;
    struct TreeNode* rightChild;
} TreeNode;

struct BinarySearchTree {
    TreeNode* root;
};

BinarySearchTree* createTree()
{
    BinarySearchTree* newTree = (BinarySearchTree*)malloc(sizeof(BinarySearchTree));
    newTree->root = NULL;
    return newTree;
}

TreeNode* createTreeNode(int value)
{
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->value = value;
    newNode->leftChild = NULL;
    newNode->rightChild = NULL;
    return newNode;
}

bool isEmpty(BinarySearchTree* tree)
{
    return tree != NULL && tree->root == NULL;
}

bool addValueRecursive(TreeNode* node, int value)
{
    if (node->value == value)
        return false;

    if (node->value > value) {
        if (node->leftChild == NULL) {
            node->leftChild = createTreeNode(value);
            return true;
        }
        return addValueRecursive(node->leftChild, value);
    }

    if (node->value < value) {
        if (node->rightChild == NULL) {
            node->rightChild = createTreeNode(value);
            return true;
        }
        return addValueRecursive(node->rightChild, value);
    }
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

void printTreeInAscendingOrderRecursive(TreeNode* node)
{
    if (node == NULL)
        return;

    printTreeInAscendingOrderRecursive(node->leftChild);
    printf("%d ", node->value);
    printTreeInAscendingOrderRecursive(node->rightChild);
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

void printTreeInDescendingOrderRecursive(TreeNode* node)
{
    if (node == NULL)
        return;

    printTreeInDescendingOrderRecursive(node->rightChild);
    printf("%d ", node->value);
    printTreeInDescendingOrderRecursive(node->leftChild);
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

void printTreeRecursive(TreeNode* node)
{
    if (node == NULL) {
        printf("null");
        return;
    }

    printf("(%d ", node->value);
    printTreeRecursive(node->leftChild);
    printf(" ");
    printTreeRecursive(node->rightChild);
    printf(")");
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

bool isValueInTreeRecursive(TreeNode* node, int value)
{
    if (node == NULL)
        return false;

    if (node->value == value)
        return true;
    if (node->value > value)
        return isValueInTreeRecursive(node->leftChild, value);
    if (node->value < value)
        return isValueInTreeRecursive(node->rightChild, value);
}

bool isValueInTree(BinarySearchTree* tree, int value)
{
    if (tree == NULL || isEmpty(tree))
        return false;
    return isValueInTreeRecursive(tree->root, value);
}

bool isLeaf(TreeNode* node)
{
    return node->leftChild == NULL && node->rightChild == NULL;
}

void changeParent(TreeNode* parentOfNode, TreeNode* node, TreeNode* newChild, BinarySearchTree* tree)
{
    if (parentOfNode == NULL) {
        tree->root = newChild;
        return;
    }
    if (parentOfNode->leftChild == node)
        parentOfNode->leftChild = newChild;
    else
        parentOfNode->rightChild = newChild;
}

bool deleteValueRecursive(TreeNode* node, int value, TreeNode* parent, BinarySearchTree* tree)
{
    if (node == NULL)
        return false;

    if (node->value > value)
        return deleteValueRecursive(node->leftChild, value, node, tree);
    if (node->value < value)
        return deleteValueRecursive(node->rightChild, value, node, tree);

    if (isLeaf(node))
        changeParent(parent, node, NULL, tree);
    else if (node->leftChild == NULL)
        changeParent(parent, node, node->rightChild, tree);
    else if (node->rightChild == NULL)
        changeParent(parent, node, node->leftChild, tree);
    else {
        TreeNode* maximumOfSmallerNodes = node->leftChild;
        TreeNode* maximumOfSmallerNodesParent = node;
        while (maximumOfSmallerNodes->rightChild != NULL) {
            maximumOfSmallerNodesParent = maximumOfSmallerNodes;
            maximumOfSmallerNodes = maximumOfSmallerNodes->rightChild;
        }

        changeParent(maximumOfSmallerNodesParent, maximumOfSmallerNodes, NULL, tree);
        maximumOfSmallerNodes->leftChild = node->leftChild;
        maximumOfSmallerNodes->rightChild = node->rightChild;
        changeParent(parent, node, maximumOfSmallerNodes, tree);
    }

    free(node);
    return true;
}

bool deleteValue(BinarySearchTree* tree, int value)
{
    if (tree == NULL || isEmpty(tree))
        return false;
    return deleteValueRecursive(tree->root, value, NULL, tree);
}

void destroyTreeRecursive(TreeNode* node)
{
    if (node == NULL)
        return;

    destroyTreeRecursive(node->leftChild);
    destroyTreeRecursive(node->rightChild);
    free(node);
}

void destroyTree(BinarySearchTree* tree)
{
    if (tree != NULL) {
        destroyTreeRecursive(tree->root);
        free(tree);
    }
}

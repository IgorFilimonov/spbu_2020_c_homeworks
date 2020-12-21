#include "bst_node.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

TreeNode* createTreeNode(int value)
{
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->value = value;
    newNode->height = 1;
    newNode->leftChild = NULL;
    newNode->rightChild = NULL;
    newNode->amount = 1;
    return newNode;
}

bool addValueRecursive(TreeNode* node, int value)
{
    if (node->value == value) {
        node->amount++;
        return false; // no need to balance
    }

    if (node->value < value) {
        if (node->rightChild == NULL) {
            node->rightChild = createTreeNode(value);
            return true;
        }
        return addValueRecursive(node->rightChild, value);
    }

    if (node->value > value) {
        if (node->leftChild == NULL) {
            node->leftChild = createTreeNode(value);
            return true;
        }
        return addValueRecursive(node->leftChild, value);
    }
}

void printTreeInAscendingOrderRecursive(TreeNode* node)
{
    if (node == NULL)
        return;

    printTreeInAscendingOrderRecursive(node->leftChild);
    printf("%d met %d times\n", node->value, node->amount);
    printTreeInAscendingOrderRecursive(node->rightChild);
}

void printTreeInDescendingOrderRecursive(TreeNode* node)
{
    if (node == NULL)
        return;

    printTreeInDescendingOrderRecursive(node->rightChild);
    printf("%d ", node->value);
    printTreeInDescendingOrderRecursive(node->leftChild);
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

bool isValueInTreeRecursive(TreeNode* node, int value)
{
    if (node == NULL)
        return false;

    if (node->value == value)
        return true;
    if (node->value < value)
        return isValueInTreeRecursive(node->rightChild, value);
    if (node->value > value)
        return isValueInTreeRecursive(node->leftChild, value);
}

bool isLeaf(TreeNode* node);

void changeParent(TreeNode* parentOfNode, TreeNode* node, TreeNode* newChild, TreeNode** newRoot);

bool deleteValueRecursive(TreeNode* node, int value, TreeNode* parent, TreeNode** newRoot, TreeNode** nodeForBalancing)
{
    if (node == NULL)
        return false;

    if (node->value < value)
        return deleteValueRecursive(node->rightChild, value, node, newRoot, nodeForBalancing);
    if (node->value > value)
        return deleteValueRecursive(node->leftChild, value, node, newRoot, nodeForBalancing);

    if (node->amount != 1) {
        node->amount--;
        return false; // no need to balance
    }

    if (node->leftChild != NULL && node->rightChild != NULL) {
        TreeNode* maximumOfSmallerNodes = node->leftChild;
        TreeNode* maximumOfSmallerNodesParent = node;
        while (maximumOfSmallerNodes->rightChild != NULL) {
            maximumOfSmallerNodesParent = maximumOfSmallerNodes;
            maximumOfSmallerNodes = maximumOfSmallerNodes->rightChild;
        }

        changeParent(maximumOfSmallerNodesParent, maximumOfSmallerNodes, maximumOfSmallerNodes->leftChild, newRoot);
        maximumOfSmallerNodes->leftChild = node->leftChild;
        maximumOfSmallerNodes->rightChild = node->rightChild;
        changeParent(parent, node, maximumOfSmallerNodes, newRoot);
        if (nodeForBalancing != NULL) {
            if (maximumOfSmallerNodesParent == node)
                *nodeForBalancing = maximumOfSmallerNodes;
            else
                *nodeForBalancing = maximumOfSmallerNodesParent;
        }
    } else {
        if (isLeaf(node))
            changeParent(parent, node, NULL, newRoot);
        else if (node->leftChild == NULL)
            changeParent(parent, node, node->rightChild, newRoot);
        else
            changeParent(parent, node, node->leftChild, newRoot);
        if (nodeForBalancing != NULL)
            *nodeForBalancing = parent;
    }

    free(node);
    return true;
}

bool isLeaf(TreeNode* node)
{
    return node->leftChild == NULL && node->rightChild == NULL;
}

void changeParent(TreeNode* parentOfNode, TreeNode* node, TreeNode* newChild, TreeNode** newRoot)
{
    if (parentOfNode == NULL) {
        *newRoot = newChild;
        return;
    }
    if (parentOfNode->leftChild == node)
        parentOfNode->leftChild = newChild;
    else
        parentOfNode->rightChild = newChild;
}

void destroyTreeRecursive(TreeNode* node)
{
    if (node == NULL)
        return;

    destroyTreeRecursive(node->leftChild);
    destroyTreeRecursive(node->rightChild);
    free(node);
}

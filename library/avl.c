#include "avl.h"
#include "../library/commonUtils/numericOperations.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int value;
    int height;
    struct TreeNode* leftChild;
    struct TreeNode* rightChild;
} TreeNode;

struct AVLTree {
    TreeNode* root;
};

AVLTree* createTree()
{
    AVLTree* newTree = (AVLTree*)malloc(sizeof(AVLTree));
    newTree->root = NULL;
    return newTree;
}

TreeNode* createTreeNode(int value)
{
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->value = value;
    newNode->height = 1;
    newNode->leftChild = NULL;
    newNode->rightChild = NULL;
    return newNode;
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

bool addValueRecursive(TreeNode* node, int value);

bool addValue(AVLTree* tree, int value)
{
    if (tree == NULL)
        return false;

    if (isEmpty(tree)) {
        tree->root = createTreeNode(value);
        return true;
    }

    bool isAddingValueSuccessful = addValueRecursive(tree->root, value);
    if (isAddingValueSuccessful)
        tree->root = balance(tree->root);
    return isAddingValueSuccessful;
}

bool addValueRecursive(TreeNode* node, int value)
{
    if (node->value == value)
        return false;

    bool isAddingValueSuccessful = false;

    if (node->value < value) {
        if (node->rightChild == NULL) {
            node->rightChild = createTreeNode(value);
            isAddingValueSuccessful = true;
        } else {
            isAddingValueSuccessful = addValueRecursive(node->rightChild, value);
            if (isAddingValueSuccessful)
                node->rightChild = balance(node->rightChild);
        }
    }
    if (node->value > value) {
        if (node->leftChild == NULL) {
            node->leftChild = createTreeNode(value);
            isAddingValueSuccessful = true;
        } else {
            isAddingValueSuccessful = addValueRecursive(node->leftChild, value);
            if (isAddingValueSuccessful)
                node->leftChild = balance(node->leftChild);
        }
    }

    if (isAddingValueSuccessful)
        updateHeight(node);
    return isAddingValueSuccessful;
}

void printTreeInAscendingOrderRecursive(TreeNode* node);

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

void printTreeInAscendingOrderRecursive(TreeNode* node)
{
    if (node == NULL)
        return;

    printTreeInAscendingOrderRecursive(node->leftChild);
    printf("%d ", node->value);
    printTreeInAscendingOrderRecursive(node->rightChild);
}

void printTreeInDescendingOrderRecursive(TreeNode* node);

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

void printTreeInDescendingOrderRecursive(TreeNode* node)
{
    if (node == NULL)
        return;

    printTreeInDescendingOrderRecursive(node->rightChild);
    printf("%d ", node->value);
    printTreeInDescendingOrderRecursive(node->leftChild);
}

void printTreeRecursive(TreeNode* node);

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

bool isValueInTreeRecursive(TreeNode* node, int value);

bool isValueInTree(AVLTree* tree, int value)
{
    if (tree == NULL || isEmpty(tree))
        return false;
    return isValueInTreeRecursive(tree->root, value);
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

bool deleteValueRecursive(TreeNode* node, int value, TreeNode* parent, AVLTree* tree);

bool deleteValue(AVLTree* tree, int value)
{
    if (tree == NULL || isEmpty(tree))
        return false;
    bool isDeletionValueSuccessful = deleteValueRecursive(tree->root, value, NULL, tree);
    if (isDeletionValueSuccessful)
        tree->root = balance(tree->root);
    return isDeletionValueSuccessful;
}

bool isLeaf(TreeNode* node);

void changeParent(TreeNode* parentOfNode, TreeNode* node, TreeNode* newChild, AVLTree* tree);

TreeNode* cutMaximumOfSmallerNodes(TreeNode* node, TreeNode* parent, AVLTree* tree);

bool deleteValueRecursive(TreeNode* node, int value, TreeNode* parent, AVLTree* tree)
{
    if (node == NULL)
        return false;

    if (node->value == value) {
        if (isLeaf(node))
            changeParent(parent, node, NULL, tree);
        else if (node->leftChild == NULL)
            changeParent(parent, node, node->rightChild, tree);
        else if (node->rightChild == NULL)
            changeParent(parent, node, node->leftChild, tree);
        else {
            TreeNode* maximumOfSmallerNodes = cutMaximumOfSmallerNodes(node->leftChild, node, tree);
            maximumOfSmallerNodes->leftChild = node->leftChild;
            maximumOfSmallerNodes->rightChild = node->rightChild;
            updateHeight(maximumOfSmallerNodes);
            changeParent(parent, node, maximumOfSmallerNodes, tree);
        }

        free(node);
        return true;
    }

    bool isValueDeletionSuccessful = false;

    if (node->value < value) {
        isValueDeletionSuccessful = deleteValueRecursive(node->rightChild, value, node, tree);
        if (isValueDeletionSuccessful)
            node->rightChild = balance(node->rightChild);
    }
    if (node->value > value) {
        isValueDeletionSuccessful = deleteValueRecursive(node->leftChild, value, node, tree);
        if (isValueDeletionSuccessful)
            node->leftChild = balance(node->leftChild);
    }

    if (isValueDeletionSuccessful)
        updateHeight(node);
    return isValueDeletionSuccessful;
}

bool isLeaf(TreeNode* node)
{
    return node->leftChild == NULL && node->rightChild == NULL;
}

void changeParent(TreeNode* parentOfNode, TreeNode* node, TreeNode* newChild, AVLTree* tree)
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

TreeNode* cutMaximumOfSmallerNodes(TreeNode* node, TreeNode* parent, AVLTree* tree)
{
    if (node->rightChild == NULL) {
        changeParent(parent, node, node->leftChild, tree);
        return node;
    }

    TreeNode* maximumOfSmallerNodes = cutMaximumOfSmallerNodes(node->rightChild, node, tree);
    node->rightChild = balance(node->rightChild);
    updateHeight(node);
    return maximumOfSmallerNodes;
}

void destroyTreeRecursive(TreeNode* node);

void destroyTree(AVLTree* tree)
{
    if (tree != NULL) {
        destroyTreeRecursive(tree->root);
        free(tree);
    }
}

void destroyTreeRecursive(TreeNode* node)
{
    if (node == NULL)
        return;

    destroyTreeRecursive(node->leftChild);
    destroyTreeRecursive(node->rightChild);
    free(node);
}

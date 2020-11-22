#ifndef IDIOT_BST_NODE_H
#define IDIOT_BST_NODE_H

#include <stdbool.h>

typedef struct TreeNode {
    int value;
    int height;
    struct TreeNode* leftChild;
    struct TreeNode* rightChild;
} TreeNode;

TreeNode* createTreeNode(int value);

bool addValueRecursive(TreeNode* node, int value);

void printTreeInAscendingOrderRecursive(TreeNode* node);

void printTreeInDescendingOrderRecursive(TreeNode* node);

void printTreeRecursive(TreeNode* node);

bool isValueInTreeRecursive(TreeNode* node, int value);

bool deleteValueRecursive(TreeNode* node, int value, TreeNode* parent, TreeNode** newRoot, TreeNode** nodeForBalancing);

void destroyTreeRecursive(TreeNode* node);

#endif //IDIOT_BST_NODE_H

#include "../library/trees/avl.h"
#include <stdio.h>

AVLTree* readNumbers()
{
    AVLTree* avlTree = createTree();

    printf("Enter numbers:\n");

    int number = 0;
    scanf("%d", &number);
    while (number != 0) {
        addValue(avlTree, number);
        scanf("%d", &number);
    }

    return avlTree;
}

int main()
{
    AVLTree* avlTree = readNumbers();

    printTreeInAscendingOrder(avlTree);

    destroyTree(avlTree);
    return 0;
}

#include "../library/list.h"
#include <stdio.h>

List* createWarriors(int n)
{
    List* warriors = createList();
    for (int i = 0; i < n; ++i)
        insert(createListElement(i + 1), i, warriors);
    makeListCyclical(warriors);
    return warriors;
}

ListElement* findLastWarrior(List* warriors, int n, int m)
{
    ListElement* currentWarrior = head(warriors);
    for (int i = 1; i < n; ++i) {
        for (int j = 1; j < m; ++j)
            currentWarrior = getNextElement(currentWarrior);
        ListElement* warriorToBeKilled = currentWarrior;
        currentWarrior = getNextElement(currentWarrior);
        deleteFromList(locate(warriorToBeKilled, warriors), warriors);
    }

    return currentWarrior;
}

int main()
{
    printf("Enter n and m:\n");
    int n = 0, m = 0;
    scanf("%d%d", &n, &m);
    if (n < 1 || m < 1) {
        printf("Invalid input data");
        return 0;
    }

    List* warriors = createWarriors(n);

    printf("The last survivor will be the warrior number ");
    printListElement(findLastWarrior(warriors, n, m));

    removeList(warriors);
    return 0;
}

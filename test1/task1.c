#include "../library/list.h"
#include <stdio.h>

void readInputData(FILE* inputFile, List** list, int* size)
{
    for (*size = 0; !feof(inputFile); ++*size) {
        int value = 0;
        fscanf(inputFile, "%d", &value);
        ListElement* element = createListElement(value);
        insert(element, *size, *list);
    }
}

int main()
{
    FILE* inputFile = fopen("../test1/input.txt", "r");
    if (inputFile == NULL) {
        printf("Couldn't open the file");
        return 0;
    }

    List* list = createList();
    int size = 0;
    readInputData(inputFile, &list, &size);

    ListElement* start = head(list);
    ListElement* end = tail(list);
    bool isSymmetric = true;
    for (int i = 0; i < size / 2; ++i) {
        if (getValue(start) != getValue(end)) {
            isSymmetric = false;
            break;
        }
        start = getNextElement(start);
        end = getPreviousElement(end);
    }

    if (isSymmetric)
        printf("The list is symmetrical");
    else
        printf("The list isn't symmetrical");

    removeList(list);
    fclose(inputFile);
    return 0;
}
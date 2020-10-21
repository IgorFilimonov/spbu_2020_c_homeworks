#include "../library/list.h"
#include <stdio.h>

int main()
{
    List* numbers = createList();
    for (int i = 0; i < 5; ++i) {
        ListElement* number = createListElement(i);
        insert(number, i, numbers);
    }
    printf("List: ");
    printList(numbers);

    printf("Tail: ");
    printListElement(tail(numbers));

    deleteFromList(0, numbers);
    printf("Delete 0: ");
    printList(numbers);

    printf("Head: ");
    printListElement(head(numbers));

    ListElement* number1 = createListElement(5);
    insert(number1, 1, numbers);
    printf("Insert 5 to position 1: ");
    printList(numbers);

    ListElement* number2 = retrieve(3, numbers);
    printf("Element with value 3 is at index %d\n", locate(number2, numbers));

    printf("Element at index 6: ");
    printListElement(retrieve(6, numbers));

    removeList(numbers);
    return 0;
}

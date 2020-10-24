#include "../library/list.h"
#include <stdio.h>

int main()
{
    List* numbers = createList();
    ListElement* number1 = createListElement(1);
    ListElement* number2 = createListElement(2);
    ListElement* number3 = createListElement(3);
    ListElement* number4 = createListElement(4);
    insert(number1, 0, numbers);
    insert(number2, 1, numbers);
    insert(number3, 2, numbers);
    insert(number4, 3, numbers);
    printf("List: ");
    printList(numbers);

    printf("Tail: ");
    printListElement(tail(numbers));

    deleteFromList(0, numbers);
    printf("Delete 1: ");
    printList(numbers);

    printf("Head: ");
    printListElement(head(numbers));

    ListElement* number5 = createListElement(5);
    insert(number5, 1, numbers);
    printf("Insert 5 to position 1: ");
    printList(numbers);

    printf("Element with value 3 is at index %d\n", locate(number3, numbers));
    printf("Element with value 4 is at index %d\n", locate(number4, numbers));
    printf("Element with value 2 is at index %d\n", locate(number2, numbers));

    printf("Element at index 6: ");
    printListElement(retrieve(6, numbers));

    removeList(numbers);
    return 0;
}

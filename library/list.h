#ifndef LIST_LIST_H
#define LIST_LIST_H

#include <stdbool.h>

typedef struct ListElement ListElement;

typedef struct List List;

List* createList();

ListElement* createListElement(int value);

ListElement* head(List* list);

ListElement* tail(List* list);

void printList(List* list);

void removeList(List* list);

ListElement* retrieve(int position, List* list);

bool insert(ListElement* value, int position, List* list);

int locate(ListElement* value, List* list);

bool deleteFromList(int position, List* list);

void printListElement(ListElement* element);

void removeListElement(ListElement* element);

ListElement* getNextElement(ListElement* element);

bool makeListCyclical(List* list);

#endif //LIST_LIST_H

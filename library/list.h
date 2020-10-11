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

void addListElement(List* list, ListElement* element);

void removeList(List* list);

ListElement* retrieve(int position, List* list);

bool insert(ListElement* value, int position, List* list);

int locate(ListElement* value, List* list);

bool delete(List* list, int position);

void printListElement(ListElement* element);

#endif //LIST_LIST_H

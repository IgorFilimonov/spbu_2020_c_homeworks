#include "list.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct ListElement {
    int value;
    ListElement* next;
};

struct List {
    ListElement* head;
    ListElement* tail;
    int size;
};

List* createList()
{
    List* list = (List*)malloc(sizeof(List));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

ListElement* createListElement(int value)
{
    ListElement* element = (ListElement*)malloc(sizeof(ListElement));
    element->value = value;
    element->next = NULL;
    return element;
}

ListElement* head(List* list)
{
    return list->head;
}

ListElement* tail(List* list)
{
    return list->tail;
}

void printList(List* list)
{
    printf("START -> ");
    ListElement* current = head(list);
    while (current != NULL) {
        printf("%d -> ", current->value);
        current = current->next;
    }
    printf("END\n");
}

void addListElement(List* list, ListElement* element)
{
    if (head(list) == NULL) {
        list->head = element;
        list->tail = element;
        return;
    }
    tail(list)->next = element;
    list->tail = element;
    list->size++;
}

void removeList(List* list)
{
    ListElement* current = head(list);
    while (current != NULL) {
        ListElement* copyOfCurrent = current;
        current = current->next;
        removeListElement(copyOfCurrent);
    }
    free(list);
}

ListElement* retrieve(int position, List* list)
{
    if (position < 0 || position > list->size - 1)
        return NULL;

    ListElement* current = head(list);
    for (int i = 0; i < position; ++i)
        current = current->next;
    return current;
}

bool insert(ListElement* value, int position, List* list)
{
    if (position < 0 || position > list->size)
        return false;

    if (position == 0) {
        value->next = head(list);
        if (value->next == NULL)
            list->tail = value;
        list->head = value;
        list->size++;
        return true;
    }

    ListElement* previous = retrieve(position - 1, list);
    value->next = previous->next;
    if (previous == tail(list))
        list->tail = value;
    previous->next = value;
    list->size++;
    return true;
}

int locate(ListElement* value, List* list)
{
    ListElement* current = head(list);
    int position = 0;
    while (current != NULL) {
        if (current == value)
            return position;
        current = current->next;
        ++position;
    }
    return -1; // there is no element with this value
}

bool deleteFromList(int position, List* list)
{
    if (position < 0 || position > list->size - 1 || list->size == 0)
        return false;

    if (position == 0) {
        ListElement* oldHead = head(list);
        list->head = head(list)->next;
        if (head(list) == NULL) // if true, list is empty
            list->tail = NULL;
        removeListElement(oldHead);
        list->size--;
        return true;
    }

    ListElement* previous = retrieve(position - 1, list);
    ListElement* next = retrieve(position + 1, list);
    if (previous->next == tail(list))
        list->tail = previous;
    removeListElement(previous->next);
    previous->next = next;
    list->size--;
    return true;
}

void printListElement(ListElement* element)
{
    if (element == NULL)
        printf("NULL\n");
    else
        printf("%d\n", element->value);
}

void removeListElement(ListElement* element)
{
    free(element);
}

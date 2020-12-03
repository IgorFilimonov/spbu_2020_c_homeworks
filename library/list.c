#include "list.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct ListElement {
    int value;
    ListElement* next;
    ListElement* previous;
};

struct List {
    ListElement* head;
    ListElement* tail;
    int size;
    bool isCyclical;
};

List* createList()
{
    List* list = (List*)malloc(sizeof(List));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    list->isCyclical = false;
    return list;
}

ListElement* createListElement(int value)
{
    ListElement* element = (ListElement*)malloc(sizeof(ListElement));
    element->value = value;
    element->next = NULL;
    element->previous = NULL;
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
    while (current != tail(list)) {
        printf("%d -> ", current->value);
        current = current->next;
    }
    if (tail(list) != NULL)
        printf("%d -> ", tail(list)->value);
    printf("END\n");
}

void removeList(List* list)
{
    ListElement* current = head(list);
    while (current != tail(list)) {
        ListElement* temporary = current;
        current = current->next;
        removeListElement(temporary);
    }
    if (tail(list) != NULL)
        removeListElement(tail(list));
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
        else
            head(list)->previous = value;
        list->head = value;
        list->size++;
        if (list->isCyclical) {
            tail(list)->next = head(list);
            value->previous = tail(list);
        }
        return true;
    }

    ListElement* previous = retrieve(position - 1, list);
    value->next = previous->next;
    value->previous = previous;
    if (previous->next != NULL)
        previous->next->previous = value;
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
    while (current != tail(list)) {
        if (current == value)
            return position;
        current = current->next;
        ++position;
    }
    if (tail(list) == value)
        return position;
    return -1; // there is no element with this value
}

bool deleteFromList(int position, List* list)
{
    if (position < 0 || position > list->size - 1)
        return false;

    if (position == 0) {
        ListElement* oldHead = head(list);
        list->head = head(list)->next;
        if (head(list) == NULL) // if true, list will be empty
            list->tail = NULL;
        removeListElement(oldHead);
        list->size--;
        if (list->isCyclical && tail(list) != NULL) {
            tail(list)->next = head(list);
            head(list)->previous = tail(list);
        } else
            head(list)->previous = NULL;
        return true;
    }

    ListElement* previous = retrieve(position - 1, list);
    ListElement* next = retrieve(position + 1, list);
    if (previous->next == tail(list))
        list->tail = previous;
    removeListElement(previous->next);
    previous->next = next;
    next->previous = previous;
    list->size--;
    if (list->isCyclical) {
        tail(list)->next = head(list);
        head(list)->previous = tail(list);
    }
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

ListElement* getNextElement(ListElement* element)
{
    return element->next;
}

bool makeListCyclical(List* list)
{
    if (list->size == 0)
        return false;
    list->isCyclical = true;
    tail(list)->next = head(list);
    head(list)->previous = tail(list);
    return true;
}

int getValue(ListElement* element)
{
    if (element != NULL)
        return element->value;
}

ListElement* getPreviousElement(ListElement* element)
{
    if (element != NULL)
        return element->previous;
}

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
};

List* createList()
{
    List* list = (List*)malloc(sizeof(List));
    list->head = NULL;
    list->tail = NULL;
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
}

void removeList(List* list)
{
    ListElement* current = head(list);
    while (current != NULL) {
        ListElement* copyOfCurrent = current;
        current = current->next;
        free(copyOfCurrent);
    }
    free(list);
}

ListElement* retrieve(int position, List* list)
{
    ListElement* current = head(list);
    for (int i = 0; i < position && current != NULL; ++i)
        current = current->next;
    return current;
}

bool insert(ListElement* value, int position, List* list)
{
    if (position == 0) {
        value->next = head(list);
        if (value->next == NULL)
            list->tail = value;
        list->head = value;
        return true;
    }

    ListElement* previous = retrieve(position - 1, list);
    if (previous == NULL)
        return false;

    value->next = previous->next;
    if (previous == tail(list))
        list->tail = value;
    previous->next = value;
    return true;
}

int locate(ListElement* value, List* list)
{
    ListElement* current = head(list);
    int position = 0;
    while (current != NULL) {
        if (current->value == value->value)
            return position;
        current = current->next;
        ++position;
    }
    return -1; // there is no element with this value
}

bool delete (int position, List* list)
{
    if (position == 0) {
        if (head(list) == NULL)
            return false;

        ListElement* oldHead = head(list);
        list->head = head(list)->next;
        if (head(list) == NULL) // if true, list is empty
            list->tail = NULL;
        free(oldHead);
        return true;
    }

    ListElement* previous = retrieve(position - 1, list);
    if (previous == NULL || previous->next == NULL)
        return false;

    ListElement* next = retrieve(position + 1, list);
    if (previous->next == tail(list))
        list->tail = previous;
    free(previous->next);
    previous->next = next;
    return true;
}

void printListElement(ListElement* element)
{
    if (element == NULL)
        printf("NULL\n");
    else
        printf("%d\n", element->value);
}
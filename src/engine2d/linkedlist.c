/**
 * <------------------------------------------------------------------>
 * @name    2D Engine
 * @author  Martin Krcma
 * @date    28. 2. 2021
 * <------------------------------------------------------------------>
 * @file    linkedlist.c
 * @brief   Implementation of linkedlist.h
 * <------------------------------------------------------------------>
 */

#include "linkedlist.h"

#include <stdlib.h>

bool LinkedList_init(LinkedList * list) {
    if(list == NULL) return false;

    list->count = 0;
    list->first = NULL;
    list->last = NULL;

    return true;
}


bool LinkedList_insert(LinkedList * list, LinkedList_Element * element) {
    if(list == NULL || element == NULL) return false;

    if(LinkedList_contains(list, element)) return false;

    LinkedList_Element * parent = list->first;
    if(parent == NULL) {
        //insert first element of list
        list->first = element;
    } else {
        //insert next element
        while(parent->next != NULL) {
            parent = parent->next;
        }
        parent->next = element;
    }

    //set end element
    list->last = element;

    list->count++;

    return true;
}


LinkedList_Element * LinkedList_valueAt(LinkedList * list, unsigned int index) {
    if(list == NULL) return NULL;

    unsigned int current_index = 0;
    LinkedList_Element * element = list->first;
    while(element != NULL) {
        //find element in list by index
        if(current_index == index) {
            return element;
        }
        element = element->next;
        current_index++;
    }

    return NULL;
}


LinkedList_Element * LinkedList_next(LinkedList_Element * element) {
    if(element == NULL) return NULL;
    return element->next;
}


bool LinkedList_removeElement(LinkedList * list, LinkedList_Element * element, bool destruct) {
    if(list == NULL || element == NULL) return false;

    LinkedList_Element * last = NULL;
    LinkedList_Element * current = list->first;
    while(element != NULL) {
        //find element in list by index
        if(element == current) {
            //destruct data
            if(destruct && element->destruct) element->destruct(element);
            //reconnect linked list
            if(last == NULL) {
                list->first = element->next;
            } else {
                last->next = element->next;
            }
            //decrease count of elements
            list->count--;
            //chage pointer on last element (if is needed)
            if(element == list->last) list->last = last;
            return true;
        }
        last = element;
        element = element->next;
    }

    return false;
}


bool LinkedList_removeIndex(LinkedList * list, unsigned int index, bool destruct) {
    if(list == NULL) return false;

    unsigned int current_index = 0;
    LinkedList_Element * last = NULL;
    LinkedList_Element * element = list->first;
    while(element != NULL) {
        //find element in list by index
        if(current_index == index) {
            //destruct data
            if(destruct && element->destruct) element->destruct(element);
            //reconnect linked list
            if(last == NULL) {
                list->first = element->next;
            } else {
                last->next = element->next;
            }
            //decrease count of elements
            list->count--;
            //chage pointer on last element (if is needed)
            if(element == list->last) list->last = last;
            return true;
        }
        last = element;
        element = element->next;
        current_index++;
    }

    return false;
}

bool LinkedList_contains(LinkedList * list, LinkedList_Element * element) {
    if(list == NULL || element == NULL) return false;

    LinkedList_Element * current = list->first;
    while(current != NULL) {
        if(element == current) {
            return true;
        }
        current = current->next;
    }

    return false;
}

void LinkedList_clear(LinkedList * list) {
    if(list == NULL) return;

    list->first = NULL;
    list->last = NULL;
    list->count = 0;
}

#include <stdio.h>

void LinkedList_dectruct(LinkedList * list) {
    if(list == NULL) return;

    LinkedList_Element * element = list->first;
    while(element != NULL) {
        if(element->destruct) element->destruct(element);
        element->data = NULL;
        element = element->next;
    }
}

/**
 * <------------------------------------------------------------------>
 * @name    2D Engine
 * @author  Martin Krcma
 * @date    28. 2. 2021
 * <------------------------------------------------------------------>
 * @file    engine_object.c
 * @brief   Implementation of engine_object.h
 * <------------------------------------------------------------------>
 */

#include "engine_object.h"



static void destruct(void * ptr);


bool E_Obj_init(E_Obj * obj) {
    if(obj == NULL) return false;

    obj->data = NULL;
    obj->events = NULL;

    return true;
}

void E_Obj_destruct(E_Obj * obj) {
    if(obj == NULL) return;
    if(obj->events == NULL) return;

    if(obj->events->destruct) obj->events->destruct(obj);
}

bool E_Obj_insertToList(LinkedList * list, E_Obj * obj) {
    if(obj == NULL || list == NULL) return false;

    LinkedList_Element * element = malloc(sizeof(LinkedList_Element));
    element->ptr = obj;
    element->destruct = destruct;

    return LinkedList_insert(list, element);
}

static void destruct(void * data) {
    if(data == NULL) return;
    E_Obj_destruct((E_Obj*) data);
}

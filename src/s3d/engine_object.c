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


#define DEFAULT_DATA_VECTOR_SIZE 10
#define DATA_VECTOR_ALLOC_STEP 10


static void destruct(void * ptr);


bool E_Obj_init(E_Obj * obj) {
    if(obj == NULL) return false;

    obj->data = NULL;
    obj->destruct = NULL;
    obj->mouseButtonEvt = NULL;
    obj->mouseMoveEvt = NULL;
    obj->pressKeyEvt = NULL;
    obj->releaseKeyEvt = NULL;
    obj->render = NULL;
    obj->update = NULL;

    return true;
}

void E_Obj_destruct(E_Obj * obj) {
    if(obj == NULL) return;

    if(obj->destruct && obj->data) obj->destruct(obj->data);
}

bool E_Obj_insertToList(LinkedList * list, E_Obj * obj) {
    if(obj == NULL || list == NULL) return false;

    LinkedList_Element * element = malloc(sizeof(LinkedList_Element));
    element->ptr = obj;
    element->destruct = destruct;

    return LinkedList_insert(list, element);
}

static void destruct(void * ptr) {
    E_Obj * obj = (E_Obj*) ptr;
    obj->destruct(obj->data);
}

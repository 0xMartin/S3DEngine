/**
 * <------------------------------------------------------------------>
 * @name    2D Engine
 * @author  Martin Krcma
 * @date    28. 2. 2021
 * <------------------------------------------------------------------>
 * @file    ai.c
 * @brief   Implementation of ai.h
 * <------------------------------------------------------------------>
 */

#include "checkbox.h"

#include "../util.h"
#include "../event_virtual_functions.h"
#include "colors.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>


CheckBox * CheckBox_create(int x, int y, size_t width, size_t heigth,
                             size_t str_len) {
    if(width <= 0 || heigth <= 0 || str_len <= 0) return NULL;

    CheckBox * cb = malloc(sizeof(CheckBox));
    if(cb == NULL) return NULL;

    return cb;
}

void CheckBox_destruct(CheckBox * cb) {
    if(cb != NULL) {

        cb->events = UI_EVENTS_INIT;
    }
}

E_Obj * CheckBox_createObject(CheckBox * cb) {
    if(cb == NULL) return NULL;

    E_Obj * obj = malloc(sizeof(E_Obj));
    if(obj == NULL) return NULL;
    E_Obj_init(obj);
    obj->data = cb;
    obj->destruct = destruct;
    obj->render = render;

    return obj;
}

static void destruct(void * ptr) {
    CheckBox * cb = (CheckBox*) ptr;
    CheckBox_destruct(cb);
}

static void render(struct _E_Obj * obj, Event_Render * evt) {

}


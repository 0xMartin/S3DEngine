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

#include "radiobutton.h"

#include "../util.h"
#include "../event_virtual_functions.h"
#include "colors.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>


RadioButton * RadioButton_create(int x, int y, size_t width, size_t heigth,
                             size_t str_len) {
    if(width <= 0 || heigth <= 0 || str_len <= 0) return NULL;

    RadioButton * rb = malloc(sizeof(RadioButton));
    if(rb == NULL) return NULL;

    return rb;
}

void RadioButton_destruct(RadioButton * rb) {
    if(rb != NULL) {

        rb->events = UI_EVENTS_INIT;
    }
}

E_Obj * RadioButton_createObject(RadioButton * rb) {
    if(rb == NULL) return NULL;

    E_Obj * obj = malloc(sizeof(E_Obj));
    if(obj == NULL) return NULL;
    E_Obj_init(obj);
    obj->data = rb;
    obj->destruct = destruct;
    obj->render = render;

    return obj;
}

static void destruct(void * ptr) {
    RadioButton * rb = (RadioButton*) ptr;
    RadioButton_destruct(rb);
}

static void render(struct _E_Obj * obj, Event_Render * evt) {

}


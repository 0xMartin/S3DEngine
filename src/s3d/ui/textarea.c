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

#include "textarea.h"

#include "../util.h"
#include "../event_virtual_functions.h"
#include "colors.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>


TextArea * TextArea_create(int x, int y, size_t width, size_t heigth,
                             size_t str_len) {
    if(width <= 0 || heigth <= 0 || str_len <= 0) return NULL;

    TextArea * ta = malloc(sizeof(TextArea));
    if(ta == NULL) return NULL;


    return ta;
}

void TextArea_destruct(TextArea * tf) {
    if(tf != NULL) {
        if(tf->text) free(tf->text);
        tf->text = NULL;
        tf->events = UI_EVENTS_INIT;
    }
}

E_Obj * TextArea_createObject(TextArea * tf) {
    if(tf == NULL) return NULL;

    E_Obj * obj = malloc(sizeof(E_Obj));
    if(obj == NULL) return NULL;
    E_Obj_init(obj);
    obj->data = tf;
    obj->destruct = destruct;
    obj->render = render;
    obj->mouseMoveEvt = mouseMoveEvt;
    obj->mouseButtonEvt = mouseButtonEvt;
    obj->pressKeyEvt = pressKeyEvt;
    obj->releaseKeyEvt = releaseKeyEvt;
    obj->update = update;

    return obj;
}

static void destruct(void * ptr) {
    TextArea * ta = (TextArea*) ptr;
    TextField_destruct(ta);
}

static void render(struct _E_Obj * obj, Event_Render * evt) {

}

static void mouseMoveEvt(struct _E_Obj * obj, Context * cntx, Event_Mouse * evt) {

}

static void mouseButtonEvt(struct _E_Obj * obj, Context * cntx, Event_Mouse * evt) {

}

static void pressKeyEvt(struct _E_Obj * obj, Context * cntx, Event_Key * evt) {

}

static void releaseKeyEvt(struct _E_Obj * obj, Context * cntx, Event_Key * evt) {

}

static void update(struct _E_Obj * obj, Context * cntx, Event_Update * evt) {

}

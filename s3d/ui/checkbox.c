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
#include "colors.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>


/* Object event functions -------------------------------------------------------- */

static void destruct(void * obj) {
    CheckBox * cb = (CheckBox*) obj;
    CheckBox_destruct(cb);
}

static void render(void * obj, const Event_Render * evt) {

}

static const E_Obj_Evts e_obj_evts = {
    .destruct = destruct,
    .render = render,
    .update = NULL,
    .mouseMoveEvt = NULL,
    .mouseButtonEvt = NULL,
    .pressKeyEvt = NULL,
    .releaseKeyEvt = NULL
};

/* Object functions -------------------------------------------------------- */

CheckBox * CheckBox_create(int x, int y, size_t width, size_t heigth,
                             size_t str_len) {
    CheckBox * cb = malloc(sizeof(CheckBox));
    if(cb == NULL) return NULL;

    cb->objEvts = &e_obj_evts;

    return cb;
}

void CheckBox_destruct(CheckBox * cb) {
    if(cb != NULL) {

        cb->events = UI_EVENTS_INIT;
    }
}


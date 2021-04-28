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
#include "colors.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>


/* Object event functions -------------------------------------------------------- */

static void destruct(void * obj) {
    RadioButton * rb = (RadioButton*) obj;
    RadioButton_destruct(rb);
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

RadioButton * RadioButton_create(int x, int y, size_t width, size_t heigth,
                             size_t str_len) {
    RadioButton * rb = malloc(sizeof(RadioButton));
    if(rb == NULL) return NULL;

    rb->objEvts = &e_obj_evts;

    return rb;
}

void RadioButton_destruct(RadioButton * rb) {
    if(rb != NULL) {

        rb->events = UI_EVENTS_INIT;
    }
}


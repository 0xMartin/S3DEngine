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

#include "label.h"

#include "../util.h"
#include "colors.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


/* Object event functions -------------------------------------------------------- */

static void destruct(void * obj) {
    Label * btn = (Label*) obj;
    Label_destruct(btn);
}

static void render(void * obj, const Event_Render * evt) {
    Label * lab = (Label*) obj;

    Render_setColor(&lab->foreground);
    Render_drawString(
                lab->position.x,
                lab->position.y,
                lab->text);
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

Label * Label_create(int x, int y, const char * const txt) {
    if(txt == NULL) return NULL;

    Label * lab = malloc(sizeof(Label));
    if(lab == NULL) return NULL;

    lab->objEvts = &e_obj_evts;

    lab->foreground = UI_LABEL_FG_COLOR;
    lab->events.enabled = true;
    lab->position.x = x;
    lab->position.y = y;
    lab->events = UI_EVENTS_INIT;
    lab->text = malloc(sizeof (char) * (strlen(txt) + 1));
    sprintf(lab->text, "%s", txt);

    return lab;
}

void Label_destruct(Label * lab) {
    if(lab != NULL) {
        if(lab->text) free(lab->text);
        lab->text = NULL;
        lab->events = UI_EVENTS_INIT;
    }
}


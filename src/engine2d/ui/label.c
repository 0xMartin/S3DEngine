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
#include "../event_virtual_functions.h"
#include "colors.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


Label * Label_create(int x, int y, const char * const txt) {
    if(txt == NULL) return NULL;

    Label * lab = malloc(sizeof(Label));
    if(lab == NULL) return NULL;

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

E_Obj * Label_createObject(Label * lab) {
    if(lab == NULL) return NULL;

    E_Obj * obj = malloc(sizeof(E_Obj));
    if(obj == NULL) return NULL;
    E_Obj_init(obj);
    obj->data = lab;
    obj->destruct = destruct;
    obj->render = render;

    return obj;
}

static void destruct(void * ptr) {
    Label * btn = (Label*) ptr;
    Label_destruct(btn);
}

static void render(struct _E_Obj * obj, Event_Render * evt) {
    Label * lab = (Label*) obj->data;

    Render_setColor(&lab->foreground);
    Render_drawString(
                lab->position.x,
                lab->position.y,
                lab->text);
}


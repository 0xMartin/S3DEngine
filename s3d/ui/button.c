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

#include "button.h"

#include "../util.h"
#include "colors.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


/* Object event functions -------------------------------------------------------- */

static void destruct(void * obj) {
    Button * btn = (Button*) obj;
    Button_destruct(btn);
}

static void render(void * obj, const Event_Render * evt) {
    Button * btn = (Button*) obj;
    if(btn->events.hover) {
        Color c = COLOR_DARKER(btn->background);
        Render_setColor(&c);
    } else {
        Render_setColor(&btn->background);
    }
    Render_fillRectangle(&btn->position, btn->width, btn->height);
    Render_setColor(&btn->foreground);
    Render_drawRectangle(&btn->position, btn->width, btn->height);
    Render_drawString(
                btn->position.x + (btn->width - Render_getStringWidth(btn->text))/2,
                btn->position.y + (btn->height + Render_getStringHeight())/2,
                btn->text);
}

static void mouseMoveEvt(void * obj, Context * cntx, const Event_Mouse * evt) {
    Button * btn = (Button*) obj;
    if(!btn->events.enabled) return;

    if(IN_RANGE(evt->x, btn->position.x, btn->position.x + btn->width)) {
        if(IN_RANGE(evt->y, btn->position.y, btn->position.y + btn->height)) {
            btn->events.hover = true;
            if(btn->events.mouseMovedAction) btn->events.mouseMovedAction(btn, evt);
            return;
        }
    }
    btn->events.hover = false;
}

static void mouseButtonEvt(void * obj, Context * cntx, const Event_Mouse * evt) {
    Button * btn = (Button*) obj;
    if(!btn->events.enabled) return;

    btn->events.focus = false;
    if(IN_RANGE(evt->x, btn->position.x, btn->position.x + btn->width)) {
        if(IN_RANGE(evt->y, btn->position.y, btn->position.y + btn->height)) {
            btn->events.focus = true;
            if(evt->state == EVT_M_DOWN) {
                if(btn->events.mousePressAction) btn->events.mousePressAction(btn, evt);
            } else if(evt->state == EVT_M_UP) {
                if(btn->events.mouseReleaseAction) btn->events.mouseReleaseAction(btn, evt);
            }
        }
    }
}

static void pressKeyEvt(void * obj, Context * cntx, const Event_Key * evt) {
    Button * btn = (Button*) obj;
    if(!btn->events.enabled) return;

    if(btn->events.focus) {
        if(btn->events.keyPressedAction) btn->events.keyPressedAction(btn, evt);
    }
}

static void releaseKeyEvt(void * obj, Context * cntx, const Event_Key * evt) {
    Button * btn = (Button*) obj;
    if(!btn->events.enabled) return;

    if(btn->events.focus) {
        if(btn->events.keyPressedAction) btn->events.keyPressedAction(btn, evt);
    }
}

static const E_Obj_Evts e_obj_evts = {
    .destruct = destruct,
    .render = render,
    .update = NULL,
    .mouseMoveEvt = mouseMoveEvt,
    .mouseButtonEvt = mouseButtonEvt,
    .pressKeyEvt = pressKeyEvt,
    .releaseKeyEvt = releaseKeyEvt
};

/* Object functions -------------------------------------------------------- */

Button * Button_create(int x, int y, size_t width, size_t heigth,
                       const char * const txt) {
    if(txt == NULL) return NULL;

    Button * btn = malloc(sizeof(Button));
    if(btn == NULL) return NULL;

    btn->objEvts = &e_obj_evts;

    btn->background = UI_BUTTON_BG_COLOR;
    btn->foreground = UI_BUTTON_FG_COLOR;
    btn->events.enabled = true;
    btn->position.x = x;
    btn->position.y = y;
    btn->width = width;
    btn->height = heigth;
    btn->events = UI_EVENTS_INIT;
    btn->text = malloc(sizeof (char) * (strlen(txt) + 1));
    sprintf(btn->text, "%s", txt);

    return btn;
}

void Button_destruct(Button * btn) {
    if(btn != NULL) {
        if(btn->text) free(btn->text);
        btn->text = NULL;
        btn->events = UI_EVENTS_INIT;
    }
}
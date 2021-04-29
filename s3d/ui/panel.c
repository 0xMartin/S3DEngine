/**
 * <------------------------------------------------------------------>
 * @name    2D Engine
 * @author  Martin Krcma
 * @date    28. 4. 2021
 * <------------------------------------------------------------------>
 * @file    panel.c
 * @brief   Implementation of panel.h
 * <------------------------------------------------------------------>
 */

#include "panel.h"

#include "../util.h"
#include "colors.h"
#include <stdlib.h>


#define MOUSE_POS_THRESHOLD 15


/* Object event functions -------------------------------------------------------- */

static void destruct(void * obj) {
    Panel * btn = (Panel*) obj;
    Panel_destruct(btn);
}

static void render(void * obj, const Event_Render * evt) {
    Panel * pan = (Panel*) obj;

    Event_Render panel_evt;
    panel_evt.window_width = pan->width;
    panel_evt.window_height = pan->height;

    //draw panel
    Render_setColor(&pan->background);
    Render_fillRectangle(&pan->position, pan->width, pan->height);
    Color border_color = COLOR_LIGHTER(pan->background, 0.1);
    Render_setColor(&border_color);
    Render_drawRectangle(&pan->position, pan->width, pan->height);

    //shift origin
    glTranslatef(pan->position.x, pan->position.y, 0);

    //render childs
    Render_setScissor(pan->position.x, pan->position.y + pan->height,
                      pan->width, pan->height, evt);

    E_Obj * child;
    LinkedList_Element * el = pan->childs.first;
    while(el != NULL) {
        if(el->ptr != NULL) {
            child = (E_Obj*) el->ptr;
            if(child->events) {
                if(child->events->render) child->events->render(child, &panel_evt);
            }
        }
        el = LinkedList_next(el);
    }

    Render_resetScissor(evt);

    //shift back origin
    glTranslatef(-pan->position.x, -pan->position.y, 0);
}

static void update(void * obj, Context * cntx, const Event_Update * evt) {
    Panel * pan = (Panel*) obj;

    E_Obj * child;
    LinkedList_Element * el = pan->childs.first;
    while(el != NULL) {
        if(el->ptr != NULL) {
            child = (E_Obj*) el->ptr;
            if(child->events) {
                if(child->events->update) child->events->update(child, cntx, evt);
            }
        }
        el = LinkedList_next(el);
    }
}

static void mouseMoveEvt(void * obj, Context * cntx, const Event_Mouse * evt) {
    Panel * pan = (Panel*) obj;

    if(IN_RANGE(evt->x, pan->position.x - MOUSE_POS_THRESHOLD,
                pan->position.x + pan->width + MOUSE_POS_THRESHOLD)) {
        if(IN_RANGE(evt->y, pan->position.y - MOUSE_POS_THRESHOLD,
                    pan->position.y + pan->height + MOUSE_POS_THRESHOLD)) {

            Event_Mouse panel_evt = *evt;
            panel_evt.x -= pan->position.x;
            panel_evt.y -= pan->position.y;

            E_Obj * child;
            LinkedList_Element * el = pan->childs.first;
            while(el != NULL) {
                if(el->ptr != NULL) {
                    child = (E_Obj*) el->ptr;
                    if(child->events) {
                        if(child->events->mouseMoveEvt) child->events->mouseMoveEvt(child, cntx, &panel_evt);
                    }
                }
                el = LinkedList_next(el);
            }

        }
    }
}

static void mouseButtonEvt(void * obj, Context * cntx, const Event_Mouse * evt) {
    Panel * pan = (Panel*) obj;

    if(IN_RANGE(evt->x, pan->position.x - MOUSE_POS_THRESHOLD,
                pan->position.x + pan->width + MOUSE_POS_THRESHOLD)) {
        if(IN_RANGE(evt->y, pan->position.y - MOUSE_POS_THRESHOLD,
                    pan->position.y + pan->height + MOUSE_POS_THRESHOLD)) {

            Event_Mouse panel_evt = *evt;
            panel_evt.x -= pan->position.x;
            panel_evt.y -= pan->position.y;

            E_Obj * child;
            LinkedList_Element * el = pan->childs.first;
            while(el != NULL) {
                if(el->ptr != NULL) {
                    child = (E_Obj*) el->ptr;
                    if(child->events) {
                        if(child->events->mouseButtonEvt) child->events->mouseButtonEvt(child, cntx, &panel_evt);
                    }
                }
                el = LinkedList_next(el);
            }

        }
    }
}

static void pressKeyEvt(void * obj, Context * cntx, const Event_Key * evt) {
    Panel * pan = (Panel*) obj;

    E_Obj * child;
    LinkedList_Element * el = pan->childs.first;
    while(el != NULL) {
        if(el->ptr != NULL) {
            child = (E_Obj*) el->ptr;
            if(child->events) {
                if(child->events->pressKeyEvt) child->events->pressKeyEvt(child, cntx, evt);
            }
        }
        el = LinkedList_next(el);
    }
}

static void releaseKeyEvt(void * obj, Context * cntx, const Event_Key * evt) {
    Panel * pan = (Panel*) obj;

    E_Obj * child;
    LinkedList_Element * el = pan->childs.first;
    while(el != NULL) {
        if(el->ptr != NULL) {
            child = (E_Obj*) el->ptr;
            if(child->events) {
                if(child->events->releaseKeyEvt) child->events->releaseKeyEvt(child, cntx, evt);
            }
        }
        el = LinkedList_next(el);
    }
}


static const E_Obj_Evts e_obj_evts = {
    .destruct = destruct,
    .render = render,
    .update = update,
    .mouseMoveEvt = mouseMoveEvt,
    .mouseButtonEvt = mouseButtonEvt,
    .pressKeyEvt = pressKeyEvt,
    .releaseKeyEvt = releaseKeyEvt
};

/* Object functions -------------------------------------------------------- */

Panel * Panel_create(int x, int y, size_t width, size_t height) {
    Panel * pan = malloc(sizeof(Panel));
    if(pan == NULL) return NULL;

    pan->objEvts = &e_obj_evts;

    pan->background = UI_PANEL_BG_COLOR;
    pan->position.x = x;
    pan->position.y = y;
    pan->width = width;
    pan->height = height;
    pan->events = UI_EVENTS_INIT;

    LinkedList_init(&pan->childs);

    return pan;
}

void Panel_destruct(Panel * pan) {
    if(pan != NULL) {
        pan->events = UI_EVENTS_INIT;

        LinkedList_dectruct(&pan->childs);
    }
}

bool Panel_insertChild(Panel * pan, E_Obj * obj) {
    if(pan == NULL || obj == NULL) return false;
    return E_Obj_insertToList(&pan->childs, obj);;
}


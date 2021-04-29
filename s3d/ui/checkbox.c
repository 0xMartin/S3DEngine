/**
 * <------------------------------------------------------------------>
 * @name    2D Engine
 * @author  Martin Krcma
 * @date    19. 3. 2021
 * <------------------------------------------------------------------>
 * @file    checkbox.c
 * @brief   Implementation of checkbox.h
 * <------------------------------------------------------------------>
 */

#include "checkbox.h"

#include "../util.h"
#include "colors.h"
#include <stdlib.h>
#include <stdio.h>


/* Object event functions -------------------------------------------------------- */

static void destruct(void * obj) {
    CheckBox * cb = (CheckBox*) obj;
    CheckBox_destruct(cb);
}

static void render(void * obj, const Event_Render * evt) {
    CheckBox * cb = (CheckBox*) obj;

    Render_setColor(&cb->background);
    Render_fillRectangle(&cb->position, cb->size, cb->size);
    Render_setColor(&cb->borderColor);
    Render_drawRectangle(&cb->position, cb->size, cb->size);

    if(cb->value) {
        Render_setColor(&cb->foreground);
        Point2D pts[3];
        pts[0].x = cb->position.x + (int)cb->size / 4;
        pts[0].y = cb->position.y + (int)cb->size / 4;
        pts[1].x = cb->position.x + (int)cb->size / 2;
        pts[1].y = cb->position.y + (int)cb->size * 0.7;
        pts[2].x = cb->position.x + (int)cb->size * 1.2;
        pts[2].y = cb->position.y - (int)cb->size / 6;
        Render_lineWidth(2.5);
        Render_drawLines(pts, 3);
        Render_lineWidth(RENDER_DEFAULT_LINE_WIDTH);
    }

    if(cb->label != NULL) {
        if(cb->label->objEvts->render) {
            int center = cb->size/2 + Render_getStringHeight()/3;
            //shift origin
            glTranslatef(cb->position.x, cb->position.y + center, 0);

            //render
            cb->label->objEvts->render(cb->label, evt);

            //shift origin back
            glTranslatef(-cb->position.x, -cb->position.y - center, 0);
        }
    }
}

static void mouseButtonEvt(void * obj, Context * cntx, const Event_Mouse * evt) {
    CheckBox * cb = (CheckBox*) obj;
    if(!cb->events.enabled) return;

    cb->events.focus = false;
    if(evt->x >= 0 && evt->y >= 0) {
        if(IN_RANGE(evt->x, cb->position.x, cb->position.x + cb->size)) {
            if(IN_RANGE(evt->y, cb->position.y, cb->position.y + cb->size)) {
                cb->events.focus = true;
                if(evt->state == EVT_M_DOWN) {
                    cb->value = !cb->value;
                    if(cb->events.mousePressAction) cb->events.mousePressAction(cb, evt);
                } else if(evt->state == EVT_M_UP) {
                    if(cb->events.mouseReleaseAction) cb->events.mouseReleaseAction(cb, evt);
                }
            }
        }
    }
}

static const E_Obj_Evts e_obj_evts = {
    .destruct = destruct,
    .render = render,
    .update = NULL,
    .mouseMoveEvt = NULL,
    .mouseButtonEvt = mouseButtonEvt,
    .pressKeyEvt = NULL,
    .releaseKeyEvt = NULL
};

/* Object functions -------------------------------------------------------- */

CheckBox * CheckBox_create(int x, int y, size_t size, bool value,
                           const char * const txt) {
    CheckBox * cb = malloc(sizeof(CheckBox));
    if(cb == NULL) return NULL;

    cb->objEvts = &e_obj_evts;
    cb->events = UI_EVENTS_INIT;
    cb->position.x = x;
    cb->position.y = y;
    cb->value = value;
    cb->size = size;
    cb->background = UI_CHECK_BG_COLOR;
    cb->borderColor = UI_CHECK_BORDER_COLOR;
    cb->foreground = UI_CHECK_FG_COLOR;

    if(txt != NULL) {
        if(*txt != 0) {
            cb->label = Label_create(size + 10, 0, txt);
        }
    }

    return cb;
}

void CheckBox_destruct(CheckBox * cb) {
    if(cb != NULL) {
        cb->events = UI_EVENTS_INIT;
        if(cb->label) Label_destruct(cb->label);
    }
}


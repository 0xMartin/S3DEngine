/**
 * <------------------------------------------------------------------>
 * @name    2D Engine
 * @author  Martin Krcma
 * @date    19. 3. 2021
 * <------------------------------------------------------------------>
 * @file    radiobutton.c
 * @brief   Implementation of radiobutton.h
 * <------------------------------------------------------------------>
 */

#include "radiobutton.h"

#include "../util.h"
#include "colors.h"
#include <stdlib.h>


/* Object event functions -------------------------------------------------------- */

static void destruct(void * obj) {
    RadioButton * rb = (RadioButton*) obj;
    RadioButton_destruct(rb);
}

static void render(void * obj, const Event_Render * evt) {
    RadioButton * rb = (RadioButton*) obj;

    Point2D p = rb->position;
    p.x += rb->size/2;
    p.y += rb->size/2;

    Render_setColor(&rb->background);
    //Render_fillRectangle(&rb->position, rb->size, rb->size);
    Render_setColor(&rb->borderColor);
    Render_lineWidth(2);
    Render_drawEllipse(&p, rb->size/2, rb->size/2);
    Render_lineWidth(RENDER_DEFAULT_LINE_WIDTH);

    if(rb->value) {
        Render_setColor(&rb->foreground);
        Render_fillEllipse(&p, rb->size/3, rb->size/3);
    }

    if(rb->label != NULL) {
        if(rb->label->objEvts->render) {
            int center = rb->size/2 + Render_getStringHeight()/3;
            //shift origin
            glTranslatef(rb->position.x, rb->position.y + center, 0);

            //render
            rb->label->objEvts->render(rb->label, evt);

            //shift origin back
            glTranslatef(-rb->position.x, -rb->position.y - center, 0);
        }
    }
}

static void mouseButtonEvt(void * obj, Context * cntx, const Event_Mouse * evt) {
    RadioButton * rb = (RadioButton*) obj;
    if(!rb->events.enabled) return;

    rb->events.focus = false;
    if(evt->x >= 0 && evt->y >= 0) {
        if(IN_RANGE(evt->x, rb->position.x, rb->position.x + rb->size)) {
            if(IN_RANGE(evt->y, rb->position.y, rb->position.y + rb->size)) {
                rb->events.focus = true;
                if(evt->state == EVT_M_DOWN) {
                    rb->value = !rb->value;
                    if(rb->events.mousePressAction) rb->events.mousePressAction(rb, evt);
                } else if(evt->state == EVT_M_UP) {
                    if(rb->events.mouseReleaseAction) rb->events.mouseReleaseAction(rb, evt);
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

RadioButton * RadioButton_create(int x, int y, size_t size, bool value,
                             const char * const txt) {
    RadioButton * rb = malloc(sizeof(RadioButton));
    if(rb == NULL) return NULL;

    rb->objEvts = &e_obj_evts;
    rb->events = UI_EVENTS_INIT;
    rb->position.x = x;
    rb->position.y = y;
    rb->value = value;
    rb->size = size;
    rb->background = UI_CHECK_BG_COLOR;
    rb->borderColor = UI_CHECK_BORDER_COLOR;
    rb->foreground = UI_CHECK_FG_COLOR;

    if(txt != NULL) {
        if(*txt != 0) {
            rb->label = Label_create(size + 10, 0, txt);
        }
    }

    return rb;
}

void RadioButton_destruct(RadioButton * rb) {
    if(rb != NULL) {
        rb->events = UI_EVENTS_INIT;
        if(rb->label) Label_destruct(rb->label);
    }
}


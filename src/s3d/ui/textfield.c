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

#include "textfield.h"

#include "../util.h"
#include "../event_virtual_functions.h"
#include "colors.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>


TextField * TextField_create(int x, int y, size_t width, size_t heigth,
                             size_t str_len) {
    if(width <= 0 || heigth <= 0 || str_len <= 0) return NULL;

    TextField * tf = malloc(sizeof(TextField));
    if(tf == NULL) return NULL;

    tf->background = UI_TEXTFIELD_BG_COLOR;
    tf->foreground = UI_TEXTFIELD_FG_COLOR;
    tf->caret = UI_TEXTFIELD_CARET_COLOR;
    tf->events.enabled = true;
    tf->position.x = x;
    tf->position.y = y;
    tf->width = width;
    tf->height = heigth;
    tf->caret_position = -1;
    tf->events = UI_EVENTS_INIT;
    tf->textLength = str_len;
    tf->text = calloc(str_len + 1, sizeof (char));

    return tf;
}

void TextField_destruct(TextField * tf) {
    if(tf != NULL) {
        if(tf->text) free(tf->text);
        tf->text = NULL;
        tf->events = UI_EVENTS_INIT;
    }
}

E_Obj * TextField_createObject(TextField * tf) {
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
    TextField * tf = (TextField*) ptr;
    TextField_destruct(tf);
}

static void render(struct _E_Obj * obj, Event_Render * evt) {
    TextField * tf = (TextField*) obj->data;
    if(tf->events.hover) {
        Color c = COLOR_DARKER(tf->background);
        Render_setColor(&c);
    } else {
        Render_setColor(&tf->background);
    }
    Render_fillRectangle(&tf->position, tf->width, tf->height);
    Render_setColor(&tf->foreground);
    Render_drawRectangle(&tf->position, tf->width, tf->height);
    float center = (tf->height + Render_getStringHeight(tf->text))/2;

    Render_drawString(tf->position.x + 5,
                      tf->position.y + center,
                      tf->text);

    if(tf->events.focus) {
        if(tf->caret_time % 2 == 0) {
            Point2D p1, p2;
            p1.x = tf->position.x + 5 + Render_getStringWidthIndex(tf->text, tf->caret_position) + 2;
            p2.x = p1.x;
            p1.y = tf->position.y + center;
            p2.y = tf->position.y + center - Render_getStringHeight();
            Render_setColor(&tf->caret);
            Render_drawLine(&p1, &p2);
        }
    }
}

static void mouseMoveEvt(struct _E_Obj * obj, Context * cntx, Event_Mouse * evt) {
    TextField * tf = (TextField*) obj->data;
    if(!tf->events.enabled) return;

    if(IN_RANGE(evt->x, tf->position.x, tf->position.x + tf->width)) {
        if(IN_RANGE(evt->y, tf->position.y, tf->position.y + tf->height)) {
            tf->events.hover = true;
            if(tf->events.mouseMovedAction) tf->events.mouseMovedAction(tf, evt);
            return;
        }
    }
    tf->events.hover = false;
}

static void mouseButtonEvt(struct _E_Obj * obj, Context * cntx, Event_Mouse * evt) {
    TextField * tf = (TextField*) obj->data;
    if(!tf->events.enabled) return;

    tf->events.focus = false;
    if(IN_RANGE(evt->x, tf->position.x, tf->position.x + tf->width)) {
        if(IN_RANGE(evt->y, tf->position.y, tf->position.y + tf->height)) {
            tf->events.focus = true;
            if(evt->state == EVT_M_DOWN) {
                if(tf->events.mousePressAction) tf->events.mousePressAction(tf, evt);
            } else if(evt->state == EVT_M_UP) {
                if(tf->events.mouseReleaseAction) tf->events.mouseReleaseAction(tf, evt);
            }

            int min = 999;
            int v;
            int index = 0;
            for(int i = 0; i <= tf->textLength; ++i) {
                v = tf->position.x + 5 + Render_getStringWidthIndex(tf->text, i) + 2;
                v = abs(v - evt->x);
                if(v < min) {
                    min = v;
                    index = i;
                }
            }
            tf->caret_position = index;
        }
    }
}

static void pressKeyEvt(struct _E_Obj * obj, Context * cntx, Event_Key * evt) {
    TextField * tf = (TextField*) obj->data;
    if(!tf->events.enabled) return;

    if(tf->events.focus) {
        if(tf->events.keyPressedAction) tf->events.keyPressedAction(tf, evt);

        if(isprint(evt->key)) {
            if(strlen(tf->text) + 1 <= (unsigned long)tf->textLength) {
                for(int i = strlen(tf->text); i > tf->caret_position; --i) {
                    tf->text[i] = tf->text[i - 1];
                }
                tf->text[tf->caret_position] = evt->key;
                tf->caret_position++;
            }
        } else {
            printf("%d\n", evt->key);
            switch(evt->key) {
            case EVT_C_BACKSPACE:
                if(tf->caret_position > 0) {
                    for(unsigned long i = tf->caret_position - 1; i < strlen(tf->text); ++i) {
                        tf->text[i] = tf->text[i + 1];
                    }
                    tf->caret_position--;
                }
                break;
            }
            switch(evt->arrow) {
            case LEFT:
                if(tf->caret_position > 0) {
                    tf->caret_position--;
                }
                break;
            case RIGHT:
                if((unsigned long)tf->caret_position < strlen(tf->text)) {
                    tf->caret_position++;
                }
                break;
            }
        }
    }
}

static void releaseKeyEvt(struct _E_Obj * obj, Context * cntx, Event_Key * evt) {
    TextField * tf = (TextField*) obj->data;
    if(!tf->events.enabled) return;

    if(tf->events.focus) {
        if(tf->events.keyPressedAction) tf->events.keyPressedAction(tf, evt);
    }
}

static void update(struct _E_Obj * obj, Context * cntx, Event_Update * evt) {
    TextField * tf = (TextField*) obj->data;

    tf->caret_time = evt->ns_time/4e8;
}

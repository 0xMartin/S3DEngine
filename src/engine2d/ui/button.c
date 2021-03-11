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

#include "../object_virtual_functions.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define UI_BG_COLOR (Color){0.15, 0.15, 0.15, 1.0}
#define UI_FG_COLOR (Color){0.85, 0.85, 0.85, 1.0}


E2_Button * E2_Button_create(int x, int y, size_t width, size_t heigth,
                           const char * const txt, Event_action action) {
    if(txt == NULL || action == NULL || width <= 0 || heigth <= 0) return NULL;

    E2_Button * btn = malloc(sizeof(E2_Button));
    if(btn == NULL) return NULL;

    btn->background = UI_BG_COLOR;
    btn->foreground = UI_FG_COLOR;
    btn->position.x = x;
    btn->position.y = y;
    btn->width = width;
    btn->height = heigth;
    btn->clickAction = *action;
    btn->text = malloc(sizeof (char) * (strlen(txt) + 1));
    sprintf(btn->text, "%s", txt);

    return btn;
}

void E2_Button_destruct(E2_Button * btn) {
    if(btn != NULL) {
        free(btn->text);
        btn->text = NULL;
        btn->clickAction = NULL;
    }
}

E_Obj * E2_Button_createObject(E2_Button * btn) {
    if(btn == NULL) return NULL;

    E_Obj * obj = malloc(sizeof(E_Obj));
    if(obj == NULL) return NULL;
    E_Obj_init(obj);
    obj->data = btn;
    obj->destruct = destruct;
    obj->render = render;

    return obj;
}

void destruct(void * ptr) {
    E2_Button * btn = (E2_Button*) ptr;
    E2_Button_destruct(btn);
}

void render(struct _E_Obj * obj, Event_Render * evt) {
    E2_Button * btn = (E2_Button*) obj->data;
    Render_setColor(&btn->background);
    Render_fillRectangle(&btn->position, btn->width, btn->height);
    Render_setColor(&btn->foreground);
    Render_drawRectangle(&btn->position, btn->width, btn->height);
    Render_drawString(btn->position.x + 8, btn->position.y + btn->height - 10, btn->text);
}

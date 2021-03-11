/**
 * <------------------------------------------------------------------>
 * @name    2D Engine
 * @author  Martin Krcma
 * @date    11. 3. 2021
 * <------------------------------------------------------------------>
 * @file    button.h
 * @brief
 * <------------------------------------------------------------------>
 */

#ifndef BUTTON_H
#define BUTTON_H

#include "../event.h"
#include "../render.h"
#include "../engine_object.h"
#include <stdbool.h>



typedef struct {
    Point2D position;
    bool enabled;
    size_t width;
    size_t height;
    Color background;
    Color foreground;
    Event_action clickAction;
    char * text;
} E2_Button;


/**
 * @brief E2_Button_create
 * @param x
 * @param y
 * @param width
 * @param heigth
 * @param txt
 * @param action
 * @return
 */
E2_Button * E2_Button_create(int x, int y, size_t width, size_t heigth,
                             const char * const txt, Event_action action);

/**
 * @brief E2_Button_destruct
 * @param btn
 */
void E2_Button_destruct(E2_Button * btn);

/**
 * @brief E2_Button_createObject
 * @param btn
 * @return
 */
E_Obj * E2_Button_createObject(E2_Button * btn);

#endif // BUTTON_H

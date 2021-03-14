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
    size_t width;
    size_t height;
    Color background;
    Color foreground;
    UI_Events events;
    char * text;
} Button;


/**
 * @brief Button_create
 * @param x
 * @param y
 * @param width
 * @param heigth
 * @param txt
 * @return
 */
Button * Button_create(int x, int y, size_t width, size_t heigth,
                       const char * const txt);

/**
 * @brief Button_destruct
 * @param btn
 */
void Button_destruct(Button * btn);

/**
 * @brief Button_createObject
 * @param btn
 * @return
 */
E_Obj * Button_createObject(Button * btn);

#endif // BUTTON_H

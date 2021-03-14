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

#ifndef TEXTFIELD_H
#define TEXTFIELD_H

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
    Color caret;
    int caret_position;
    int caret_time;
    UI_Events events;
    int textLength;
    char * text;
} TextField;


/**
 * @brief TextField_create
 * @param x
 * @param y
 * @param width
 * @param heigth
 * @param str_len
 * @return
 */
TextField * TextField_create(int x, int y, size_t width, size_t heigth, size_t str_len);

/**
 * @brief Button_destruct
 * @param btn
 */
void TextField_destruct(TextField * btn);

/**
 * @brief Button_createObject
 * @param btn
 * @return
 */
E_Obj * TextField_createObject(TextField * btn);

#endif // BUTTON_H

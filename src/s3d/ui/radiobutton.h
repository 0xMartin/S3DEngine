/**
 * <------------------------------------------------------------------>
 * @name    2D Engine
 * @author  Martin Krcma
 * @date    19. 3. 2021
 * <------------------------------------------------------------------>
 * @file    radiobutton.h
 * @brief
 * <------------------------------------------------------------------>
 */

#ifndef RADIOBUTTON_H
#define RADIOBUTTON_H

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
} RadioButton;


/**
 * @brief TextField_create
 * @param x
 * @param y
 * @param width
 * @param heigth
 * @param str_len
 * @return
 */
RadioButton * RadioButton_create(int x, int y, size_t width, size_t heigth, size_t str_len);

/**
 * @brief TextField_destruct
 * @param btn
 */
void RadioButton_destruct(RadioButton * btn);

/**
 * @brief Button_createObject
 * @param btn
 * @return
 */
E_Obj * RadioButton_createObject(RadioButton * btn);

#endif // BUTTON_H

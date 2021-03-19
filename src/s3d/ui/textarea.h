/**
 * <------------------------------------------------------------------>
 * @name    2D Engine
 * @author  Martin Krcma
 * @date    19. 3. 2021
 * <------------------------------------------------------------------>
 * @file    textarea.h
 * @brief
 * <------------------------------------------------------------------>
 */

#ifndef TEXTAREA_H
#define TEXTAREA_H

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
} TextArea;


/**
 * @brief TextArea_create
 * @param x
 * @param y
 * @param width
 * @param heigth
 * @param str_len
 * @return
 */
TextArea * TextArea_create(int x, int y, size_t width, size_t heigth, size_t str_len);

/**
 * @brief TextArea_destruct
 * @param btn
 */
void TextArea_destruct(TextArea * btn);

/**
 * @brief TextArea_createObject
 * @param btn
 * @return
 */
E_Obj * TextArea_createObject(TextArea * btn);

#endif // BUTTON_H
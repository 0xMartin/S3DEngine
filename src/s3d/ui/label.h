/**
 * <------------------------------------------------------------------>
 * @name    2D Engine
 * @author  Martin Krcma
 * @date    11. 3. 2021
 * <------------------------------------------------------------------>
 * @file    label.h
 * @brief
 * <------------------------------------------------------------------>
 */

#ifndef LABEL_H
#define LABEL_H

#include "../event.h"
#include "../render.h"
#include "../engine_object.h"
#include <stdbool.h>


typedef struct {
    //[engine object event]
    const E_Obj_Evts * objEvts;

    //[data]

    //UI object events
    UI_Events events;

    //UI obj data
    Point2D position;
    Color foreground;
    char * text;
} Label;


/**
 * @brief Button_create
 * @param x
 * @param y
 * @param width
 * @param heigth
 * @param txt
 * @return
 */
Label * Label_create(int x, int y, const char * const txt);

/**
 * @brief Button_destruct
 * @param btn
 */
void Label_destruct(Label * lab);

#endif // BUTTON_H

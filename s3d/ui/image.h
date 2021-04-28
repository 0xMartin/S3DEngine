/**
 * <------------------------------------------------------------------>
 * @name    2D Engine
 * @author  Martin Krcma
 * @date    19. 3. 2021
 * <------------------------------------------------------------------>
 * @file    checkbox.h
 * @brief
 * <------------------------------------------------------------------>
 */

#ifndef CHECKBOX_H
#define CHECKBOX_H

#include "../event.h"
#include "../render.h"
#include "../engine_object.h"
#include <stdbool.h>


/**
  * if you assigned this value to the width or height of the image then this dimension assign to the second dimension
  */
#define IMAGE_SIZE_AUTO 0


typedef struct {
    //[engine object event]
    const E_Obj_Evts * objEvts;

    //[data]

    //UI object events
    UI_Events events;

    //UI obj data
    Point2D position;
    size_t width;
    size_t height;
    Texture * texture;
} Image;


/**
 * @brief Image_create
 * @param x
 * @param y
 * @param width
 * @param heigth
 * @param texture
 * @return
 */
Image * Image_create(int x, int y, size_t width, size_t heigth, Texture * texture);

/**
 * @brief Image_destruct
 * @param btn
 */
void Image_destruct(Image * btn);

#endif // BUTTON_H

/******************************************************************************
 * S3D Engine
 *
 * @file       image.h
 * @brief      XXXX Function
 *
 * @author     Martin Krcma
 * @date       2021/07/20
 *****************************************************************************/

#ifndef IMAGE_H
#define IMAGE_H


#include "ui_obj.h"
#include "../graphics2d.h"

/**
  * if you assigned this value to the width or height of the image
  * then this dimension assign to the second dimension
  */
#define IMAGE_SIZE_AUTO 0


class Image : public UI_obj
{
protected:
    Texture * texture;
public:
    Image(int x, int y, size_t width, size_t heigth, Texture * texture);

    virtual void render(Graphics * graphics, const Event_Render * evt);

};


#endif // IMAGE_H

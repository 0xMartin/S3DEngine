/******************************************************************************
 * S3D Engine
 *
 * @file       image.cpp
 * @brief      XXXX Function
 *
 * @author     Martin Krcma
 * @date       2021/07/20
 *****************************************************************************/

#include "image.h"

Image::Image(int x, int y, size_t width, size_t heigth, Texture * texture) {
    Image::events = UI_EVENTS_INIT;
    Image::position.x = x;
    Image::position.y = y;
    Image::width = width;
    Image::height = heigth;
    Image::texture = texture;
}

void Image::render(Graphics * graphics, const Event_Render * evt) {
    if(!Image::events.visible) return;

    Graphics2D * g2 = (Graphics2D*)graphics;

    if(Image::width == IMAGE_SIZE_AUTO && Image::height == IMAGE_SIZE_AUTO) {
        //default size of texture
        g2->drawImage(&(Image::position), Image::texture, true);
    } else {
        Point bounds[4];
        bounds[0] = Image::position;
        bounds[1] = Image::position;
        bounds[2] = Image::position;
        bounds[3] = Image::position;
        if(Image::width != IMAGE_SIZE_AUTO && Image::height != IMAGE_SIZE_AUTO) {
            bounds[0].y += Image::height;
            bounds[2].x += Image::width;
            bounds[3].x += Image::width;
            bounds[3].y += Image::height;
        } else if(Image::width != IMAGE_SIZE_AUTO) {
            //auto height
            int height = ((float)Image::width / Image::texture->width) * Image::texture->height;
            bounds[0].y += height;
            bounds[2].x += Image::width;
            bounds[3].x += Image::width;
            bounds[3].y += height;
        } else if(Image::height != IMAGE_SIZE_AUTO) {
            //auto width
            int width = ((float)Image::height / Image::texture->height) * Image::texture->width;
            bounds[0].y += Image::height;
            bounds[2].x += width;
            bounds[3].x += width;
            bounds[3].y += Image::height;
        }
        g2->drawImage(bounds, Image::texture, false);
    }
}

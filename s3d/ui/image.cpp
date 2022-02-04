/***************************************************************************
 *
 *  File:       image.cpp
 *  Date:       20.07.2021
 *
 *  Github:     https://github.com/0xMartin
 *  Email:      martin.krcma1@gmail.com
 *
 *  Copyright (C) 2022 Martin Krcma
 *
 *  Permission is hereby granted, free of charge, to any person
 *  obtaining a copy of this software and associated documentation
 *  files (the "Software"), to deal in the Software without
 *  restriction, including without limitation the rights to use,
 *  copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following
 *  conditions:
 *
 *  The above copyright notice and this permission notice shall be
 *  included in all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 *  OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 *  HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 *  WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 *  OTHER DEALINGS IN THE SOFTWARE.
 *
 ***************************************************************************/

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
            int height = ((float)Image::width / Image::texture->getWidth()) * Image::texture->getHeight();
            bounds[0].y += height;
            bounds[2].x += Image::width;
            bounds[3].x += Image::width;
            bounds[3].y += height;
        } else if(Image::height != IMAGE_SIZE_AUTO) {
            //auto width
            int width = ((float)Image::height / Image::texture->getHeight()) * Image::texture->getHeight();
            bounds[0].y += Image::height;
            bounds[2].x += width;
            bounds[3].x += width;
            bounds[3].y += Image::height;
        }
        g2->drawImage(bounds, Image::texture, false);
    }
}

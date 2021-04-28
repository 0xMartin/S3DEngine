/**
 * <------------------------------------------------------------------>
 * @name    2D Engine
 * @author  Martin Krcma
 * @date    28. 2. 2021
 * <------------------------------------------------------------------>
 * @file    ai.c
 * @brief   Implementation of ai.h
 * <------------------------------------------------------------------>
 */

#include "image.h"

#include "../util.h"
#include "colors.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>


/* Object event functions -------------------------------------------------------- */

static void destruct(void * obj) {
    Image * img = (Image*) obj;
    Image_destruct(img);
}

static void render(void * obj, const Event_Render * evt) {
    Image * img = (Image*) obj;

    if(img->width == IMAGE_SIZE_AUTO && img->height == IMAGE_SIZE_AUTO) {
        //default size of texture
        Render_drawImage(&img->position, img->texture, true);
    } else {
        Point2D bounds[4];
        bounds[0] = img->position;
        bounds[1] = img->position;
        bounds[2] = img->position;
        bounds[3] = img->position;
        if(img->width != IMAGE_SIZE_AUTO && img->height != IMAGE_SIZE_AUTO) {
            bounds[0].y += img->height;
            bounds[2].x += img->width;
            bounds[3].x += img->width;
            bounds[3].y += img->height;
        } else if(img->width != IMAGE_SIZE_AUTO) {
            //auto height
            int height = ((float)img->width / img->texture->width) * img->texture->height;
            bounds[0].y += height;
            bounds[2].x += img->width;
            bounds[3].x += img->width;
            bounds[3].y += height;
        } else if(img->height != IMAGE_SIZE_AUTO) {
            //auto width
            int width = ((float)img->height / img->texture->height) * img->texture->width;
            bounds[0].y += img->height;
            bounds[2].x += width;
            bounds[3].x += width;
            bounds[3].y += img->height;
        }
        Render_drawImage(bounds, img->texture, false);
    }
}

static const E_Obj_Evts e_obj_evts = {
    .destruct = destruct,
    .render = render,
    .update = NULL,
    .mouseMoveEvt = NULL,
    .mouseButtonEvt = NULL,
    .pressKeyEvt = NULL,
    .releaseKeyEvt = NULL
};

/* Object functions -------------------------------------------------------- */

Image * Image_create(int x, int y, size_t width, size_t heigth, Texture * texture) {
    Image * img = malloc(sizeof(Image));
    if(img == NULL) return NULL;

    img->objEvts = &e_obj_evts;

    img->position.x = x;
    img->position.y = y;
    img->width = width;
    img->height = heigth;
    img->texture = texture;

    return img;
}

void Image_destruct(Image * img) {
    if(img != NULL) {
        img->events = UI_EVENTS_INIT;
    }
}


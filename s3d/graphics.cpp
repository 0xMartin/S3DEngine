/******************************************************************************
 * S3D Engine
 *
 * @file       graphics.cpp
 * @brief      XXXX Function
 *
 * @author     Martin Krcma
 * @date       2021/07/20
 *****************************************************************************/

#include "graphics.h"

#include <string.h>
#include <iostream>

Graphics::Graphics(int windowHandle){
    if(windowHandle < 1) {
        std::cerr << __FUNCTION__ << ": failed to create graphics, WindowHandle is incorrect\n";
        return;
    }
    Graphics::windowHandle = windowHandle;
    Graphics::color = COLOR_WHITE;
    Graphics::maxAlpha = 1.0;
    Graphics::scale_x = 1.0;
    Graphics::scale_y = 1.0;
    Graphics::scale_z = 1.0;
    Graphics::offset_x = 0.0;
    Graphics::offset_y = 0.0;
    Graphics::offset_z = 0.0;
    Graphics::font = S3D_BITMAP_HELVETICA_18;
}

void Graphics::begin(Event_Render * evt, Color * color) {
    if(evt != NULL) {
        Graphics::currentRenderEvt = *evt;
    }
    if(Graphics::windowHandle >= 1) {
        //set window
        if(glutGetWindow() != Graphics::windowHandle) {
            glutSetWindow(Graphics::windowHandle);
        }

        //reset modelview matrix.
        glLoadIdentity();

        //clear renderer
        Graphics::clear(evt, color);
    }
}

void Graphics::scale(GLfloat x, GLfloat y, GLfloat z) {
    if(x > 0.0 && y > 0.0) {
        if(Graphics::scale_x != 1.0 || Graphics::scale_y != 1.0) {
            glScalef(1.0 / Graphics::scale_x, 1.0 / Graphics::scale_y, 1.0);
        }
        Graphics::scale_x = x;
        Graphics::scale_y = y;
        Graphics::scale_z = z;
        glScalef(x, y, z);
    }
}

void Graphics::lineWidth(GLfloat width) {
    if(width > 0.0) {
        glLineWidth(width);
    }
}

void Graphics::setMaxAlpha(GLfloat alpha) {
    if(IN_RANGE(alpha, 0.0, 1.0)) {
        Graphics::maxAlpha = alpha;
    }
}

int Graphics::getStringWidth(const char * str) {
    if(str == NULL) return 0;
    if(Graphics::font == NULL) return 0;

    return glutBitmapLength(Graphics::font, (const unsigned char *) str);
}

int Graphics::getStringWidthIndex(const char * str, int lastCharIndex) {
    if(str == NULL) return 0;
    if(Graphics::font == NULL) return 0;
    if(lastCharIndex < 0) return 0;

    int length = 0;
    int len = strlen(str);
    for(int index = 0; index < lastCharIndex && index < len && index >= 0; ++index) {
        length += glutBitmapWidth(Graphics::font, *(str + index));
    }

    return length;
}

int Graphics::getStringWidthRange(const char * str, int start, int end) {
    if(str == NULL) return 0;
    if(Graphics::font == NULL) return 0;
    if(start > end) return 0;

    int length = 0;
    int len = strlen(str);
    for(int index = start; index < end && index < len && index >= 0; ++index) {
        length += glutBitmapWidth(Graphics::font, *(str + index));
    }

    return length;
}

int Graphics::getStringHeight() {
    if(Graphics::font == NULL) return 0;

    if(Graphics::font == S3D_STROKE_ROMAN) {
        return 10;
    } else if(Graphics::font == S3D_STROKE_MONO_ROMAN) {
        return 10;
    } else if(Graphics::font == S3D_BITMAP_9_BY_15) {
        return 15;
    } else if(Graphics::font == S3D_BITMAP_8_BY_13) {
        return 13;
    } else if(Graphics::font == S3D_BITMAP_TIMES_ROMAN_10) {
        return 10;
    } else if(Graphics::font == S3D_BITMAP_TIMES_ROMAN_24) {
        return 24;
    } else if(Graphics::font == S3D_BITMAP_HELVETICA_10) {
        return 10;
    } else if(Graphics::font == S3D_BITMAP_HELVETICA_12) {
        return 12;
    } else if(Graphics::font == S3D_BITMAP_HELVETICA_18) {
        return 18;
    }

    return 0;
}

void Graphics::setColorRGB(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) {
    if(IN_RANGE(red, 0.0, 1.0) && IN_RANGE(green, 0.0, 1.0)
            && IN_RANGE(blue, 0.0, 1.0) && IN_RANGE(alpha, 0.0, 1.0)) {
        Graphics::color.red = red;
        Graphics::color.green = green;
        Graphics::color.blue = blue;
        Graphics::color.alpha = alpha;
        glColor4f(Graphics::color.red, Graphics::color.green, Graphics::color.blue,
                  MIN(Graphics::color.alpha, Graphics::maxAlpha));
    }
}

void Graphics::setColor(Color * color) {
    if(color != NULL) {
        if(IN_RANGE(color->red, 0.0, 1.0) &&
                IN_RANGE(color->green, 0.0, 1.0) &&
                IN_RANGE(color->blue, 0.0, 1.0) &&
                IN_RANGE(color->alpha, 0.0, 1.0)) {
            Graphics::color = *color;
            glColor4f(Graphics::color.red, Graphics::color.green, Graphics::color.blue,
                      MIN(Graphics::color.alpha, Graphics::maxAlpha));
        }
    }
}

void Graphics::setAlpha(GLfloat alpha) {
    if(IN_RANGE(alpha, 0.0, 1.0)) {
        Graphics::color.alpha = alpha;
        glColor4f(Graphics::color.red, Graphics::color.green, Graphics::color.blue,
                  MIN(Graphics::color.alpha, Graphics::maxAlpha));
    }
}

void Graphics::applyOffset(GLfloat x, GLfloat y, GLfloat z) {
    if(x != 0.0 || y != 0.0 || z != 0.0) {
        Graphics::offset_x += x;
        Graphics::offset_y += y;
        Graphics::offset_z += z;
        glTranslatef(x, y, z);
    }
}

void Graphics::clearOffset() {
    if(Graphics::offset_x != 0.0 || Graphics::offset_y != 0.0 || Graphics::offset_z != 0.0) {
        glTranslatef(-Graphics::offset_x, -Graphics::offset_y, -Graphics::offset_z);
        Graphics::offset_x = 0.0;
        Graphics::offset_y = 0.0;
        Graphics::offset_z = 0.0;
    }
}

void Graphics::setScissor(GLfloat x, GLfloat y, GLfloat width,
                          GLfloat height, const Event_Render * evt) {
    if(width > 0 && height > 0 && evt->window_width > 0 && evt->window_height > 0) {
        int x_s = Graphics::offset_x + x;
        int y_s = evt->window_height - y - Graphics::offset_y;
        glScissor(x_s, y_s,
                  MIN(width, evt->window_width - x_s),
                  MIN(height, evt->window_height - y_s));
    }
}

void Graphics::resetScissor(const Event_Render * evt) {
    if(evt->window_width > 0 && evt->window_height > 0) {
        glScissor(Graphics::offset_x, Graphics::offset_y,
                  evt->window_width, evt->window_height);
    }
}

void Graphics::clear(Event_Render * evt, Color * color) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if(color != NULL) {
        glClearColor(color->red, color->green, color->blue, 1.0);
    }

    if(evt != NULL) {
        Graphics::resetScissor(evt);
    }

    Graphics::maxAlpha = 1.0;
    Graphics::color.red = Graphics::color.green = Graphics::color.blue = 1.0;
    Graphics::font = S3D_BITMAP_HELVETICA_18;
    glLineWidth(1.0);

    Graphics::clearOffset();

    if(Graphics::scale_x != 1.0 || Graphics::scale_y != 1.0) {
        glScalef(1.0 / scale_x, 1.0 / Graphics::scale_y, 1.0);
        Graphics::scale_x = 1.0;
        Graphics::scale_y = 1.0;
    }
}

void Graphics::render() {
    glutSwapBuffers();
}

void Graphics::setFont(void * font, GLint size) {
    if(font != NULL && size > 5) {
        if(font == S3D_STROKE_ROMAN ||
                font == S3D_STROKE_MONO_ROMAN ||
                font == S3D_BITMAP_9_BY_15 ||
                font == S3D_BITMAP_8_BY_13 ||
                font == S3D_BITMAP_TIMES_ROMAN_10 ||
                font == S3D_BITMAP_TIMES_ROMAN_24 ||
                font == S3D_BITMAP_HELVETICA_10 ||
                font == S3D_BITMAP_HELVETICA_12 ||
                font == S3D_BITMAP_HELVETICA_18) {
            Graphics::font = font;
        }
    }
}

void Graphics::drawString(GLfloat x, GLfloat y, const char * const str) {
    if(str != NULL) {
        if(strlen(str) > 0) {
            glColor4f(Graphics::color.red, Graphics::color.green, Graphics::color.blue,
                      MIN(Graphics::color.alpha, Graphics::maxAlpha));
            glRasterPos2f(x, y);
            const char * c  = str;
            while(*c){
                glutBitmapCharacter(Graphics::font, *c);
                c = c + 1;
            }
        }
    }
}

void Graphics::restorePerspectiveProjection() {
    //switch to projection mode
    glMatrixMode(GL_PROJECTION);

    //restore previous projection matrix
    glPopMatrix();

    //get back to modelview mode
    glMatrixMode(GL_MODELVIEW);
}

void Graphics::setOrthographicProjection(const Event_Render * evt) {
    //switch to projection mode
    glMatrixMode(GL_PROJECTION);

    //save previous matrix which contains the
    //settings for the perspective projection
    glPushMatrix();

    //reset matrix
    glLoadIdentity();

    //set a 2D orthographic projection
    gluOrtho2D(0, evt->window_width, evt->window_height, 0);

    //switch back to modelview mode
    glMatrixMode(GL_MODELVIEW);
}

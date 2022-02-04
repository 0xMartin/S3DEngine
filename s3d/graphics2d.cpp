/***************************************************************************
 *
 *  File:       graphics2d.cpp
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

#include "graphics2d.h"

#include <math.h>


Graphics2D::Graphics2D(int windowHandle) : Graphics(windowHandle) {

}

void Graphics2D::drawLine(Point * p1, Point * p2) {
    if(p1 != NULL && p2 != NULL) {
        glColor4f(Graphics::color.red, Graphics::color.green, Graphics::color.blue,
                  MIN(Graphics::color.alpha, Graphics::maxAlpha));
        glBegin(GL_LINES);
        glVertex2f(p1->x, p1->y);
        glVertex2f(p2->x, p2->y);
        glEnd();
    }
}

void Graphics2D::drawLines(Point * p, size_t count) {
    if(p != NULL && count > 0) {
        Point * p1, *p2;
        p1 = p;
        p2 = NULL;

        glColor4f(Graphics::color.red, Graphics::color.green, Graphics::color.blue,
                  MIN(Graphics::color.alpha, Graphics::maxAlpha));
        for(size_t i = 1; i < count; ++i) {
            p2 = p1 + 1;
            glBegin(GL_LINES);
            glVertex2f(p1->x, p1->y);
            glVertex2f(p2->x, p2->y);
            glEnd();
            p1 = p2;
        }
    }
}

void Graphics2D::drawTriangle(Point * p1, Point * p2, Point * p3) {
    if(p1 != NULL && p2 != NULL && p3 != NULL) {
        glColor4f(Graphics::color.red, Graphics::color.green, Graphics::color.blue,
                  MIN(Graphics::color.alpha, Graphics::maxAlpha));
        glBegin(GL_LINE_LOOP);
        glVertex2f(p1->x, p1->y);
        glVertex2f(p2->x, p2->y);
        glVertex2f(p3->x, p3->y);
        glEnd();
    }
}

void Graphics2D::drawQuad(Point * p1, Point * p2, Point * p3, Point * p4) {
    if(p1 != NULL && p2 != NULL && p3 != NULL) {
        glColor4f(Graphics::color.red, Graphics::color.green, Graphics::color.blue,
                  MIN(Graphics::color.alpha, Graphics::maxAlpha));
        glBegin(GL_LINE_LOOP);
        glVertex2f(p1->x, p1->y);
        glVertex2f(p2->x, p2->y);
        glVertex2f(p3->x, p3->y);
        glVertex2f(p4->x, p4->y);
        glEnd();
    }
}

void Graphics2D::drawPolygon(Point * p, size_t count) {
    if(p != NULL && count > 3) {
        glColor4f(Graphics::color.red, Graphics::color.green, Graphics::color.blue,
                  MIN(Graphics::color.alpha, Graphics::maxAlpha));
        glBegin(GL_LINE_LOOP);
        for(size_t i = 0; i <= count; ++i) {
            glVertex2f((p + i)->x, (p + i)->y);
        }
        glEnd();
    }
}

void Graphics2D::drawRectangle(Point * p, size_t width, size_t height) {
    if(p != NULL && width > 0 && height > 0) {
        glColor4f(Graphics::color.red, Graphics::color.green, Graphics::color.blue,
                  MIN(Graphics::color.alpha, Graphics::maxAlpha));
        glBegin(GL_LINE_LOOP);
        glVertex2f(p->x, p->y);
        glVertex2f(p->x + width, p->y);
        glVertex2f(p->x + width, p->y + height);
        glVertex2f(p->x, p->y + height);
        glEnd();
    }
}

void Graphics2D::fillTriangle(Point * p1, Point * p2, Point * p3) {
    if(p1 != NULL && p2 != NULL && p3 != NULL) {
        glColor4f(Graphics::color.red, Graphics::color.green, Graphics::color.blue,
                  MIN(Graphics::color.alpha, Graphics::maxAlpha));
        glBegin(GL_TRIANGLES);
        glVertex2f(p1->x, p1->y);
        glVertex2f(p2->x, p2->y);
        glVertex2f(p3->x, p3->y);
        glEnd();
    }
}

void Graphics2D::fillQuad(Point * p1, Point * p2, Point * p3, Point * p4) {
    if(p1 != NULL && p2 != NULL && p3 != NULL) {
        glColor4f(Graphics::color.red, Graphics::color.green, Graphics::color.blue,
                  MIN(Graphics::color.alpha, Graphics::maxAlpha));
        glBegin(GL_QUADS);
        glVertex2f(p1->x, p1->y);
        glVertex2f(p2->x, p2->y);
        glVertex2f(p3->x, p3->y);
        glVertex2f(p4->x, p4->y);
        glEnd();
    }
}

void Graphics2D::fillPolygon(Point * p, size_t count) {
    if(p != NULL && count >= 3) {
        glColor4f(Graphics::color.red, Graphics::color.green, Graphics::color.blue,
                  MIN(Graphics::color.alpha, Graphics::maxAlpha));
        glBegin(GL_POLYGON);
        for(size_t i = 0; i < count; ++i) {
            glVertex2f((p + i)->x, (p + i)->y);
        }
        glEnd();
    }
}

void Graphics2D::drawEllipse(Point * p, GLfloat rx, GLfloat ry) {
    if(p != NULL) {
        int num_segments = 12 + MAX(rx, ry) / 5;
        float theta = 2 * 3.1415926 / num_segments;
        float c = cosf(theta);
        float s = sinf(theta);
        float t;
        float x = 1;
        float y = 0;

        glColor4f(Graphics::color.red, Graphics::color.green, Graphics::color.blue,
                  MIN(Graphics::color.alpha, Graphics::maxAlpha));
        glBegin(GL_LINE_LOOP);
        for(int i = 0; i < num_segments; i++)
        {
            glVertex2f(x * rx + p->x, y * ry + p->y);
            t = x;
            x = c * x - s * y;
            y = s * t + c * y;
        }
        glEnd();
    }
}

void Graphics2D::fillEllipse(Point * p, GLfloat rx, GLfloat ry) {
    if(p != NULL) {
        int num_segments = 12 + MAX(rx, ry) / 5;
        float theta = 2 * 3.1415926 / num_segments;
        float c = cosf(theta);
        float s = sinf(theta);
        float t;
        float x = 1;
        float y = 0;

        glColor4f(Graphics::color.red, Graphics::color.green, Graphics::color.blue,
                  MIN(Graphics::color.alpha, Graphics::maxAlpha));
        glBegin(GL_POLYGON);
        for(int i = 0; i < num_segments; i++)
        {
            glVertex2f(x * rx + p->x, y * ry + p->y);
            t = x;
            x = c * x - s * y;
            y = s * t + c * y;
        }
        glEnd();
    }
}

void Graphics2D::fillRectangle(Point * p, size_t width, size_t height) {
    if(p != NULL && width > 0 && height > 0) {

        glColor4f(Graphics::color.red, Graphics::color.green, Graphics::color.blue,
                  MIN(Graphics::color.alpha, Graphics::maxAlpha));
        glBegin(GL_QUADS);
        glVertex2f(p->x, p->y);
        glVertex2f(p->x + width, p->y);
        glVertex2f(p->x + width, p->y + height);
        glVertex2f(p->x, p->y + height);
        glEnd();
    }
}

void Graphics2D::drawImage(Point * p, Texture * texture, bool defaultShape) {
    if(p != NULL) {
        glColor4f(1.0, 1.0, 1.0, Graphics::color.alpha);
        texture->bindTexture();
        glBegin(GL_QUADS);

        if(defaultShape) {
            glTexCoord2i(0, 0);
            glVertex2f(p->x, p->y + texture->getHeight());

            glTexCoord2i(0, 1);
            glVertex2f(p->x, p->y);

            glTexCoord2i(1, 1);
            glVertex2f(p->x + texture->getWidth(), p->y);

            glTexCoord2i(1, 0);
            glVertex2f(p->x + texture->getWidth(), p->y + texture->getHeight());
        } else {
            for(unsigned int i = 0; i < 4; ++i) {
                glTexCoord2i(i > 1, i > 0 && i < 3);
                glVertex2f((p + i)->x, (p + i)->y);
            }
        }

        glEnd();
        texture->unbindTexture();
    }
}

void Graphics2D::fillMesh(Point * p, std::vector<Face2*> * faces) {
    if(p == NULL || faces == NULL) return;

    Graphics::applyOffset(p->x, p->y, 0.0);
    for(Face2 * face : *faces) {
        Graphics2D::fillPolygon(*face->points.data(), face->points.size());
    }
    Graphics::applyOffset(-p->x, -p->y, 0.0);

}

void Graphics2D::drawMesh(Point * p, std::vector<Face2*> * faces) {
    if(p == NULL || faces == NULL) return;

    Graphics::applyOffset(p->x, p->y, 0.0);
    for(Face2 * face : *faces) {
        Graphics2D::drawPolygon(*face->points.data(), face->points.size());
    }
    Graphics::applyOffset(-p->x, -p->y, 0.0);

}

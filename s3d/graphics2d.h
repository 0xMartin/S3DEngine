/***************************************************************************
 *
 *  File:       graphics2d.h
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

#ifndef GRAPHICS2D_H
#define GRAPHICS2D_H

#include "graphics.h"
#include "texture.h"


/*---------------------------------------2D-Objects-----------------------------------------------*/
typedef S3D_EXPORT struct {
    GLfloat x; /** X position of point*/
    GLfloat y; /** Y position of point*/
} Point;

typedef S3D_EXPORT struct {
    Point position; /** Position */
    size_t width; /** Width */
    size_t height; /** Height */
} Bounds;

typedef S3D_EXPORT struct {
    std::vector<Point*> points;
    GLint textureID;
} Face2;
/*------------------------------------------------------------------------------------------------*/


/**
 * @brief The Graphics2D class
 */
class S3D_EXPORT Graphics2D : public Graphics {
public:
    Graphics2D(int windowHandle);

    /**
     * @brief drawLine
     * @param p1
     * @param p2
     */
    void drawLine(Point * p1, Point * p2);

    /**
     * @brief drawLines
     * @param p
     * @param count
     */
    void drawLines(Point * p, size_t count);

    /**
     * @brief drawTriangle
     * @param p1
     * @param p2
     * @param p3
     */
    void drawTriangle(Point * p1, Point * p2, Point * p3);

    /**
     * @brief drawQuad
     * @param p1
     * @param p2
     * @param p3
     * @param p4
     */
    void drawQuad(Point * p1, Point * p2, Point * p3, Point * p4);

    /**
     * @brief drawPolygon
     * @param p
     * @param count
     */
    void drawPolygon(Point * p, size_t count);

    /**
     * @brief drawRectangle
     * @param p
     * @param width
     * @param height
     */
    void drawRectangle(Point * p, size_t width, size_t height);

    /**
     * @brief fillTriangle
     * @param p1
     * @param p2
     * @param p3
     */
    void fillTriangle(Point * p1, Point * p2, Point * p3);

    /**
     * @brief fillQuad
     * @param p1
     * @param p2
     * @param p3
     * @param p4
     */
    void fillQuad(Point * p1, Point * p2, Point * p3, Point * p4);

    /**
     * @brief fillPolygon
     * @param p
     * @param count
     */
    void fillPolygon(Point * p, size_t count);

    /**
     * @brief drawEllipse
     * @param p
     * @param rx
     * @param ry
     */
    void drawEllipse(Point * p, GLfloat rx, GLfloat ry);

    /**
     * @brief fillEllipse
     * @param p
     * @param rx
     * @param ry
     */
    void fillEllipse(Point * p, GLfloat rx, GLfloat ry);

    /**
     * @brief fillRectangle
     * @param p
     * @param width
     * @param height
     */
    void fillRectangle(Point * p, size_t width, size_t height);

    /**
     * @brief drawImage
     * @param p
     * @param texture
     * @param defaultShape
     */
    void drawImage(Point * p, Texture * texture, bool defaultShape);

    /**
     * @brief mesh
     * @param p
     */
    void fillMesh(Point * p, std::vector<Face2*> * faces);

    /**
     * @brief drawMesh
     * @param p
     * @param faces
     */
    void drawMesh(Point * p, std::vector<Face2*> * faces);
};


#endif // GRAPHICS2D_H

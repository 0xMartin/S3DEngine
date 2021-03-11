/**
 * <------------------------------------------------------------------>
 * @name    2D Engine
 * @author  Martin Krcma
 * @date    8. 3. 2021
 * <------------------------------------------------------------------>
 * @file    render.h
 * @brief
 * <------------------------------------------------------------------>
 */

#ifndef RENDER_H
#define RENDER_H


#if __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

#if _WIN32
#include <Windows.h>
#endif

#include "util.h"


//colors
#define COLOR_BLACK     {0.0,   0.0,    0.0,    1.0}
#define COLOR_BLUE      {0.0,   0.0,    1.0,    1.0}
#define COLOR_CYAN      {0.0,   1.0,    1.0,    1.0}
#define COLOR_DARKGRAY	{0.25,  0.25,   0.25,   1.0}
#define COLOR_GRAY      {0.5,   0.5,    0.5,    1.0}
#define COLOR_GREEN     {0.0,   1.0,    0.0,    1.0}
#define COLOR_LIGHTGRAY	{0.75,  0.75,   0.75,   1.0}
#define COLOR_MAGENTA	{1.0,   0.0,    1.0,    1.0}
#define COLOR_ORANGE	{1.0,   0.78,   0.0,    1.0}
#define COLOR_PINK      {1.0,   0.69,   0.69,   1.0}
#define COLOR_RED       {1.0,   0.0,    0.0,    1.0}
#define COLOR_WHITE     {1.0,   1.0,    1.0,    1.0}
#define COLOR_YELLOW	{1.0,   1.0,    0.0,    1.0}

#define COLOR_DARKER(n, c)	({\
    n.red = c.red * 0.8;\
    n.green = c.green * 0.8;\
    n.blue = c.blue * 0.8;})

#define COLOR_LIGHTER(n, c) ({\
    n.red = MIN(1.0, c.red * 1.2);\
    n.green = MIN(1.0, c.green * 1.2);\
    n.blue = MIN(1.0, c.blue * 1.2);})

//fonts
#define E2D_STROKE_ROMAN            GLUT_STROKE_ROMAN
#define E2D_STROKE_MONO_ROMAN       GLUT_STROKE_MONO_ROMAN
#define E2D_BITMAP_9_BY_15          GLUT_BITMAP_9_BY_15
#define E2D_BITMAP_8_BY_13          GLUT_BITMAP_8_BY_13
#define E2D_BITMAP_TIMES_ROMAN_10   GLUT_BITMAP_TIMES_ROMAN_10
#define E2D_BITMAP_TIMES_ROMAN_24   GLUT_BITMAP_TIMES_ROMAN_24
#define E2D_BITMAP_HELVETICA_10     GLUT_BITMAP_HELVETICA_10
#define E2D_BITMAP_HELVETICA_12     GLUT_BITMAP_HELVETICA_12
#define E2D_BITMAP_HELVETICA_18     GLUT_BITMAP_HELVETICA_18


//RGB color
typedef struct {
    GLfloat red; /** red color*/
    GLfloat green; /** green color*/
    GLfloat blue; /** blue color*/
    GLfloat alpha; /** alpha*/
} Color;

//2D point
typedef struct {
    GLfloat x; /** X position of point*/
    GLfloat y; /** Y position of point*/
    Color color; /** color of point*/
} Point2D;


/**
 * @brief Render_setColorRGB
 * @param red
 * @param green
 * @param blue
 */
void Render_setColorRGB(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);

/**
 * @brief Render_setColor
 * @param color
 */
void Render_setColor(Color * color);

/**
 * @brief Render_setAlpha
 * @param alpha
 */
void Render_setAlpha(GLfloat alpha);

/**
 * @brief Render_setColor
 * @param color
 */
void Render_enablePtColor();

/**
 * @brief Render_setColor
 * @param color
 */
void Render_disablePtColor();

/**
 * @brief Render_clear
 * @param color
 */
void Render_clear(Color * color);

/**
 * @brief Render_drawLine
 * @param p1
 * @param p2
 */
void Render_drawLine(Point2D * p1, Point2D * p2);

/**
 * @brief Render_drawLines
 * @param p
 * @param count
 */
void Render_drawLines(Point2D * p, size_t count);

/**
 * @brief Render_drawTriangle
 * @param p1
 * @param p2
 * @param p3
 */
void Render_drawTriangle(Point2D * p1, Point2D * p2, Point2D * p3);

/**
 * @brief Render_drawQuad
 * @param p1
 * @param p2
 * @param p3
 * @param p4
 */
void Render_drawQuad(Point2D * p1, Point2D * p2, Point2D * p3, Point2D * p4);

/**
 * @brief Render_drawPolygon
 * @param p
 * @param count
 */
void Render_drawPolygon(Point2D * p, size_t count);

/**
 * @brief Render_drawRectangle
 * @param p
 * @param width
 * @param height
 */
void Render_drawRectangle(Point2D * p, size_t width, size_t height);

/**
 * @brief Render_fillTriangle
 * @param p1
 * @param p2
 * @param p3
 */
void Render_fillTriangle(Point2D * p1, Point2D * p2, Point2D * p3);

/**
 * @brief Render_fillQuad
 * @param p1
 * @param p2
 * @param p3
 * @param p4
 */
void Render_fillQuad(Point2D * p1, Point2D * p2, Point2D * p3, Point2D * p4);

/**
 * @brief Render_fillPolygon
 * @param p
 * @param count
 */
void Render_fillPolygon(Point2D * p, size_t count);

/**
 * @brief Render_drawEllipse
 * @param p
 * @param rx
 * @param ry
 */
void Render_drawEllipse(Point2D * p, GLfloat rx, GLfloat ry);

/**
 * @brief Render_fillEllipse
 * @param p
 * @param rx
 * @param ry
 */
void Render_fillEllipse(Point2D * p, GLfloat rx, GLfloat ry);

/**
 * @brief Render_fillRectangle
 * @param p
 * @param width
 * @param height
 */
void Render_fillRectangle(Point2D * p, size_t width, size_t height);

/**
 * @brief Render_drawImage
 * @param p
 * @param texture
 * @param position
 */
void Render_drawImage(Point2D * p, Texture * texture, bool position);

/**
 * @brief Render_setFont
 * @param font
 * @param size
 */
void Render_setFont(void * font, GLint size);

/**
 * @brief Render_drawString
 * @param p
 * @param str
 */
void Render_drawString(GLfloat x, GLfloat y,  const char * const str);

#endif // RENDER_H

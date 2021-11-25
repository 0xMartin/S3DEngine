/******************************************************************************
 * S3D Engine
 *
 * @file       graphics.h
 * @brief      XXXX Function
 *
 * @author     Martin Krcma
 * @date       2021/07/20
 *****************************************************************************/

#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "api.h"

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
#include "event.h"
#include <vector>


/*------------------------------------Colors------------------------------------------------------*/
#define COLOR_BLACK     (Color){0.0,   0.0,    0.0,    1.0}
#define COLOR_BLUE      (Color){0.0,   0.0,    1.0,    1.0}
#define COLOR_CYAN      (Color){0.0,   1.0,    1.0,    1.0}
#define COLOR_DARKGRAY	(Color){0.25,  0.25,   0.25,   1.0}
#define COLOR_GRAY      (Color){0.5,   0.5,    0.5,    1.0}
#define COLOR_GREEN     (Color){0.0,   1.0,    0.0,    1.0}
#define COLOR_LIGHTGRAY	(Color){0.75,  0.75,   0.75,   1.0}
#define COLOR_MAGENTA	(Color){1.0,   0.0,    1.0,    1.0}
#define COLOR_ORANGE	(Color){1.0,   0.78,   0.0,    1.0}
#define COLOR_PINK      (Color){1.0,   0.69,   0.69,   1.0}
#define COLOR_RED       (Color){1.0,   0.0,    0.0,    1.0}
#define COLOR_WHITE     (Color){1.0,   1.0,    1.0,    1.0}
#define COLOR_YELLOW	(Color){1.0,   1.0,    0.0,    1.0}


#define COLOR_DARKER(c, factor)	((Color){.red=(GLfloat)(c.red*(1.0-factor)),\
    .green=(GLfloat)(c.green*(1.0-factor)), .blue=(GLfloat)(c.blue*(1.0-factor)), .alpha=c.alpha})

#define COLOR_LIGHTER(c, factor) ((Color){.red=(GLfloat)MIN(1.0, c.red * 1.0 + factor),\
    .green=(GLfloat)MIN(1.0, c.green * 1.0 + factor), .blue=(GLfloat)MIN(1.0, c.blue * 1.0 + factor), .alpha=c.alpha})

#define COLOR_CHANGE_OPACITY(c, opacity) ((Color){.red=c.red, .green=c.green, .blue=c.blue, .alpha=opacity})

typedef struct {
    GLfloat red; /** red color*/
    GLfloat green; /** green color*/
    GLfloat blue; /** blue color*/
    GLfloat alpha; /** alpha*/
} Color;
/*------------------------------------------------------------------------------------------------*/


/*-------------------------------------Fonts------------------------------------------------------*/
#define S3D_STROKE_ROMAN            GLUT_STROKE_ROMAN
#define S3D_STROKE_MONO_ROMAN       GLUT_STROKE_MONO_ROMAN
#define S3D_BITMAP_9_BY_15          GLUT_BITMAP_9_BY_15
#define S3D_BITMAP_8_BY_13          GLUT_BITMAP_8_BY_13
#define S3D_BITMAP_TIMES_ROMAN_10   GLUT_BITMAP_TIMES_ROMAN_10
#define S3D_BITMAP_TIMES_ROMAN_24   GLUT_BITMAP_TIMES_ROMAN_24
#define S3D_BITMAP_HELVETICA_10     GLUT_BITMAP_HELVETICA_10
#define S3D_BITMAP_HELVETICA_12     GLUT_BITMAP_HELVETICA_12
#define S3D_BITMAP_HELVETICA_18     GLUT_BITMAP_HELVETICA_18
/*------------------------------------------------------------------------------------------------*/

#define DEFAULT_LINE_WIDTH 1


/**
 * @brief The Graphics class
 */
class S3D_EXPORT Graphics {
protected:
    int windowHandle;
    Color color;
    GLfloat maxAlpha;
    GLfloat scale_x;
    GLfloat scale_y;
    GLfloat scale_z;
    GLfloat offset_x;
    GLfloat offset_y;
    GLfloat offset_z;
    void * font;

    Event_Render currentRenderEvt;
public:
    Graphics(int windowHandle);

    /**
     * @brief begin
     * @param evt
     */
    void begin(Event_Render * evt, Color * color);

    /**
     * @brief scale
     * @param x
     * @param y
     * @param z
     */
    void scale(GLfloat x, GLfloat y, GLfloat z);

    /**
     * @brief lineWidth
     * @param width
     */
    void lineWidth(GLfloat width);

    /**
     * @brief setMaxAlpha
     * @param alpha
     */
    void setMaxAlpha(GLfloat alpha);

    /**
     * @brief getStringWidth
     * @param alpha
     * @return
     */
    int getStringWidth(const char * str);

    /**
     * @brief getStringWidthIndex
     * @param str
     * @param lastCharIndex
     * @return
     */
    int getStringWidthIndex(const char * str, int lastCharIndex);

    /**
     * @brief getStringWidthRange
     * @param str
     * @param start
     * @param end
     * @return
     */
    int getStringWidthRange(const char * str, int start, int end);

    /**
     * @brief getStringHeight
     * @return
     */
    int getStringHeight();

    /**
     * @brief setColorRGB
     * @param red
     * @param green
     * @param blue
     */
    void setColorRGB(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);

    /**
     * @brief setColor
     * @param color
     */
    void setColor(Color * color);

    /**
     * @brief setAlpha
     * @param alpha
     */
    void setAlpha(GLfloat alpha);

    /**
     * @brief applyOffset
     * @param x
     * @param y
     * @param z
     */
    void applyOffset(GLfloat x, GLfloat y, GLfloat z);

    /**
     * @brief clearOffset
     */
    void clearOffset();

    /**
     * @brief setScissor
     * @param x
     * @param y
     * @param width
     * @param heigh
     * @param evt
     */
    void setScissor(GLfloat x, GLfloat y, GLfloat width,
                           GLfloat height, const Event_Render * evt);

    /**
     * @brief resetScissor
     * @param evt
     */
    void resetScissor(const Event_Render * evt);

    /**
     * @brief clear
     * @param evt
     * @param color
     */
    void clear(Event_Render * evt, Color * color);

    /**
     * @brief render
     */
    void render();

    /**
     * @brief setFont
     * @param font
     * @param size
     */
    void setFont(void * font, GLint size);

    /**
     * @brief drawString
     * @param p
     * @param str
     */
    void drawString(GLfloat x, GLfloat y,  const char * const str);

    /**
     * @brief restorePerspectiveProjection
     */
    void restorePerspectiveProjection();

    /**
     * @brief setOrthographicProjection
     * @param evt
     */
    void setOrthographicProjection(const Event_Render * evt);
};

#endif // GRAPHICS_H

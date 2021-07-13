#ifndef GRAPHICS2D_H
#define GRAPHICS2D_H

#include "graphics.h"


typedef struct {
    GLfloat x; /** X position of point*/
    GLfloat y; /** Y position of point*/
    Color color; /** color of point*/
} Point2D;

typedef struct {
    Point2D position; /** Position */
    size_t width; /** Width */
    size_t height; /** Height */
} Bounds2D;

typedef struct {
    Point2D * points;
    size_t count;
    GLint textureID;
} Face2D;

class Graphics2D : public Graphics {
private:
    void applyPtColor(Point2D * p);

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
    bool enableVerColor;

public:
    Graphics2D(int windowHandle);

    /**
     * @brief drawLine
     * @param p1
     * @param p2
     */
    void drawLine(Point2D * p1, Point2D * p2);

    /**
     * @brief drawLines
     * @param p
     * @param count
     */
    void drawLines(Point2D * p, size_t count);

    /**
     * @brief drawTriangle
     * @param p1
     * @param p2
     * @param p3
     */
    void drawTriangle(Point2D * p1, Point2D * p2, Point2D * p3);

    /**
     * @brief drawQuad
     * @param p1
     * @param p2
     * @param p3
     * @param p4
     */
    void drawQuad(Point2D * p1, Point2D * p2, Point2D * p3, Point2D * p4);

    /**
     * @brief drawPolygon
     * @param p
     * @param count
     */
    void drawPolygon(Point2D * p, size_t count);

    /**
     * @brief drawRectangle
     * @param p
     * @param width
     * @param height
     */
    void drawRectangle(Point2D * p, size_t width, size_t height);

    /**
     * @brief fillTriangle
     * @param p1
     * @param p2
     * @param p3
     */
    void fillTriangle(Point2D * p1, Point2D * p2, Point2D * p3);

    /**
     * @brief fillQuad
     * @param p1
     * @param p2
     * @param p3
     * @param p4
     */
    void fillQuad(Point2D * p1, Point2D * p2, Point2D * p3, Point2D * p4);

    /**
     * @brief fillPolygon
     * @param p
     * @param count
     */
    void fillPolygon(Point2D * p, size_t count);

    /**
     * @brief drawEllipse
     * @param p
     * @param rx
     * @param ry
     */
    void drawEllipse(Point2D * p, GLfloat rx, GLfloat ry);

    /**
     * @brief fillEllipse
     * @param p
     * @param rx
     * @param ry
     */
    void fillEllipse(Point2D * p, GLfloat rx, GLfloat ry);

    /**
     * @brief fillRectangle
     * @param p
     * @param width
     * @param height
     */
    void fillRectangle(Point2D * p, size_t width, size_t height);

    /**
     * @brief drawImage
     * @param p
     * @param texture
     * @param defaultShape
     */
    void drawImage(Point2D * p, Texture * texture, bool defaultShape);

    /**
     * @brief mesh
     * @param p
     */
    void fillMesh(Point2D * p, std::vector<Face2D*> * faces);

    /**
     * @brief drawMesh
     * @param p
     * @param faces
     */
    void drawMesh(Point2D * p, std::vector<Face2D*> * faces);
};


#endif // GRAPHICS2D_H

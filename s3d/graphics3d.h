#ifndef GRAPHICS3D_H
#define GRAPHICS3D_H

#include "graphics2d.h"


typedef struct {
    GLfloat x; /** X position*/
    GLfloat y; /** Y position*/
    GLfloat z; /** Z position*/
} Vertex3;

typedef struct {
    std::vector<Vertex3*> v; /** vertices */
    std::vector<Point*> vt; /** texture coordinates */
    std::vector<Vertex3*> vn; /** normals */
    GLint textureID;
} Face3;

typedef struct {
    Vertex3 * v[3]; /** vertices */
    Point * vt[3]; /** texture coordinates */
    Vertex3 * vn[3]; /** normals */
    GLint textureID;
} Triangle3;


class Graphics3D : public Graphics2D {
public:
    Graphics3D(int windowHandle);

    /**
     * @brief drawTriangle
     * @param t
     */
    void drawTriangle(Triangle3 * t);

    /**
     * @brief drawTriangles
     * @param triangles
     */
    void drawTriangles(std::vector<Triangle3> & triangles);

    /**
     * @brief fillTriangle
     * @param t
     */
    void fillTriangle(Triangle3 * t);

    /**
     * @brief fillTriangles
     * @param triangles
     */
    void fillTriangles(std::vector<Triangle3> & triangles);

    /**
     * @brief drawFaces
     * @param faces
     */
    void drawFaces(std::vector<Face3> & faces);

    /**
     * @brief fillFaces
     * @param faces
     */
    void fillFaces(std::vector<Face3> & faces);

    /**
     * @brief drawImage
     * @param p
     * @param texture
     * @param defaultShape
     */
    void drawImage(Vertex3 * p, Texture * texture, bool defaultShape);
};

#endif // GRAPHICS3D_H

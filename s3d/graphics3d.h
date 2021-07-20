/******************************************************************************
 * S3D Engine
 *
 * @file       graphics3d.h
 * @brief      XXXX Function
 *
 * @author     Martin Krcma
 * @date       2021/07/20
 *****************************************************************************/

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
} Face3;

typedef struct {
    Vertex3 * v[3]; /** vertices */
    Point * vt[3]; /** texture coordinates */
    Vertex3 * vn[3]; /** normals */
} Triangle3;


/*------------------------------------FloatBuffer-------------------------------------------------*/
class FloatBuffer {
public:
    GLfloat * vertices;
    GLfloat * normals;
    GLfloat * textureCoords;
    size_t size;

    FloatBuffer();
    ~FloatBuffer();

    /**
     * @brief convertTrianglesToArray
     * @param triangles
     * @return
     */
    bool convertTrianglesToArray(std::vector<Triangle3> & triangles);

    /**
     * @brief getSizeInBytes
     * @return
     */
    size_t getSizeInBytes();
};
/*------------------------------------------------------------------------------------------------*/


class Graphics3D : public Graphics2D {
private:
    //triangles only
    GLuint vertexBuffer; /** vertex buffer */
    GLuint normalBuffer; /** normal buffer */
    GLuint textureCoordBuffer; /** texture cord buffer */
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
     * @param position
     * @param rotation
     * @param texture
     * @param width
     * @param height
     */
    void drawImage(Vertex3 * position, Vertex3 * rotation,
                   Texture * texture, size_t width, size_t height);

    /**
     * @brief drawFloatBuffer
     * @param buffer
     */
    void drawFloatBuffer(FloatBuffer * buffer);
};


#endif // GRAPHICS3D_H

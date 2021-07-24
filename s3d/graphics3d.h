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
#include "shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


/*---------------------------------------Shader-Uniforms------------------------------------------*/
#define MODEL_VIEW_PROJECTION_MATRIX_UNIFORM ("MVP")
#define MODEL_MATRIX_UNIFORM ("M")
#define LIGHT_POSITION_UNIFORM ("lightPos")
#define LIGHT_COLOR_UNIFORM ("lightColor")
#define VIEW_POSITION_UNIFORM ("viewPos")
#define COLOR_UNIFORM ("Color")
/*------------------------------------------------------------------------------------------------*/


/*---------------------------------------3D-Objects-----------------------------------------------*/
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
/*------------------------------------------------------------------------------------------------*/


/*-------------------------------------DataBuffer-------------------------------------------------*/

typedef enum {
    VBO_Texture, /** format: v.x, v.y, v.z, n.x, n.y, n.z, vt.x, vt. */
    VBO_Color /** format: v.x, v.y, v.z, n.x, n.y, n.z*/
} VBOType;

class VertexDataBuffer {
public: 
    VBOType type; /** type of buffer */
    GLfloat * data; /** array with data */
    size_t size; /** number of vertices */

    VertexDataBuffer(VBOType type);
    ~VertexDataBuffer();

    /**
     * @brief buildVertexData
     * @param triangles
     * @param type
     * @return
     */
    bool buildVertexData(std::vector<Triangle3> & triangles, VBOType type);

    /**
     * @brief getSizeInBytes
     * @return
     */
    size_t getSizeInBytes();
};
/*------------------------------------------------------------------------------------------------*/


typedef struct {
    Vertex3 position;
    Color color;
} Light;


/**
 * @brief The Graphics3D class
 */
class Graphics3D : public Graphics2D {
protected:
    //triangles only
    GLuint vertexBuffer; /** vertex buffer */

    ShaderProgram * defaultShader;
    ShaderProgram * shaderProgram; /** active shader program */

    glm::mat4 projection; /** scene projection matrix */

    std::vector<Light*> * lights; /** vector with lights */
public:

    Graphics3D(int windowHandle);
    ~Graphics3D();

    /**
     * @brief computeProjectionMatrix
     * @param FOV
     * @param aspect
     * @param zNear
     * @param zFar
     */
    void computeProjectionMatrix(GLdouble FOV, GLdouble aspect,
                                 GLdouble zNear, GLdouble zFar);

    /**
     * @brief bindLightVector
     * @param lights
     */
    void bindLightVector(std::vector<Light*> * lights);

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
     * @brief drawVertexDataBuffer
     * @param buffer
     * @param modelMatrix
     */
    void drawVertexDataBuffer(VertexDataBuffer * buffer, GLfloat * modelTransformMatrix);

    /**
     * @brief setShaderProgram
     * @param shaderProgram
     */
    void setShaderProgram(ShaderProgram * shaderProgram);

    /**
     * @brief setDefaultShaderProgram
     */
    void setDefaultShaderProgram();
};


#endif // GRAPHICS3D_H

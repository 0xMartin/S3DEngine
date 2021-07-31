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
typedef enum {
    OBJECT_SHADER,
    SKYBOX_SHADER,
    IMG_SHADER,
    GRASS_SHADER,
    WATTER_SHADER,
    GLASS_SHADER,
    ALL
} ShaderType;


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
    Vertex3 * v[3]; /** vertices */
    Point * vt[3]; /** texture coordinates */
    Vertex3 * vn[3]; /** normals */
} Triangle3;
/*------------------------------------------------------------------------------------------------*/


/*-------------------------------------DataBuffer-------------------------------------------------*/

class VertexDataBuffer {
public: 
    std::vector<GLfloat> positionBuffer; /** buffer with positions */
    std::vector<GLfloat> normalsBuffer; /** buffer with positions */
    std::vector<GLfloat> UVBuffer; /** buffer with positions */
    size_t vertexCount; /** number of vertices */

    VertexDataBuffer();

    /**
     * @brief buildVertexData
     * @param triangles
     * @param type
     * @return
     */
    bool buildVertexData(Triangle3 & triangle);

    /**
     * @brief buildVertexData
     * @param triangles
     * @param type
     * @return
     */
    bool buildVertexData(std::vector<Triangle3> & triangles);

    /**
     * @brief getPositionData
     * @return
     */
    GLfloat * getPositionData();

    /**
     * @brief getPositionData
     * @return
     */
    GLfloat * getNormalData();

    /**
     * @brief getPositionData
     * @return
     */
    GLfloat * getUVData();

    /**
     * @brief clear
     */
    void clear();

    /**
     * @brief pushPositionVertex
     * @param v
     */
    void pushPositionVertex(Vertex3 v);

    /**
     * @brief pushPositionVertex
     * @param v
     */
    void pushNormalVertex(Vertex3 v);

    /**
     * @brief pushPositionVertex
     * @param v
     */
    void pushUVVertex(Point v);
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
    GLuint VBO_position;
    GLuint VBO_normal;
    GLuint VBO_UV;

    GLuint VAO_object;
    GLuint VAO_skybox;


    //shader programs
    ShaderProgram * objectShader;
    ShaderProgram * skyboxShader;
    ShaderProgram * imageShader;

    glm::mat4 projectionMatrix; /** scene projection matrix */

    std::vector<Light*> * lights; /** vector with lights */

    Texture * texture; /** current texture */

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
     * @brief drawVertexDataBuffer
     * @param buffer
     * @param modelMatrix
     */
    void drawVertexDataBuffer(VertexDataBuffer * buffer, GLfloat * modelTransformMatrix);

    /**
     * @brief setShaderProgram
     * @param shaderProgram
     */
    void setShaderProgram(ShaderProgram * shaderProgram, ShaderType type);

    /**
     * @brief setDefaultShaderProgram
     */
    void setDefaultShaderProgram(ShaderType type);

    /**
     * @brief drawSkyBox
     * @param tex
     * @param scale
     */
    ShaderProgram * getShaderProgram(int type);

    /**
     * @brief setTexture
     * @param texture
     */
    void setTexture(Texture * texture);

    /**
     * @brief drawLine
     * @param v1
     * @param v2
     */
    void drawLine(Vertex3 v1, Vertex3 v2);

    /**
     * @brief drawLines
     * @param vertices
     */
    void drawLines(std::vector<Vertex3> vertices);

    /**
     * @brief drawTriangle
     * @param t
     */
    void drawTriangle(Triangle3 t);

    /**
     * @brief drawTriangles
     * @param triangles
     */
    void drawTriangles(std::vector<Triangle3> & triangles);

    /**
     * @brief drawTriangle
     * @param t
     */
    void drawCube(Vertex3 position, Vertex3 rotation, GLfloat size);

    /**
     * @brief fillTriangle
     * @param t
     */
    void fillTriangle(Triangle3 triangle);

    /**
     * @brief fillTriangles
     * @param triangles
     */
    void fillTriangles(std::vector<Triangle3> & triangles);

    /**
     * @brief fillTriangles
     * @param triangles
     */
    void fillPlane(Vertex3 position, Vertex3 rotation, size_t width, size_t height);

    /**
     * @brief drawCube
     * @param position
     * @param rotation
     * @param size
     */
    void fillCube(Vertex3 position, Vertex3 rotation, GLfloat size);

    /**
     * @brief drawImage
     * @param position
     * @param rotation
     * @param texture
     * @param width
     * @param height
     */
    void drawImage(Vertex3 position, Vertex3 rotation,
                   Texture * texture, size_t width, size_t height);


    /**
     * @brief drawSkybox
     * @param origin
     * @param textureID
     */
    void drawSkybox(Vertex3 origin, GLfloat scale, GLint textureID);

};


#endif // GRAPHICS3D_H

/***************************************************************************
 *
 *  File:       graphics3d.h
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

#ifndef GRAPHICS3D_H
#define GRAPHICS3D_H


#include "graphics2d.h"
#include "shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


/*---------------------------------------Shader-Uniforms------------------------------------------*/
typedef S3D_EXPORT enum {
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
typedef S3D_EXPORT struct {
    GLfloat x; /** X position*/
    GLfloat y; /** Y position*/
    GLfloat z; /** Z position*/
} Vertex3;

typedef S3D_EXPORT struct {
    Vertex3 * v[3]; /** vertices */
    Point * vt[3]; /** texture coordinates */
    Vertex3 * vn[3]; /** normals */
} Triangle3;
/*------------------------------------------------------------------------------------------------*/


/*-------------------------------------DataBuffer-------------------------------------------------*/

class S3D_EXPORT VertexDataBuffer {
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


typedef S3D_EXPORT struct {
    Vertex3 position;
    Color color;
} Light;


/**
 * @brief The Graphics3D class
 */
class S3D_EXPORT Graphics3D : public Graphics2D {
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

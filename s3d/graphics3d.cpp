/******************************************************************************
 * S3D Engine
 *
 * @file       graphics3d.cpp
 * @brief      XXXX Function
 *
 * @author     Martin Krcma
 * @date       2021/07/20
 *****************************************************************************/

#include "graphics3d.h"


#include "default_shaders.h"
#include <string.h>
#include <cstdarg>
#include <GLES3/gl3.h>



/*--------------------------------ModelDataBuffer-------------------------------------------------*/
VertexDataBuffer::VertexDataBuffer() {
    VertexDataBuffer::vertexCount = 0;
}


bool VertexDataBuffer::buildVertexData(Triangle3 & triangle) {
    std::vector<Triangle3> triangles;
    triangles.push_back(triangle);
    return VertexDataBuffer::buildVertexData(triangles);
}


bool VertexDataBuffer::buildVertexData(std::vector<Triangle3> & triangles) {
    //load all data to buffer
    unsigned int i;
    for(Triangle3 t : triangles) {
        for(i = 0; i < 3; ++i) {
            //position
            VertexDataBuffer::positionBuffer.push_back(t.v[i]->x);
            VertexDataBuffer::positionBuffer.push_back(t.v[i]->y);
            VertexDataBuffer::positionBuffer.push_back(t.v[i]->z);

            //normals
            VertexDataBuffer::normalsBuffer.push_back(t.vn[i]->x);
            VertexDataBuffer::normalsBuffer.push_back(t.vn[i]->y);
            VertexDataBuffer::normalsBuffer.push_back(t.vn[i]->y);

            //texture coord
            VertexDataBuffer::UVBuffer.push_back(t.vt[i]->x);
            VertexDataBuffer::UVBuffer.push_back(t.vt[i]->y);
        }
    }

    //set size (number of vertices)
    VertexDataBuffer::vertexCount = triangles.size() * 3;

    return true;
}


GLfloat * VertexDataBuffer::getPositionData() {
    return VertexDataBuffer::positionBuffer.data();
}


GLfloat * VertexDataBuffer::getNormalData() {
    return VertexDataBuffer::normalsBuffer.data();
}


GLfloat * VertexDataBuffer::getUVData() {
    return VertexDataBuffer::UVBuffer.data();
}


void VertexDataBuffer::clear() {
    VertexDataBuffer::positionBuffer.clear();
    VertexDataBuffer::normalsBuffer.clear();
    VertexDataBuffer::UVBuffer.clear();
}

void VertexDataBuffer::pushPositionVertex(Vertex3 v) {
    VertexDataBuffer::positionBuffer.push_back(v.x);
    VertexDataBuffer::positionBuffer.push_back(v.y);
    VertexDataBuffer::positionBuffer.push_back(v.z);
}

void VertexDataBuffer::pushNormalVertex(Vertex3 v) {
    VertexDataBuffer::normalsBuffer.push_back(v.x);
    VertexDataBuffer::normalsBuffer.push_back(v.y);
    VertexDataBuffer::positionBuffer.push_back(v.z);
}

void VertexDataBuffer::pushUVVertex(Point v) {
    VertexDataBuffer::UVBuffer.push_back(v.x);
    VertexDataBuffer::UVBuffer.push_back(v.y);
}
/*------------------------------------------------------------------------------------------------*/



Graphics3D::Graphics3D(int windowHandle) : Graphics2D(windowHandle) {
    //create buffer objects
    GLuint vbo[3];
    glGenBuffers(3, vbo);
    Graphics3D::VBO_position = vbo[0];
    Graphics3D::VBO_normal = vbo[1];
    Graphics3D::VBO_UV = vbo[2];

    //create VAO for (objects)
    //<-------------------------------------------------------------------------------->
    glGenVertexArrays(1, &(Graphics3D::VAO_object));
    glBindVertexArray(Graphics3D::VAO_object);

    //enable the vertex attribute arrays
    glEnableVertexAttribArray(0);  //vertex position
    glEnableVertexAttribArray(1);  //vertex normals
    glEnableVertexAttribArray(2);  //vertex UV


    glBindBuffer(GL_ARRAY_BUFFER, Graphics3D::VBO_position);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat),
                          NULL);

    glBindBuffer(GL_ARRAY_BUFFER, Graphics3D::VBO_normal);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat),
                          NULL);

    glBindBuffer(GL_ARRAY_BUFFER, Graphics3D::VBO_UV);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat),
                          NULL);
    //<-------------------------------------------------------------------------------->

    //create VAO for (skybox)
    //<-------------------------------------------------------------------------------->
    glGenVertexArrays(1, &(Graphics3D::VAO_skybox));
    glBindVertexArray(Graphics3D::VAO_skybox);

    //enable the vertex attribute arrays
    glEnableVertexAttribArray(0);  //vertex position

    glBindBuffer(GL_ARRAY_BUFFER, Graphics3D::VBO_position);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat),
                          NULL);
    //<-------------------------------------------------------------------------------->

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);


    //set default shader programs
    Graphics3D::setDefaultShaderProgram(ShaderType::ALL);
    //set projection
    Graphics3D::computeProjectionMatrix(45.0, 2.0, 0.1, 100.0);
    //init vars
    Graphics3D::texture = NULL;
}


Graphics3D::~Graphics3D() {
    glDeleteBuffers(1, &(Graphics3D::VBO_position));
    glDeleteBuffers(1, &(Graphics3D::VBO_normal));
    glDeleteBuffers(1, &(Graphics3D::VBO_UV));

    glDeleteVertexArrays(1, &(Graphics3D::VAO_object));
    glDeleteVertexArrays(1, &(Graphics3D::VAO_skybox));

    delete Graphics3D::objectShader;
    delete Graphics3D::skyboxShader;
}


void Graphics3D::computeProjectionMatrix(GLdouble FOV, GLdouble aspect,
                                         GLdouble zNear, GLdouble zFar) {
    gluPerspective(FOV, aspect, zNear, zFar);

    GLfloat buffer[16];
    glGetFloatv(GL_PROJECTION_MATRIX, buffer);
    Graphics3D::projectionMatrix = glm::make_mat4(buffer);
}


void Graphics3D::bindLightVector(std::vector<Light*> * lights) {
    Graphics3D::lights = lights;
}


void Graphics3D::drawVertexDataBuffer(VertexDataBuffer * buffer, GLfloat * modelTransformMatrix) {
    if(buffer == NULL) return;
    if(buffer->vertexCount == 0) return;

    /**
     * use shader program and set all variables
     */
    if(Graphics3D::objectShader != NULL) {
        //use shader
        Graphics3D::objectShader->use();

        //<--------------Vertex-Shader--------------------------------------------------------------->
        glm::mat4 modelView;
        glGetFloatv(GL_MODELVIEW_MATRIX, glm::value_ptr(modelView));
        glm::mat4 MVP = Graphics3D::projectionMatrix * modelView;

        /**
         * model view projection matrix
         */
        Graphics3D::objectShader->setMatrix4(MODEL_VIEW_PROJECTION_MATRIX_UNIFORM,
                                             glm::value_ptr(MVP));

        /**
         * model matrix
         */
        if(modelTransformMatrix != NULL) {
            Graphics3D::objectShader->setMatrix4(MODEL_MATRIX_UNIFORM,
                                                 modelTransformMatrix);
        }
        //<------------------------------------------------------------------------------------------->

        //<---------------Fragment-Shader------------------------------------------------------------->
        //default color of surface
        if(Graphics3D::texture == NULL) {
            Graphics3D::objectShader->setVec4(
                        COLOR_UNIFORM,
                        Graphics::color.red,
                        Graphics::color.green,
                        Graphics::color.blue,
                        MIN(Graphics::color.alpha, Graphics::maxAlpha));
        } else {
            Graphics3D::objectShader->setVec4(
                        COLOR_UNIFORM,
                        0.0, 0.0 ,0.0, 0.0);
        }

        //lights
        if(lights != NULL) {
            if(lights->size() > 0) {
                Light * l = (*lights)[0];
                if(l != NULL) {
                    //set position of light
                    Graphics3D::objectShader->setVec3(
                                LIGHT_POSITION_UNIFORM, l->position.x, l->position.y, l->position.z);
                    //set color of light
                    Graphics3D::objectShader->setVec3(
                                LIGHT_COLOR_UNIFORM, l->color.red, l->color.green, l->color.blue);
                    //set position of camera
                    Graphics3D::objectShader->setVec3(
                                VIEW_POSITION_UNIFORM,
                                Graphics::currentRenderEvt.x,
                                Graphics::currentRenderEvt.y,
                                Graphics::currentRenderEvt.z);
                }
            }
        }
        //<------------------------------------------------------------------------------------------->
    }

    //upload position data to VBO
    glBindBuffer(GL_ARRAY_BUFFER, Graphics3D::VBO_position);
    glBufferData(GL_ARRAY_BUFFER, buffer->vertexCount * sizeof(GLfloat) * 3,
                 buffer->getPositionData(), GL_DYNAMIC_DRAW);

    //upload normal data to VBO
    glBindBuffer(GL_ARRAY_BUFFER, Graphics3D::VBO_normal);
    glBufferData(GL_ARRAY_BUFFER, buffer->vertexCount * sizeof(GLfloat) * 3,
                 buffer->getNormalData(), GL_DYNAMIC_DRAW);

    //upload UV data to VBO
    glBindBuffer(GL_ARRAY_BUFFER, Graphics3D::VBO_UV);
    glBufferData(GL_ARRAY_BUFFER, buffer->vertexCount * sizeof(GLfloat) * 2,
                 buffer->getUVData(), GL_DYNAMIC_DRAW);

    //draw the triangles
    glBindVertexArray(Graphics3D::VAO_object);
    glDrawArrays(GL_TRIANGLES, 0, buffer->vertexCount);

    //unbind current vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    //stop using current shader program
    glUseProgram(0);
}


void Graphics3D::setShaderProgram(ShaderProgram * shaderProgram, ShaderType type) {
    switch (type) {
    case OBJECT_SHADER:
        if(Graphics3D::objectShader) delete Graphics3D::objectShader;
        Graphics3D::objectShader = shaderProgram;
        break;
    case SKYBOX_SHADER:
        if(Graphics3D::skyboxShader) delete Graphics3D::skyboxShader;
        Graphics3D::skyboxShader = shaderProgram;
        break;
    case IMG_SHADER:
        if(Graphics3D::imageShader) delete Graphics3D::imageShader;
        Graphics3D::imageShader = shaderProgram;
        break;
    }
}


void Graphics3D::setDefaultShaderProgram(ShaderType type) {
    if(type == ShaderType::OBJECT_SHADER || type == ShaderType::ALL) {
        Graphics3D::objectShader = new ShaderProgram();
        Graphics3D::objectShader->addShader(SHADER_OBJ_VERTEX, GL_VERTEX_SHADER);
        Graphics3D::objectShader->addShader(SHADER_OBJ_FRAGMENT, GL_FRAGMENT_SHADER);
        Graphics3D::objectShader->link();
    }

    if(type == ShaderType::SKYBOX_SHADER || type == ShaderType::ALL) {
        Graphics3D::skyboxShader = new ShaderProgram();
        Graphics3D::skyboxShader->addShader(SHADER_SKY_VERTEX, GL_VERTEX_SHADER);
        Graphics3D::skyboxShader->addShader(SHADER_SKY_FRAGMENT, GL_FRAGMENT_SHADER);
        Graphics3D::skyboxShader->link();
    }

    if(type == ShaderType::IMG_SHADER || type == ShaderType::ALL) {
        Graphics3D::imageShader = new ShaderProgram();
        Graphics3D::imageShader->addShader(SHADER_IMG_VERTEX, GL_VERTEX_SHADER);
        Graphics3D::imageShader->addShader(SHADER_IMG_FRAGMENT, GL_FRAGMENT_SHADER);
        Graphics3D::imageShader->link();
    }
}


ShaderProgram * Graphics3D::getShaderProgram(int type) {
    switch (type) {
    case OBJECT_SHADER:
        return Graphics3D::objectShader;
        break;
    case SKYBOX_SHADER:
        return Graphics3D::skyboxShader;
        break;
    case IMG_SHADER:
        return Graphics3D::imageShader;
        break;
    default:
        return NULL;
    }
}


void Graphics3D::setTexture(Texture * texture) {
    Graphics3D::texture = texture;

    if(texture != NULL) {
        glBindTexture(GL_TEXTURE_2D, texture->getID());
        glEnable(GL_TEXTURE_2D);
    } else {
        glDisable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}


void Graphics3D::drawLine(Vertex3 v1, Vertex3 v2) {
    glBegin(GL_LINE);

    glVertex3f(v1.x, v1.y, v1.z);
    glVertex3f(v2.x, v2.y, v2.z);

    glEnd();
}


void Graphics3D::drawLines(std::vector<Vertex3> vertices) {
    glBegin(GL_LINES);

    for(Vertex3 v : vertices) {
        glVertex3f(v.x, v.y, v.z);
    }

    glEnd();
}


void Graphics3D::drawTriangle(Triangle3 t) {
    glBegin(GL_LINE_LOOP);

    glVertex3f(t.v[0]->x, t.v[0]->y,
            t.v[0]->z);

    glVertex3f(t.v[1]->x, t.v[1]->y,
            t.v[1]->z);

    glVertex3f(t.v[2]->x, t.v[2]->y,
            t.v[2]->z);

    glEnd();
}


void Graphics3D::drawTriangles(std::vector<Triangle3> & triangles) {
    for(Triangle3 t : triangles) {
        glBegin(GL_LINE_LOOP);

        glVertex3f(t.v[0]->x, t.v[0]->y,
                t.v[0]->z);

        glVertex3f(t.v[1]->x, t.v[1]->y,
                t.v[1]->z);

        glVertex3f(t.v[2]->x, t.v[2]->y,
                t.v[2]->z);

        glEnd();
    }
}


void Graphics3D::drawCube(Vertex3 position, Vertex3 rotation, GLfloat size) {
    glPushMatrix();

    glTranslatef(position.x, position.y, position.z);
    glRotatef(rotation.x, 1.0, 0.0, 0.0);
    glRotatef(rotation.y, 0.0, 1.0, 0.0);
    glRotatef(rotation.z, 0.0, 0.0, 1.0);

    glBegin(GL_LINE_LOOP);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, size);
    glVertex3f(size, 0.0, size);
    glVertex3f(size, 0.0, 0.0);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glVertex3f(0.0, size, 0.0);
    glVertex3f(0.0, size, size);
    glVertex3f(size, size, size);
    glVertex3f(size, size, 0.0);
    glEnd();

    glBegin(GL_LINES);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, size, 0.0);

    glVertex3f(0.0, 0.0, size);
    glVertex3f(0.0, size, size);

    glVertex3f(size, 0.0, size);
    glVertex3f(size, size, size);

    glVertex3f(size, 0.0, 0.0);
    glVertex3f(size, size, 0.0);
    glEnd();

    glPopMatrix();
}


void Graphics3D::fillTriangle(Triangle3 t) {
    glBegin(GL_TRIANGLES);
    glVertex3f(t.v[0]->x, t.v[0]->y,
            t.v[0]->z);

    glVertex3f(t.v[1]->x, t.v[1]->y,
            t.v[1]->z);

    glVertex3f(t.v[2]->x, t.v[2]->y,
            t.v[2]->z);
    glEnd();
}


void Graphics3D::fillTriangles(std::vector<Triangle3> & triangles) {
    glBegin(GL_TRIANGLES);
    for(Triangle3 t : triangles) {
        glVertex3f(t.v[0]->x, t.v[0]->y,
                t.v[0]->z);

        glVertex3f(t.v[1]->x, t.v[1]->y,
                t.v[1]->z);

        glVertex3f(t.v[2]->x, t.v[2]->y,
                t.v[2]->z);
    }
    glEnd();
}


void Graphics3D::fillPlane(Vertex3 position, Vertex3 rotation, size_t width, size_t height) {
    glPushMatrix();

    glTranslatef(position.x, position.y, position.z);
    glRotatef(rotation.x, 1.0, 0.0, 0.0);
    glRotatef(rotation.y, 0.0, 1.0, 0.0);
    glRotatef(rotation.z, 0.0, 0.0, 1.0);

    glBegin(GL_QUADS);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, width);
    glVertex3f(height, 0.0, width);
    glVertex3f(height, 0.0, 0.0);
    glEnd();

    glPopMatrix();
}


void Graphics3D::fillCube(Vertex3 position, Vertex3 rotation, GLfloat size) {
    glPushMatrix();

    glTranslatef(position.x, position.y, position.z);
    glRotatef(rotation.x, 1.0, 0.0, 0.0);
    glRotatef(rotation.y, 0.0, 1.0, 0.0);
    glRotatef(rotation.z, 0.0, 0.0, 1.0);

    glBegin(GL_QUADS);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, size);
    glVertex3f(size, 0.0, size);
    glVertex3f(size, 0.0, 0.0);

    glVertex3f(0.0, size, 0.0);
    glVertex3f(0.0, size, size);
    glVertex3f(size, size, size);
    glVertex3f(size, size, 0.0);

    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, size);
    glVertex3f(0.0, size, size);
    glVertex3f(0.0, size, 0.0);

    glVertex3f(size, 0.0, 0.0);
    glVertex3f(size, 0.0, size);
    glVertex3f(size, size, size);
    glVertex3f(size, size, 0.0);

    glVertex3f(0.0, 0.0, size);
    glVertex3f(size, 0.0, size);
    glVertex3f(size, size, size);
    glVertex3f(0.0, size, size);

    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(size, 0.0, 0.0);
    glVertex3f(size, size, 0.0);
    glVertex3f(0.0, size, 0.0);
    glEnd();


    glPopMatrix();
}


void Graphics3D::drawImage(Vertex3 position, Vertex3 rotation,
                           Texture * texture, size_t width, size_t height) {
    if(texture != NULL) {
        glPushMatrix();

        glTranslatef(position.x, position.y, position.z);
        glRotatef(rotation.x, 1.0, 0.0, 0.0);
        glRotatef(rotation.y, 0.0, 1.0, 0.0);
        glRotatef(rotation.z, 0.0, 0.0, 1.0);

        glColor4f(1.0, 1.0, 1.0, MIN(1.0, Graphics::maxAlpha));
        glBindTexture(GL_TEXTURE_2D, texture->getID());
        glEnable(GL_TEXTURE_2D);

        glBegin(GL_QUADS);
        glTexCoord2i(0, 1);
        glVertex3f(0.0, height, 0.0);
        glTexCoord2i(0, 0);
        glVertex3f(0.0, 0.0, 0.0);
        glTexCoord2i(1, 0);
        glVertex3f(width, 0.0, 0.0);
        glTexCoord2i(1, 1);
        glVertex3f(width, height, 0.0);
        glEnd();

        glDisable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);

        glPopMatrix();
    }
}


static float skyboxVertices[] = {
    -1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f,  1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

    -1.0f,  1.0f, -1.0f,
    1.0f,  1.0f, -1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
    1.0f, -1.0f,  1.0f
};

void Graphics3D::drawSkybox(Vertex3 origin, GLfloat scale, GLint textureID) {

    glPushMatrix();

    //transformation
    glTranslatef(origin.x, origin.y, origin.z);
    glScalef(scale, scale, scale);

    if(Graphics3D::skyboxShader != NULL) {
        Graphics3D::skyboxShader->use();

        //<--------------Vertex-Shader--------------------------------------------------------------->
        glm::mat4 modelView;
        glGetFloatv(GL_MODELVIEW_MATRIX, glm::value_ptr(modelView));
        glm::mat4 MVP = Graphics3D::projectionMatrix * modelView;

        /**
         * model view projection matrix
         */
        Graphics3D::objectShader->setMatrix4(MODEL_VIEW_PROJECTION_MATRIX_UNIFORM,
                                             glm::value_ptr(MVP));
        //<------------------------------------------------------------------------------------------->
    }

    //glBindVertexArray(skyboxVAO);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
    glDepthMask(GL_FALSE);


    //bind VBO
    glBindBuffer(GL_ARRAY_BUFFER, Graphics3D::VBO_position);
    //upload vertex data to the video device
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices),
                 skyboxVertices, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //draw the triangles
    glBindVertexArray(Graphics3D::VAO_skybox);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    //unbind current vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    //stop using current shader program
    glUseProgram(0);


    glDepthMask(GL_TRUE);
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

    glPopMatrix();
}

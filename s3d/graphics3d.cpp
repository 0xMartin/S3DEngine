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


#include <string.h>
#include <cstdarg>
#include <GLES3/gl3.h>


/*--------------------------------Default-Shaders-------------------------------------------------*/

static const char * vertex_src = R"glsl(
    #version 330 core

    layout(location = 0) in vec3 aPosition;
    layout(location = 1) in vec3 aNormal;
    layout(location = 2) in vec2 aUV;

    out vec2 UV;
    out vec3 Normal;
    out vec3 FragPos;

    uniform mat4 MVP;
    uniform mat4 M;

    void main(){
        gl_Position = MVP * vec4(aPosition, 1.0);
        UV = aUV;
        Normal = aNormal;
        FragPos = vec3(M * vec4(aPosition, 1.0));
    }
)glsl";

static const char * fragment_src = R"glsl(
    #version 330 core

    in vec2 UV;
    in vec3 Normal;
    in vec3 FragPos;

    out vec4 FragColor;

    //lights
    uniform vec3 lightPos;
    uniform vec3 lightColor;
    uniform vec3 viewPos;

    //object surface (texture or color)
    uniform vec3 Color;
    uniform sampler2D objTexture;

    void main(){
        vec3 objectColor = Color;
        objectColor += texture(objTexture, UV).rgb;

        vec3 norm = normalize(Normal);
        vec3 lightDir = normalize(lightPos - FragPos);

        vec3 viewDir = normalize(viewPos - FragPos);
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
        vec3 specular = 0.5 * spec * lightColor;

        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = diff * lightColor;

        vec3 ambient = 0.01 * lightColor;
        vec3 result = (ambient + diffuse + specular) * objectColor;
        FragColor = vec4(result, 1.0);
    }
)glsl";

/*------------------------------------------------------------------------------------------------*/


/*--------------------------------ModelDataBuffer-------------------------------------------------*/
VertexDataBuffer::VertexDataBuffer(VBOType type) {
    VertexDataBuffer::type = type;
    VertexDataBuffer::size = 0;
    VertexDataBuffer::data = NULL;
}

VertexDataBuffer::~VertexDataBuffer() {
    if(VertexDataBuffer::data) free(VertexDataBuffer::data);
}

bool VertexDataBuffer::buildVertexData(std::vector<Triangle3> & triangles, VBOType type) {

    //set type of  buffer
    VertexDataBuffer::type = type;

    //size
    size_t size = sizeof(GLfloat) * triangles.size() * 3 * 8;

    //allocate data array
    if(VertexDataBuffer::data == NULL) {
        VertexDataBuffer::data = (GLfloat*) malloc(size);
    } else if(VertexDataBuffer::size < size ||
              VertexDataBuffer::size/2 > size) {
        //realloc only if is not enought space or new size is 2 times lower
        VertexDataBuffer::data = (GLfloat*) realloc(VertexDataBuffer::data, size);
    }
    if(VertexDataBuffer::data == NULL) return false;

    //load all data to buffer
    unsigned int offset = 0;
    unsigned int i;
    for(Triangle3 t : triangles) {
        for(i = 0; i < 3; ++i) {
            //position
            VertexDataBuffer::data[offset] = t.v[i]->x;
            VertexDataBuffer::data[offset + 1] = t.v[i]->y;
            VertexDataBuffer::data[offset + 2] = t.v[i]->z;

            //normals
            VertexDataBuffer::data[offset + 3] = t.vn[i]->x;
            VertexDataBuffer::data[offset + 4] = t.vn[i]->y;
            VertexDataBuffer::data[offset + 5] = t.vn[i]->y;

            //texture coord
            VertexDataBuffer::data[offset + 6] = t.vt[i]->x;
            VertexDataBuffer::data[offset + 7] = t.vt[i]->y;

            offset += 8;
        }
    }

    //set size (number of vertices)
    VertexDataBuffer::size = triangles.size() * 3;

    return true;
}
/*------------------------------------------------------------------------------------------------*/



Graphics3D::Graphics3D(int windowHandle) : Graphics2D(windowHandle) {   
    //vertex buffer (for texture)
    glGenBuffers(1, &(Graphics3D::vertexBuffer));

    glBindBuffer(GL_ARRAY_BUFFER, Graphics3D::vertexBuffer);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat),
                          (GLvoid*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat),
                          (GLvoid*)(3 * sizeof(GLfloat)));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat),
                          (GLvoid*)(6 * sizeof(GLfloat)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);


    //default shader program
    Graphics3D::defaultShader = new ShaderProgram();
    Graphics3D::defaultShader->addShader(vertex_src, GL_VERTEX_SHADER);
    Graphics3D::defaultShader->addShader(fragment_src, GL_FRAGMENT_SHADER);
    Graphics3D::defaultShader->link();

    //set shader program
    Graphics3D::setDefaultShaderProgram();

    Graphics3D::computeProjectionMatrix(45.0, 2.0, 0.1, 100.0);
}

Graphics3D::~Graphics3D() {
    glDeleteBuffers(1, &(Graphics3D::vertexBuffer));

    delete Graphics3D::defaultShader;
}

void Graphics3D::computeProjectionMatrix(GLdouble FOV, GLdouble aspect,
                                         GLdouble zNear, GLdouble zFar) {
    gluPerspective(FOV, aspect, zNear, zFar);

    GLfloat buffer[16];
    glGetFloatv(GL_PROJECTION_MATRIX, buffer);
    Graphics3D::projection = glm::make_mat4(buffer);
}

void Graphics3D::bindLightVector(std::vector<Light*> * lights) {
    Graphics3D::lights = lights;
}

void Graphics3D::drawTriangle(Triangle3 * t) {
    glBegin(GL_LINE_LOOP);

    glVertex3f(t->v[0]->x, t->v[0]->y,
            t->v[0]->z);

    glVertex3f(t->v[1]->x, t->v[1]->y,
            t->v[1]->z);

    glVertex3f(t->v[2]->x, t->v[2]->y,
            t->v[2]->z);

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

void Graphics3D::fillTriangle(Triangle3 * t) {
    glBegin(GL_TRIANGLES);

    glVertex3f(t->v[0]->x, t->v[0]->y,
            t->v[0]->z);

    glVertex3f(t->v[1]->x, t->v[1]->y,
            t->v[1]->z);

    glVertex3f(t->v[2]->x, t->v[2]->y,
            t->v[2]->z);

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

void Graphics3D::drawFaces(std::vector<Face3> & faces) {   
    for(Face3 & f : faces) {
        glBegin(GL_LINE_LOOP);
        for(Vertex3 * v : f.v) {
            glVertex3f(v->x, v->y, v->z);
        }
        glEnd();
    }
}

void Graphics3D::fillFaces(std::vector<Face3> & faces) {
    glBegin(GL_POLYGON);
    for(Face3 & f : faces) {
        for(Vertex3 * v : f.v) {
            glVertex3f(v->x, v->y, v->z);
        }
    }
    glEnd();
}

void Graphics3D::drawImage(Vertex3 * position, Vertex3 * rotation,
                           Texture * texture, size_t width, size_t height) {
    if(position != NULL && position!= NULL && texture != NULL) {
        glPushMatrix();

        glTranslatef(position->x, position->y, position->z);
        glRotatef(rotation->x, 1.0, 0.0, 0.0);
        glRotatef(rotation->y, 0.0, 1.0, 0.0);
        glRotatef(rotation->z, 0.0, 0.0, 1.0);

        glColor4f(1.0, 1.0, 1.0, Graphics::color.alpha);
        glBindTexture(GL_TEXTURE_2D, texture->textureID);
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

void Graphics3D::drawVertexDataBuffer(VertexDataBuffer * buffer, GLfloat * modelTransformMatrix) {
    if(buffer == NULL) return;
    if(buffer->size == 0 || buffer->data == NULL) return;

    /**
     * use shader program and set all variables
     */
    if(Graphics3D::shaderProgram != NULL) {
        //use
        Graphics3D::shaderProgram->use();

        //<--------------Vertex-Shader--------------------------------------------------------------->
        glm::mat4 modelView;
        glGetFloatv(GL_MODELVIEW_MATRIX, glm::value_ptr(modelView));
        glm::mat4 MVP = Graphics3D::projection * modelView;

        /**
         * model view projection matrix
         */
        Graphics3D::shaderProgram->setMatrix4(MODEL_VIEW_PROJECTION_MATRIX_UNIFORM,
                                              glm::value_ptr(MVP));

        /**
         * model matrix
         */
        if(modelTransformMatrix != NULL) {
            Graphics3D::shaderProgram->setMatrix4(MODEL_MATRIX_UNIFORM,
                                                  modelTransformMatrix);
        }
        //<------------------------------------------------------------------------------------------->

        //<---------------Fragment-Shader------------------------------------------------------------->
        //default color
        switch (buffer->type) {
        case VBO_Color:
            Graphics3D::shaderProgram->setVec3(
                        COLOR_UNIFORM,
                        Graphics::color.red,
                        Graphics::color.green,
                        Graphics::color.blue);
            break;
        case VBO_Texture:
            Graphics3D::shaderProgram->setVec3(
                        COLOR_UNIFORM,
                        0.0, 0.0 ,0.0);
            break;
        }

        //lights
        if(lights != NULL) {
            if(lights->size() > 0) {
                Light * l = (*lights)[0];
                if(l != NULL) {
                    //set position of light
                    Graphics3D::shaderProgram->setVec3(
                                LIGHT_POSITION_UNIFORM, l->position.x, l->position.y, l->position.z);
                    //set color of light
                    Graphics3D::shaderProgram->setVec3(
                                LIGHT_COLOR_UNIFORM, l->color.red, l->color.green, l->color.blue);
                    //set position of camera
                    Graphics3D::shaderProgram->setVec3(
                                VIEW_POSITION_UNIFORM,
                                Graphics::currentRenderEvt.x,
                                Graphics::currentRenderEvt.y,
                                Graphics::currentRenderEvt.z);
                }
            }
        }
        //<------------------------------------------------------------------------------------------->
    }

    //bind vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, Graphics3D::vertexBuffer);
    //upload vertex data to the video device
    glBufferData(GL_ARRAY_BUFFER, buffer->size * sizeof(GLfloat) * 8,
                 buffer->data, GL_DYNAMIC_DRAW);
    //actually draw the triangle, giving the number of vertices provided
    glDrawArrays(GL_TRIANGLES, 0, buffer->size);

    //unbind current vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    //stop using current shader program
    glUseProgram(0);
}

void Graphics3D::setShaderProgram(ShaderProgram * shaderProgram) {
    Graphics3D::shaderProgram = shaderProgram;
}

void Graphics3D::setDefaultShaderProgram() {
    Graphics3D::shaderProgram = defaultShader;
}

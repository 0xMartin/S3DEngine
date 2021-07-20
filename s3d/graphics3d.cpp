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


#include <GLES3/gl3.h>


/*------------------------------------FloatBuffer-------------------------------------------------*/
FloatBuffer::FloatBuffer() {
    FloatBuffer::size = 0;
    FloatBuffer::vertices = NULL;
    FloatBuffer::normals = NULL;
    FloatBuffer::textureCoords = NULL;
}

FloatBuffer::~FloatBuffer() {
    if(FloatBuffer::vertices) free(FloatBuffer::vertices);
    if(FloatBuffer::normals) free(FloatBuffer::normals);
    if(FloatBuffer::textureCoords) free(FloatBuffer::textureCoords);
}

bool FloatBuffer::convertTrianglesToArray(std::vector<Triangle3> & triangles) {
    FloatBuffer::size = 0;

    //vertex array
    if(FloatBuffer::vertices == NULL) {
        FloatBuffer::vertices = (GLfloat*) malloc(sizeof(GLfloat) * 9 * triangles.size());
    } else {
        FloatBuffer::vertices = (GLfloat*) realloc(FloatBuffer::vertices,
                                                   sizeof(GLfloat) * 9 * triangles.size());
    }
    if(FloatBuffer::vertices == NULL) {
        return false;
    }

    //normal array
    if(FloatBuffer::normals == NULL) {
        FloatBuffer::normals = (GLfloat*) malloc(sizeof(GLfloat) * 9 * triangles.size());
    } else {
        FloatBuffer::normals = (GLfloat*) realloc(FloatBuffer::normals,
                                                  sizeof(GLfloat) * 9 * triangles.size());
    }
    if(FloatBuffer::normals == NULL) {
        return false;
    }

    //texture coords array
    if(FloatBuffer::textureCoords == NULL) {
        FloatBuffer::textureCoords = (GLfloat*) malloc(sizeof(GLfloat) * 6 * triangles.size());
    } else {
        FloatBuffer::textureCoords = (GLfloat*) realloc(FloatBuffer::textureCoords,
                                                        sizeof(GLfloat) * 6 * triangles.size());
    }
    if(FloatBuffer::textureCoords == NULL) {
        return false;
    }

    unsigned int i;
    unsigned int size3 = 0;
    unsigned int size2 = 0;
    for(Triangle3 t : triangles) {
        for(i = 0; i < 3; ++i) {
            FloatBuffer::vertices[size3] = t.v[i]->x;
            FloatBuffer::vertices[size3 + 1] = t.v[i]->y;
            FloatBuffer::vertices[size3 + 2] = t.v[i]->z;

            FloatBuffer::normals[size3] = t.vn[i]->x;
            FloatBuffer::normals[size3 + 1] = t.vn[i]->y;
            FloatBuffer::normals[size3 + 2] = t.vn[i]->z;

            FloatBuffer::textureCoords[size2] = t.vt[i]->x;
            FloatBuffer::textureCoords[size2 + 1] = t.vt[i]->y;

            ++FloatBuffer::size;
            size3 += 3;
            size2 += 2;
        }
    }

    return true;
}
/*------------------------------------------------------------------------------------------------*/


Graphics3D::Graphics3D(int windowHandle) : Graphics2D(windowHandle) {   
    //vertex buffer
    glGenBuffers(1, &(Graphics3D::vertexBuffer));
    glBindBuffer(GL_ARRAY_BUFFER, Graphics3D::vertexBuffer);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, NULL);

    //normal buffer
    glGenBuffers(1, &(Graphics3D::normalBuffer));
    glBindBuffer(GL_ARRAY_BUFFER, Graphics3D::normalBuffer);
    glEnableClientState(GL_NORMAL_ARRAY);
    glNormalPointer(GL_FLOAT, 0, NULL);

    //texture coord
    glGenBuffers(1, &(Graphics3D::textureCoordBuffer));
    glBindBuffer(GL_ARRAY_BUFFER, Graphics3D::textureCoordBuffer);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glTexCoordPointer(2, GL_FLOAT, 0, NULL);
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

void Graphics3D::drawFloatBuffer(FloatBuffer * buffer) {
    if(buffer->size == 0) return;

    /**
     * draw vertices
     */
    if(buffer->vertices != NULL) {
        //bind vertex buffer
        glBindBuffer(GL_ARRAY_BUFFER, Graphics3D::vertexBuffer);

        //upload vertex data to the video device
        glBufferData(GL_ARRAY_BUFFER, buffer->size * sizeof(GLfloat) * 3,
                     buffer->vertices, GL_DYNAMIC_DRAW);

        //actually draw the triangle, giving the number of vertices provided
        glDrawArrays(GL_TRIANGLES, 0, buffer->size);
    }

}

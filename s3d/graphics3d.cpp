#include "graphics3d.h"

Graphics3D::Graphics3D(int windowHandle) : Graphics2D(windowHandle) {

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
    for(Face3 f : faces) {
        glBegin(GL_LINE_LOOP);
        for(Vertex3 * v : f.v) {
            glVertex3f(v->x, v->y, v->z);
        }
        glEnd();
    }
}

void Graphics3D::fillFaces(std::vector<Face3> & faces) {
    glBegin(GL_POLYGON);
    for(Face3 f : faces) {
        for(Vertex3 * v : f.v) {
            glVertex3f(v->x, v->y, v->z);
        }
    }
    glEnd();
}

void Graphics3D::drawImage(Vertex3 * p, Texture * texture, bool defaultShape) {
    if(p != NULL) {
        glColor4f(1.0, 1.0, 1.0, Graphics::color.alpha);
        glBindTexture(GL_TEXTURE_3D, texture->textureID);
        glEnable(GL_TEXTURE_3D);
        glBegin(GL_QUADS);

        if(defaultShape) {
            glTexCoord3i(0, 0, 0);
            glVertex3f(p->x, p->y + texture->height, p->z);

            glTexCoord3i(0, 1, 0);
            glVertex3f(p->x, p->y, p->z);

            glTexCoord3i(1, 1, 0);
            glVertex3f(p->x + texture->width, p->y, p->z);

            glTexCoord3i(1, 0, 0);
            glVertex3f(p->x + texture->width, p->y + texture->height, p->z);
        } else {
            for(unsigned int i = 0; i < 4; ++i) {
                glTexCoord2i(i > 1, i > 0 && i < 3);
                glVertex3f((p + i)->x, (p + i)->y, (p + i)->z);
            }
        }

        glEnd();
        glDisable(GL_TEXTURE_3D);
        glBindTexture(GL_TEXTURE_3D, 0);
    }
}

#ifndef GRAPHICS3D_H
#define GRAPHICS3D_H

#include "graphics2d.h"


typedef struct {
    GLfloat x; /** X position*/
    GLfloat y; /** Y position*/
    GLfloat z; /** Z position*/
} Vertex;

typedef struct {
    Vertex * vetices;
    size_t count;
    GLint textureID;
} Face3D;


class Graphics3D : public Graphics2D {
public:
    Graphics3D(int windowHandle);
};

#endif // GRAPHICS3D_H

#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include "graphics3d.h"

class Model
{
protected:
    std::vector<Vertex3> vertices;  /** vertices */
    std::vector<Point> texture_coordinates; /** texture coordinates */
    std::vector<Vertex3> normals; /** normals */
    std::vector<Triangle3> triangles;
public:
    Vertex3 offset;
    Vertex3 rotation;

    Model(const char * path);
    ~Model();

    bool loadModel(const char * path);

    void render(Graphics * graphics);
};

#endif // MODEL_H

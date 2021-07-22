/******************************************************************************
 * S3D Engine
 *
 * @file       model.h
 * @brief      XXXX Function
 *
 * @author     Martin Krcma
 * @date       2021/07/20
 *****************************************************************************/

#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include "graphics3d.h"

class Model
{
protected:
    //data model buffer with model data (use for rendering)
    VertexDataBuffer * buffer; /** buffer with vertices */

    Texture * texture; /** texture of model */

    std::vector<Vertex3> vertices;  /** vertices */
    std::vector<Point> texture_coordinates; /** texture coordinates */
    std::vector<Vertex3> normals; /** normals */
    std::vector<Triangle3> triangles;
public:
    Vertex3 offset;
    Vertex3 rotation;

    Model(const char * path);
    ~Model();

    /**
     * @brief loadModel
     * @param path
     * @return
     */
    bool loadModel(const char * path);

    /**
     * @brief setTexture
     * @param texture
     */
    void setTexture(Texture * texture);

    /**
     * @brief render
     * @param graphics
     */
    void render(Graphics * graphics);

    /**
     * @brief recomputeFloatBuffer
     * @return
     */
    bool recomputeFloatBuffer();
};

#endif // MODEL_H

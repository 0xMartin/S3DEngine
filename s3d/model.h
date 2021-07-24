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
private:
    void computeTransformationModelMatrix();

protected:
    //data model buffer with model data (use for rendering)
    VertexDataBuffer * buffer; /** buffer with vertices */

    Texture * texture; /** texture of model */

    //model transformation atributes
    Vertex3 offset;
    Vertex3 rotation;
    Vertex3 scale;

    //transformation matrix
    glm::mat4 translateMatrix;
    glm::mat4 rotateMatrix;
    glm::mat4 scaleMatrix;

    glm::mat4 modelTransformationMatrix;

public:
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
     * @brief setOffset
     * @param pos
     */
    void setOffset(Vertex3 pos);

    /**
     * @brief setRotation
     * @param pos
     */
    void setRotation(Vertex3 rotation);

    /**
     * @brief setScale
     * @param pos
     */
    void setScale(Vertex3 scale);

    /**
     * @brief getModelTranformationMatrix
     * @return
     */
    GLfloat * getModelTranformationMatrix();
};

#endif // MODEL_H

/***************************************************************************
 *
 *  File:       model.h
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

#ifndef MODEL_H
#define MODEL_H

#include "api.h"

#include <vector>
#include "graphics3d.h"

class S3D_EXPORT Model
{
private:
    void computeTransformationModelMatrix();

protected:
    //data model buffer with model data (use for rendering)
    VertexDataBuffer buffer; /** buffer with vertices */

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

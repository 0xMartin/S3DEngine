/***************************************************************************
 *
 *  File:       camera.h
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

#ifndef CAMERA_H
#define CAMERA_H

#include "api.h"
#include "graphics3d.h"
#include <stdbool.h>


/**
 * @brief The Camera class
 */
class S3D_EXPORT Camera
{
private:
    float angleXZ, angleY;  /** angle of rotation for the camera direction*/
    Vertex3 dir; /** actual vector representing the camera's direction*/
    Vertex3 pos; /** XYZ position of the camera*/
    Range<float> limitAngleY; /** camera angle limit*/
    float cosAY;    /** cos(angleY) for camera direcion*/

public:
    float deltaAngleXZ, deltaAngleY;    /** control angle*/
    Vertex3 deltaPos;    /** control position*/
    float speed;

    Camera();


    /**
     * @brief CAMERA_computePosition    Compute new X, Y, Z position of
     * camera for straight move -> Control variable: cam.deltaPos
     * @param cam   Camera
     */
    void computePosition();

    /**
     * @brief CAMERA_computeDirection   Update new value of vector representing
     * the camera's direction -> Control variable: cam.deltaAngle
     * @param cam   Camera
     */
    void computeDirection();

    /**
     * @brief CAMERA_viewTransformation Apply camera view transformation
     * @param cam   Camera
     */
    void viewTransformation();

    /**
     * @brief getPosition
     * @return
     */
    Vertex3 getPosition();

    /**
     * @brief setPosition
     * @param v
     */
    void setPosition(Vertex3 * v);

    /**
     * @brief setPosition
     * @param x
     * @param y
     * @param z
     */
    void setPosition(GLfloat x, GLfloat y, GLfloat z);

    /**
     * @brief getDirection
     * @return
     */
    Vertex3 getDirection();

    /**
     * @brief setLimitOfYAngle
     * @param min
     * @param max
     */
    void setLimitOfYAngle(float min, float max);
};


#endif // CAMERA_H

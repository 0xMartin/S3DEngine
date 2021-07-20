/******************************************************************************
 * S3D Engine
 *
 * @file       camera.h
 * @brief      XXXX Function
 *
 * @author     Martin Krcma
 * @date       2021/07/20
 *****************************************************************************/

#ifndef CAMERA_H
#define CAMERA_H

#include "graphics3d.h"
#include <stdbool.h>


class Camera
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

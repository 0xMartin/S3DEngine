#ifndef CAMERA_H
#define CAMERA_H

#include "graphics3d.h"
#include <stdbool.h>


class Camera
{
private:
    float angleXZ, angleY;  /** angle of rotation for the camera direction*/
    Vertex dir; /** actual vector representing the camera's direction*/
    Vertex pos; /** XYZ position of the camera*/
    Range<float> limitAngleY; /** camera angle limit*/
    float cosAY;    /** cos(angleY) for camera direcion*/

public:
    float deltaAngleXZ, deltaAngleY;    /** control angle*/
    Vertex deltaPos;    /** control position*/

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
    Vertex getPosition();

    /**
     * @brief getDirection
     * @return
     */
    Vertex getDirection();

    /**
     * @brief setLimitOfYAngle
     * @param min
     * @param max
     */
    void setLimitOfYAngle(float min, float max);
};


#endif // CAMERA_H

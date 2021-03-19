/**
 * <------------------------------------------------------------------>
 * @name    2D Engine
 * @author  Martin Krcma
 * @date    19. 3. 2021
 * <------------------------------------------------------------------>
 * @file    camera.h
 * @brief   Engine camera
 * <------------------------------------------------------------------>
 */

#ifndef CAMERA_H
#define CAMERA_H

#include "render.h"

#include <stdbool.h>

#define CAMERA_DIR_Y_RANGE 1.5

#define CAMERA_INIT {\
    0.0f, 0.0f,\
    {0.0f, 0.0f, 1.0f},\
    Z_VERTEX,\
    0.0f, 0.0f,\
    Z_VERTEX,\
    {-CAMERA_DIR_Y_RANGE, CAMERA_DIR_Y_RANGE},\
    0.0f\
    }


typedef struct {
    float min;
    float max;
} FRange;

/**
  * Enigne camera structure
  */
typedef struct {
    // angle of rotation for the camera direction
    float angleXZ, angleY;

    // actual vector representing the camera's direction
    Vertex dir;

    // XYZ position of the camera
    Vertex pos;

    //control angle
    float deltaAngleXZ, deltaAngleY;

    //control position
    Vertex deltaPos;

    //camera angle limit
    FRange limitAngleY;

    //cos(angleY) for camera direcion
    float cosAY;
} Camera;


/**
 * @brief CAMERA_computePosition    Compute new X, Y, Z position of
 * camera for straight move -> Control variable: cam.deltaPos
 * @param cam   Camera
 * @return TRUE (no error) / FALSE (something go wrong)
 */
bool Camera_computePosition(
        Camera * cam
        );

/**
 * @brief CAMERA_computeDirection   Update new value of vector representing
 * the camera's direction -> Control variable: cam.deltaAngle
 * @param cam   Camera
 * @return TRUE (no error) / FALSE (something go wrong)
 */
bool Camera_computeDirection(
        Camera * cam
        );

/**
 * @brief CAMERA_viewTransformation Apply camera view transformation
 * @param cam   Camera
 * @return TRUE (no error) / FALSE (something go wrong)
 */
bool Camera_viewTransformation(
        Camera * cam
        );

#endif // CAMERA_H

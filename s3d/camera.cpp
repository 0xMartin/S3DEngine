/***************************************************************************
 *
 *  File:       camera.cpp
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

#include "camera.h"


#include "util.h"
#include <math.h>


#define CAMERA_DIR_Y_RANGE 1.5


Camera::Camera() {
    Camera::speed = 0.1f;
    Camera::angleXZ = 0.0f;
    Camera::angleY = 0.0f;
    Camera::dir = (Vertex3) {0.0f, 0.0f, 0.0f};
    Camera::pos = (Vertex3) {0.0f, 0.0f, 0.0f};
    Camera::deltaAngleXZ = 0.0f;
    Camera::deltaAngleY = 0.0f;
    Camera::deltaPos = (Vertex3) {0.0f, 0.0f, 0.0f};
    Camera::limitAngleY.min = -CAMERA_DIR_Y_RANGE;
    Camera::limitAngleY.max = CAMERA_DIR_Y_RANGE;
    Camera::cosAY = 0.0f;

    //compute x, y and z of directin vector
    Camera::dir.x = cos(Camera::angleXZ);
    Camera::dir.z = sin(Camera::angleXZ);

    //compute y of directin vector
    Camera::dir.y = -sin(Camera::angleY);
    Camera::cosAY = cos(Camera::angleY);
}

void Camera::computePosition() {
    // moving in z axis
    if (Camera::deltaPos.z) {
        Camera::pos.x += Camera::deltaPos.z * Camera::dir.x;
        Camera::pos.z += Camera::deltaPos.z * Camera::dir.z;
    }

    //moving in y axis
    if (Camera::deltaPos.y) {
        Camera::pos.y += Camera::deltaPos.y;
    }

    //moving in x axis
    if (Camera::deltaPos.x) {
        Camera::pos.x -= Camera::deltaPos.x * Camera::dir.z;
        Camera::pos.z += Camera::deltaPos.x * Camera::dir.x;
    }
}

void Camera::computeDirection() {
    if(Camera::deltaAngleXZ) {
        //compute new value of angle XZ
        Camera::angleXZ += Camera::deltaAngleXZ;

        //compute x, y and z of directin vector
        Camera::dir.x = cos(Camera::angleXZ);
        Camera::dir.z = sin(Camera::angleXZ);
    }

    if(Camera::deltaAngleY) {
        //compute new angle of Y
        Camera::angleY += Camera::deltaAngleY;

        //limit
        Camera::angleY = MAX(Camera::angleY, Camera::limitAngleY.min);
        Camera::angleY = MIN(Camera::angleY, Camera::limitAngleY.max);

        //compute y of directin vector
        Camera::dir.y = -sin(Camera::angleY);
        Camera::cosAY = cos(Camera::angleY);
    }
}

void Camera::viewTransformation() {
    gluLookAt(
                Camera::pos.x,
                Camera::pos.y,
                Camera::pos.z,
                Camera::pos.x + Camera::dir.x * Camera::cosAY,
                Camera::pos.y + Camera::dir.y,
                Camera::pos.z + Camera::dir.z * Camera::cosAY,
                0.0f,
                1.0f,
                0.0f
                );
}

Vertex3 Camera::getPosition() {
    return Camera::pos;
}

void Camera::setPosition(Vertex3 * v) {
    Camera::pos = *v;
}

void Camera::setPosition(GLfloat x, GLfloat y, GLfloat z) {
    Camera::pos.x = x;
    Camera::pos.y = y;
    Camera::pos.z = z;
}

Vertex3 Camera::getDirection() {
    return Camera::dir;
}

void Camera::setLimitOfYAngle(float min, float max) {
    if(min < max) {
        Camera::limitAngleY.min = min;
        Camera::limitAngleY.max = max;
    }
}

/***************************************************************************
 *
 *  File:       util.h
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

#ifndef UTIL_H
#define UTIL_H

#include "api.h"

#if __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif


#include <iostream>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <vector>
#include <glm/glm.hpp>



#define MAX(a, b) ({ __typeof__ (a) _a = (a); __typeof__ (b) _b = (b); _a > _b ? _a : _b; })
#define MIN(a, b) ({ __typeof__ (a) _a = (a); __typeof__ (b) _b = (b); _a < _b ? _a : _b; })
#define IN_RANGE(v, min, max) (v >= min && v <= max)


template <typename T>
class S3D_EXPORT Range {
public:
    T min;
    T max;
};



/**
 * @brief UTIL_loadBMP_RGB
 * @param path
 * @param width
 * @param height
 * @param imageSize
 * @param rgba_mode
 * @return
 */
unsigned char * S3D_EXPORT UTIL_loadBMP_RGB(const char * path, unsigned int * width, unsigned int * height,
                                            unsigned int * imageSize, bool rgba_mode);

/**
 * @brief Generate random number in range from 0 to n
 * @param n The highest possible number
 * @return Random int
 */
int S3D_EXPORT UTIL_randInt(int n);

/**
 * @brief Get current system time
 * @return Nanoseconds
 */
__syscall_slong_t S3D_EXPORT UTIL_getSystemNanoTime();

/**
 * @brief Get current system time
 * @return Seconds
 */
__time_t S3D_EXPORT UTIL_getSystemSeconds();

/**
 * @brief Get current system time
 * @return timespec
 */
struct timespec S3D_EXPORT UTIL_getSystemTime();

/**
 * @brief Destruct simple data structure
 * @param data  Pointer on data structure
 */
void S3D_EXPORT UTIL_simpleDestructor(void * data);


template<typename Base, typename T>
inline S3D_EXPORT bool UTIL_instanceof(const T*) {
    return std::is_base_of<Base, T>::value;
}

/**
 * @brief computeModelTranformMatrix
 * @param x
 * @param y
 * @param z
 * @param rX
 * @param rY
 * @param rZ
 * @param sX
 * @param sY
 * @param sZ
 * @return
 */
glm::mat4 S3D_EXPORT UTIL_computeModelTranformMatrix(GLfloat x, GLfloat y, GLfloat z,
                                                     GLfloat rX, GLfloat rY, GLfloat rZ,
                                                     GLfloat sX, GLfloat sY, GLfloat sZ);


template <typename T>
void S3D_EXPORT UTIL_reverseArray(T * array, int start, int end) {
    while (start < end) {
        int temp = array[start];
        array[start] = array[end];
        array[end] = temp;
        start++;
        end--;
    }
}

/**
 * @brief UTIL_reverseImg
 * @param img_data
 * @param len
 * @param bytes_per_pixel
 * @return
 */
bool S3D_EXPORT UTIL_flipImg(unsigned char * img_data, size_t width, size_t height,
                             size_t bytes_per_pixel, bool flip_vertical);

#endif // UTIL_H

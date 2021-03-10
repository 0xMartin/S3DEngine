/**
 * <------------------------------------------------------------------>
 * @name    2D Engine
 * @author  Martin Krcma
 * @date    6. 3. 2021
 * <------------------------------------------------------------------>
 * @file    util.h
 * @brief
 * <------------------------------------------------------------------>
 */


#ifndef UTIL_H
#define UTIL_H

#if __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

#include <stdbool.h>
#include <time.h>


#define MAX(a, b) ({ __typeof__ (a) _a = (a); __typeof__ (b) _b = (b); _a > _b ? _a : _b; })
#define MIN(a, b) ({ __typeof__ (a) _a = (a); __typeof__ (b) _b = (b); _a < _b ? _a : _b; })
#define IN_RANGE(v, min, max) (v >= min && v <= max)

typedef struct {
    GLuint width;
    GLuint height;
    GLuint imageSize;
    GLuint textureID;
} Texture;

/**
 * @brief UTIL_loadBMP
 * @param textuture
 * @param path
 * @return
 */
bool UTIL_loadBMP(Texture * texture, const char * path);

/**
 * @brief randInt
 * @param n
 * @return
 */
int UTIL_randInt(int n);

/**
 * @brief UTIL_getSystemNanoTime
 * @return
 */
__syscall_slong_t UTIL_getSystemNanoTime();

/**
 * @brief UTIL_getSystemSeconds
 * @return
 */
__time_t UTIL_getSystemSeconds();

/**
 * @brief UTIL_getSystemTime
 * @return
 */
struct timespec UTIL_getSystemTime();

#endif // UTIL_H

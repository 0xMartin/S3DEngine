/***************************************************************************
 *
 *  File:       util.cpp
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

#include "util.h"

#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>



unsigned char * UTIL_loadBMP_RGB(const char * path, unsigned int * width, unsigned int * height,
                                 unsigned int * imageSize, bool rgba_mode) {
    if(width == NULL || height == NULL || imageSize == NULL) {
        std::cerr << __FUNCTION__ << ": args error (NULL) [ "<< path << "]" << std::endl;
        return NULL;
    }

    if(strlen(path) == 0) {
        std::cerr << __FUNCTION__ << ": file path is not defined [ "<< path << "]" << std::endl;
        return NULL;
    }

    //header of the BMP file
    unsigned char header[54];
    //rgb data
    unsigned char * data;

    //open file
    FILE * file = fopen(path,"rb");
    if (!file){
        std::cerr << __FUNCTION__ << ": image could not be opened [ "<< path << "]" << std::endl;
        return NULL;
    }
    if (fread(header, 1, sizeof(header), file) != 54){
        std::cerr << __FUNCTION__ << ": not a correct BMP file [ "<< path << "]" << std::endl;
        return NULL;
    }
    if (header[0] != 'B' || header[1] != 'M'){
        std::cerr << __FUNCTION__ << ": not a correct BMP file [ "<< path << "]" << std::endl;
        return NULL;
    }

    //read ints from the byte array
    *imageSize = *(int*)&(header[0x22]);
    *width = *(int*)&(header[0x12]);
    *height = *(int*)&(header[0x16]);

    //some BMP files are misformatted, guess missing information
    if (*imageSize == 0) *imageSize = (*width) * (*height) * (rgba_mode ? 4 : 3);

    //create a rgb buffer
    data = (unsigned char *) malloc(sizeof(unsigned char) * (*imageSize));
    if(data == NULL) {
        std::cerr << __FUNCTION__ << ": failed to allocate BMP data buffer [ "<< path << "]" << std::endl;
        return NULL;
    }

    //read the actual data from the file into the buffer
    fread(data, 1, *imageSize, file);
    //close file
    fclose(file);

    return data;
}


int UTIL_randInt(int n) {
    if ((n - 1) == RAND_MAX) {
        return rand();
    } else {
        int end = RAND_MAX / n;
        end *= n;
        int r;
        while((r = rand()) >= end);
        return r % n;
    }
}


__syscall_slong_t UTIL_getSystemNanoTime() {
    struct timespec ts;
    timespec_get(&ts, TIME_UTC);
    return ts.tv_nsec;
}


__time_t UTIL_getSystemSeconds() {
    struct timespec ts;
    timespec_get(&ts, TIME_UTC);
    return ts.tv_sec;
}


struct timespec UTIL_getSystemTime() {
    struct timespec ts;
    timespec_get(&ts, TIME_UTC);
    return ts;
}


void UTIL_simpleDestructor(void * data) {
    if(data != NULL) {
        free(data);
    }
}


glm::mat4 UTIL_computeModelTranformMatrix(GLfloat x, GLfloat y, GLfloat z,
                                          GLfloat rX, GLfloat rY, GLfloat rZ,
                                          GLfloat sX, GLfloat sY, GLfloat sZ) {

    glm::mat4 m1 = glm::translate(glm::mat4(1.0), glm::vec3(x, y, z));

    glm::mat4 m2 = glm::rotate(glm::mat4(1.0), rX, glm::vec3(1.0, 0.0, 0.0));
    m2 = glm::rotate(m2, rY, glm::vec3(0.0, 1.0, 0.0));
    m2 = glm::rotate(m2, rZ, glm::vec3(0.0, 0.0, 1.0));

    glm::mat4 m3 = glm::scale(glm::mat4(1.0), glm::vec3(sX, sY, sZ));

    return m1 * m2 * m3;
}


bool UTIL_flipImg(unsigned char * img_data, size_t width, size_t height,
                  size_t bytes_per_pixel, bool flip_vertical) {
    if(img_data == NULL || width == 0 ||
            height == 0 || bytes_per_pixel == 0) return false;

    unsigned char tmp;
    int x, y, i;
    unsigned char *v1, *v2;

    for(x = 0; x < (int) (flip_vertical ? width : width/2); ++x) {
        for(y = 0; y < (int) (flip_vertical ? height/2 : height); ++y) {

            v1 = &img_data[(x + y * width) * bytes_per_pixel];

            if(flip_vertical) {
                v2 = &img_data[(x + (height - 1 - y) * width - 1) * bytes_per_pixel];
            } else {
                v2 = &img_data[(width - 1 - x + y * width - 1) * bytes_per_pixel];
            }

            for(i = 0; i < (int) bytes_per_pixel; ++i) {
                tmp = *v1;
                *v1 = *v2;
                *v2 = tmp;
                ++v1;
                ++v2;
            }
        }
    }

    return true;
}

/**
 * <------------------------------------------------------------------>
 * @name    2D Engine
 * @author  Martin Krcma
 * @date    6. 3. 2021
 * <------------------------------------------------------------------>
 * @file    util.c
 * @brief   Implementation of util.h
 * <------------------------------------------------------------------>
 */

#include "util.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Texture * UTIL_loadBMP(const char * path) {
    if(strlen(path) == 0) return NULL;

    // Data read from the header of the BMP file
    unsigned char header[54];
    // Actual RGB data
    unsigned char * data;

    // Open the file
    FILE * file = fopen(path,"rb");
    if (!file){
        printf("Image could not be opened\n");
        return NULL;
    }
    if (fread(header, 1, 54, file) != 54){
        printf("Not a correct BMP file\n");
        return NULL;
    }
    if (header[0] != 'B' || header[1] != 'M'){
        printf("Not a correct BMP file\n");
        return NULL;
    }

    Texture * texture = malloc(sizeof(Texture));
    if(texture == NULL) return NULL;

    // Read ints from the byte array
    texture->imageSize = *(int*)&(header[0x22]);
    texture->width = *(int*)&(header[0x12]);
    texture->height = *(int*)&(header[0x16]);

    // Some BMP files are misformatted, guess missing information
    if (texture->imageSize == 0) texture->imageSize = texture->width * texture->height * 3;

    // Create a buffer
    data = malloc(sizeof(unsigned char) * texture->imageSize);
    // Read the actual data from the file into the buffer
    fread(data, 1, texture->imageSize, file);
    //Everything is in memory now, the file can be closed
    fclose(file);

    // Create one OpenGL texture
    glGenTextures(1, &texture->textureID);

    // "Bind" the newly created texture : all future texture functions will modify this texture
    glBindTexture(GL_TEXTURE_2D, texture->textureID);
    // Give the image to OpenGL
    glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, texture->width, texture->height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    return texture;
}

Texture * UTIL_loadJPEG(const char * path) {

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

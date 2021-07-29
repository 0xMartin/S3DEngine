/******************************************************************************
 * S3D Engine
 *
 * @file       texture.cpp
 * @brief      XXXX Function
 *
 * @author     Martin Krcma
 * @date       2021/07/28
 *****************************************************************************/

#include "texture.h"


#if __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif


#include "stb_image.h"
#include "util.h"
#include <stdlib.h>
#include <iostream>


Texture::Texture(const char * path, bool rgba_mode) {
    int comp;
    unsigned char * data = stbi_load(path, &(Texture::width), &(Texture::height), &comp, 0);
    UTIL_flipImg(data, Texture::width, Texture::height, rgba_mode ? 4 : 3, true);

    if(data == NULL) {
        std::cerr << __FUNCTION__ << ": texture failed to load [" << path << "]" << std::endl;
        return;
    }

    //create one OpenGL texture
    glGenTextures(1, &(Texture::textureID));
    //"bind" the newly created texture : all future texture functions will modify this texture
    glBindTexture(GL_TEXTURE_2D, Texture::textureID);
    //give the image to OpenGL
    glTexImage2D(GL_TEXTURE_2D, 0, rgba_mode ? GL_RGBA : GL_RGB, Texture::width,
                 Texture::height, 0, rgba_mode ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    //free image
    stbi_image_free(data);
}

unsigned int Texture::getWidth() {
    return (unsigned int) Texture::width;
}

unsigned int Texture::getHeight() {
    return (unsigned int) Texture::height;
}

unsigned int Texture::getID() {
    return Texture::textureID;
}

void Texture::bindTexture() {
    glBindTexture(GL_TEXTURE_2D, Texture::textureID);
    glEnable(GL_TEXTURE_2D);
}

void Texture::unbindTexture() {
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
}

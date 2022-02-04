/***************************************************************************
 *
 *  File:       texture.cpp
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

    if(data == NULL) {
        std::cerr << __FUNCTION__ << ": texture failed to load [" << path << "]" << std::endl;
        return;
    }

    UTIL_flipImg(data, Texture::width, Texture::height, rgba_mode ? 4 : 3, true);

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

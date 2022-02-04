/***************************************************************************
 *
 *  File:       texture.h
 *  Date:       28.07.2021
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

#ifndef TEXTURE_H
#define TEXTURE_H

#include "api.h"

/**
 * @brief The Texture class
 */
class S3D_EXPORT Texture
{
protected:
    int width;
    int height;
    unsigned int textureID;

public:
    Texture(const char * path, bool rgba_mode);

    /**
     * @brief getWidth
     * @return
     */
    unsigned int getWidth();

    /**
     * @brief getHeight
     * @return
     */
    unsigned int getHeight();

    /**
     * @brief getImageSize
     * @return
     */
    unsigned int getImageSize();

    /**
     * @brief getID
     * @return
     */
    unsigned int getID();

    /**
     * @brief bindTexture
     */
    void bindTexture();

    /**
     * @brief unbindTexture
     */
    void unbindTexture();
};

#endif // TEXTURE_H

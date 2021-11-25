/******************************************************************************
 * S3D Engine
 *
 * @file       texture.h
 * @brief      XXXX Function
 *
 * @author     Martin Krcma
 * @date       2021/07/28
 *****************************************************************************/

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

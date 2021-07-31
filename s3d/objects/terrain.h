/******************************************************************************
 * S3D Engine
 *
 * @file       map.h
 * @brief      XXXX Function
 *
 * @author     Martin Krcma
 * @date       2021/07/29
 *****************************************************************************/

#ifndef TERRAIN_H
#define TERRAIN_H

#include "../object.h"
#include "../model.h"

/**
 * @brief The Map class
 */
class Terrain : public Object3D
{
protected:
    Texture * texture;
    Model * model;

public:
    /**
     * @brief Terrain
     * @param texture_path
     * @param rgba
     * @param model_path
     */
    Terrain(const char * texture_path, bool rgba, const char * model_path);
    ~Terrain();

    virtual void render(Graphics * graphics, const Event_Render * evt);

    /**
     * @brief setOffset
     * @param pos
     */
    void setOffset(Vertex3 offset);

    /**
     * @brief setScale
     * @param pos
     */
    void setScale(Vertex3 scale);
};


#endif // TERRAIN_H

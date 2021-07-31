/******************************************************************************
 * S3D Engine
 *
 * @file       map.cpp
 * @brief      XXXX Function
 *
 * @author     Martin Krcma
 * @date       2021/07/29
 *****************************************************************************/

#include "terrain.h"

Terrain::Terrain(const char * texture_path, bool rgba, const char * model_path) {
    Terrain::texture = new Texture(texture_path, rgba);
    Terrain::model = new Model(model_path);
    Terrain::model->setTexture(Terrain::texture);
}

Terrain::~Terrain() {
    if(Terrain::model != NULL) {
        delete Terrain::model;
    }
    if(Terrain::texture != NULL) {
        delete Terrain::texture;
    }
}

void Terrain::render(Graphics * graphics, const Event_Render * evt) {
    if(Terrain::model != NULL) {
        Terrain::model->render(graphics);
    }
}

void Terrain::setOffset(Vertex3 offset) {
    if(Terrain::model != NULL) {
        Terrain::model->setOffset(offset);
    }
}

void Terrain::setScale(Vertex3 scale) {
    if(Terrain::model != NULL) {
        Terrain::model->setScale(scale);
    }
}

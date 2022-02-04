/***************************************************************************
 *
 *  File:       terrain.cpp
 *  Date:       29.07.2021
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

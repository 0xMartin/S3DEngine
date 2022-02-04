/***************************************************************************
 *
 *  File:       skybox.cpp
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

#include "skybox.h"


#include "../stb_image.h"


SkyBox::SkyBox(Scene * scene, std::string dirPath, std::string type, bool rgba_mode) {
    SkyBox::scene = scene;

    glGenTextures(1, &(SkyBox::textureID));
    glBindTexture(GL_TEXTURE_CUBE_MAP, SkyBox::textureID);


    std::vector<std::string> faces {
        dirPath + "/right." + type,
        dirPath + "/left." + type,
        dirPath + "/top." + type,
        dirPath + "/bottom." + type,
        dirPath + "/front." + type,
        dirPath + "/back." + type
    };

    int width, height, nrChannels;
    for (unsigned int i = 0; i < faces.size(); i++) {
        unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data != NULL) {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0,
                         rgba_mode ? GL_RGBA : GL_RGB, width, height, 0,
                         rgba_mode ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);
            free(data);
        } else {
            std::cerr << "cubemap texture failed to load [" << faces[i] << "]" << std::endl;
        }
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

SkyBox::~SkyBox() {
    glDeleteTextures(1, &(SkyBox::textureID));
}

void SkyBox::render(Graphics * graphics, const Event_Render * evt) {
    if(SkyBox::scene == NULL) return;
    ((Graphics3D*)graphics)->drawSkybox(SkyBox::scene->getCamera()->getPosition(),
                                        SkyBox::scene->max_renderDistance / 2, SkyBox::textureID);
}

/******************************************************************************
 * S3D Engine
 *
 * @file       skybox.cpp
 * @brief      XXXX Function
 *
 * @author     Martin Krcma
 * @date       2021/07/29
 *****************************************************************************/

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

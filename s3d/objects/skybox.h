#ifndef SKYBOX_H
#define SKYBOX_H

#include "../core.h"


class SkyBox : public Object3D
{
protected:
    GLuint textureID;
    Scene * scene;

public:

    /**
     * @brief SkyBox
     * @param scene
     * @param dirPath
     * @param type
     * @param rgba_mode
     */
    SkyBox(Scene * scene, std::string dirPath, std::string type, bool rgba_mode);

    ~SkyBox();

    virtual void render(Graphics * graphics, const Event_Render * evt);
};

#endif // SKYBOX_H

/******************************************************************************
 * S3D Engine
 *
 * @file       core.h
 * @brief      XXXX Function
 *
 * @author     Martin Krcma
 * @date       2021/07/20
 *****************************************************************************/

#ifndef CORE_H
#define CORE_H


#include "api.h"
#include "util.h"
#include "event.h"
#include "graphics3d.h"
#include "object.h"
#include "camera.h"
#include "io.h"
#include "model.h"
#include <vector>
#include <stdbool.h>


class S3D_EXPORT Scene {
protected:
    Camera * camera;
public:
    bool visibleCursor; /** is cursor visible? */
    bool mouseCamControl; /** control camera by mouse motion */
    bool mouseCenter; /** if true => mouse cursor be always on center of window*/
    GLfloat min_renderDistance; /** minimal render distance */
    GLfloat max_renderDistance; /** maximal render distance */
    std::vector<Object*> objects; /** all objects of scene */
    std::vector<Light*> lights; /** all lights of scene */

    Scene();
    ~Scene();

    /**
     * @brief addObject
     * @param object
     * @return
     */
    bool addObject(Object * object);

    /**
     * @brief getCamera
     * @return
     */
    Camera * getCamera();

    /**
     * @brief addLight
     * @param position
     * @param color
     * @return
     */
    Light * addLight(Vertex3 position, Color color);
};



/*---------------------------------CoreContext----------------------------------------------------*/

/**
 * initials values for CoreContext
 */
#define CORE_DEFAULT_CONFIG (CoreContext){0, 1280, 720,\
    "S3DEngine", false, 50, 50, (Color){0.0, 0.0, 0.0, 1.0},\
    NULL, NULL, std::vector<Texture*>(), std::vector<Model*>(), std::vector<Scene*>()}


typedef S3D_EXPORT struct {
    int windowHandle;   /** GLUT window width */
    unsigned int window_width;  /** Window width */
    unsigned int window_height; /** Window height */
    char window_title[255];   /** Window title */
    bool window_fullScreen; /** True -> fullscreen mode */
    unsigned int fps;   /** Frames per second */
    unsigned int ups;   /** Updates per second */
    Color clearColor; /** Background color of window */
    Scene * activeScene;  /** Currently processed scene */
    Graphics3D * graphics; /** Graphics renderer */
    std::vector<Texture*> textures;    /** Vector of all textures */
    std::vector<Model*> models;    /** Vector of all models */
    std::vector<Scene*> scenes;  /** Vector of all scenes */
} CoreContext;
/*------------------------------------------------------------------------------------------------*/


/**
 * @brief The S3DCore class
 */
class S3D_EXPORT S3DCore
{
public:
    CoreContext * context;

    /**
     * @brief S3DCore
     * @param argc
     * @param argv
     * @param config
     */
    S3DCore(int argc, char *argv[], CoreContext * config);

    ~S3DCore();

    /**
     * @brief run
     * @return
     */
    bool run();

    /**
     * @brief stop
     */
    void stop();

    /**
     * @brief loadTexture
     * @param path
     * @param rgba_mode
     * @return
     */
    Texture * loadTexture(const char * path, bool rgba_mode);

    /**
     * @brief getTextures
     * @return
     */
    std::vector<Texture*> * getTextures();

    /**
     * @brief loadModel
     * @param path
     * @return
     */
    Model * loadModel(const char * path);

    /**
     * @brief getModels
     * @return
     */
    std::vector<Model*> * getModels();

    /**
     * @brief createScene
     * @return
     */
    Scene * createScene();

    /**
     * @brief setActiveScene
     * @param scene
     * @return
     */
    bool setActiveScene(Scene * scene);

    /**
     * @brief deleteScene
     * @param scene
     * @return
     */
    bool deleteScene(Scene * scene);

    /**
     * @brief getScenes
     * @return
     */
    std::vector<Scene*> * getScenes();

};

S3D_EXPORT float CORE_getFPS();

#endif // CORE_H

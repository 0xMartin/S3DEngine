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


#define CORE_DEFAULT_CONFIG (CoreContext){0, 800, 600,\
    "S3DEngine", false, 50, 50, (Color){0.0, 0.0, 0.0, 1.0},\
    NULL, NULL, std::vector<Texture*>(), std::vector<Model*>(), std::vector<Scene*>()}


class Scene {
protected:
    Camera * camera;
public:
    bool visibleCursor; /** is cursor visible? */
    bool mouseCamControl; /** control camera by mouse motion */
    bool mouseCenter; /** if true => mouse cursor be always on center of window*/
    GLfloat min_renderDistance; /** minimal render distance */
    GLfloat max_renderDistance; /** maximal render distance */
    std::vector<Object*> objects; /** all objects of scene */

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
};


typedef struct {
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


/**
 * @brief The S3DCore class
 */
class S3DCore
{

public:

    CoreContext * context;

    /**
     * @brief S3DCore
     * @param argc
     * @param argv
     * @param config
     */
    S3D_API S3DCore(int argc, char *argv[], CoreContext * config);

    S3D_API ~S3DCore();

    /**
     * @brief run
     * @return
     */
    S3D_API bool S3D_API_ENTRY run();

    /**
     * @brief stop
     */
    S3D_API void S3D_API_ENTRY stop();

    /**
     * @brief loadTexture
     * @param path
     * @param rgba_mode
     * @return
     */
    S3D_API Texture * S3D_API_ENTRY loadTexture(const char * path, bool rgba_mode);

    /**
     * @brief getTextures
     * @return
     */
    S3D_API std::vector<Texture*> * S3D_API_ENTRY getTextures();

    /**
     * @brief loadModel
     * @param path
     * @return
     */
    S3D_API Model * S3D_API_ENTRY loadModel(const char * path);

    /**
     * @brief getModels
     * @return
     */
    S3D_API std::vector<Model*> * S3D_API_ENTRY getModels();

    /**
     * @brief createScene
     * @return
     */
    S3D_API Scene * S3D_API_ENTRY createScene();

    /**
     * @brief setActiveScene
     * @param scene
     * @return
     */
    S3D_API bool S3D_API_ENTRY setActiveScene(Scene * scene);

    /**
     * @brief deleteScene
     * @param scene
     * @return
     */
    S3D_API bool S3D_API_ENTRY deleteScene(Scene * scene);

    /**
     * @brief getScenes
     * @return
     */
    S3D_API std::vector<Scene*> * S3D_API_ENTRY getScenes();

};

float CORE_getFPS();

#endif // CORE_H

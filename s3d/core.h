#ifndef CORE_H
#define CORE_H


#include "api.h"
#include "util.h"
#include "event.h"
#include "graphics3d.h"
#include "engine_object.h"
#include "io.h"
#include <vector>
#include <stdbool.h>


#define CORE_DEFAULT_CONFIG {\
    0,\
    800,\
    600,\
    "Window",\
    false,\
    50,\
    50,\
    (Color){0.0, 0.0, 0.0, 1.0},\
    NULL,\
    NULL,\
    NULL,\
    NULL\
    }


class Scene {
public:
    bool visibleCursor; /** Is cursor visible? */
    bool mouseCamControl; /** Control camera by mouse motion */
    std::vector<EngineObject*> * objects;

    Scene();
    ~Scene();

    bool addObject(EngineObject * object);
};


typedef struct {
    int windowHandle;   /** GLUT window width */
    unsigned int window_width;  /** Window width */
    unsigned int window_height; /** Window height */
    char windonw_title[255];   /** Window title */
    bool window_fullScreen; /** True -> fullscreen mode */
    unsigned int fps;   /** Frames per second */
    unsigned int ups;   /** Updates per second */
    Color clearColor; /** Background color of window */
    std::vector<Texture*> * textures;    /** Vector of all textures, consisting only from <Texture> util.h */
    Scene * scene;  /** Currently processed scene */
    std::vector<Scene*> * scenes;  /** List of all scenes */
    Graphics3D * graphics;
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


#endif // CORE_H

/******************************************************************************
 * S3D Engine
 *
 * @file       core.cpp
 * @brief      XXXX Function
 *
 * @author     Martin Krcma
 * @date       2021/07/20
 *****************************************************************************/

#include "core.h"


#include "object.h"
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <iostream>

/**
 * @brief Current engine context, only one context could be processed
 * in application
 */
static CoreContext * CONTEXT = NULL;

/**
 * @brief Thread for updating
 */
static pthread_t thread_update;

//running status bools
static bool running;
static bool glut_main_loop;

//core events iterrupts
static bool interrupt_resize;
static bool interrupt_render;
static bool interrupt_update;
static bool interrupt_press_key;
static bool interrupt_release_key;
static bool interrupt_mouse_move;
static bool interrupt_mouse_button;

//core events
static Event_Key    key_event_press;
static Event_Key    key_event_release;
static Event_Mouse  mouse_event_move;
static Event_Mouse  mouse_event_button;
static Event_Render render_event;
static Event_Resize resize_event;
static Event_Update update_event;


/**
 * @brief switchSceneData
 * @param data
 * @return
 */
static bool switchSceneData(Scene * data);

/**
 * @brief Keyboard pressed function
 * @param key   Pressed key
 * @param x     none
 * @param y     none
 */
static void keyboardFunc(unsigned char key, int x, int y);

/**
 * @brief Keyboard released function
 * @param key   Released key
 * @param x     none
 * @param y     none
 */
static void keyboardUpFunc(unsigned char key, int x, int y);

/**
 * @brief Special keyboard event (pressed)
 * @param key   Key ID
 * @param x     none
 * @param y     none
 */
static void specialFunc(int key, int x, int y);

/**
 * @brief specialUpFunc     Special keyboard event (released)
 * @param key   Key ID
 * @param x     none
 * @param y     none
 */
static void specialUpFunc(int key, int x, int y);

/**
 * @brief Key press event
 * @param key   Pressed key (char)
 * @param ctrl  CTRL is down?
 * @param alt   ALT is down?
 * @param shift SHIFT is down?
 */
static void evt_pressKey(unsigned char key,  bool ctrl,
                         bool alt, bool shift, Arrow_key arrow);

/**
 * @brief Key release event
 * @param key   Released key (char)
 * @param ctrl  CTRL is down?
 * @param alt   ALT is down?
 * @param shift SHIFT is down?
 */
static void evt_releaseKey(unsigned char key,  bool ctrl,
                           bool alt, bool shift, Arrow_key arrow);

/**
 * @brief Mouse move event
 * @param x         X position of mouse cursore
 * @param y         Y position of mouse cursore
 */
static void evt_mouseMove(int x, int y);

/**
 * @brief Mouse button event
 * @param button    Button ID
 * @param state     Button state
 * @param x         none
 * @param y         none
 */
static void evt_mouseButton(int button, int state, int x, int y);

/**
 * @brief GLUT reshape function
 * @param w Window width
 * @param h Window height
 */
static void reshape(int w, int h);

/**
 * @brief Update actual scene (each object) of engine context
 */
static void updateScene();

/**
 * @brief Rendering loop
 */
static void renderLoop(int value);

/**
 * @brief Update loop
 */
static void * updateLoop(void * args);

/**
 * @brief Render actual scene (each object) of engine context
 */
static void renderScene();

/**
 * @brief Exit event of engine
 */
static void exitEvent();

/**
 * @brief Destruct engine core
 */
static void destruct();


S3DCore::S3DCore(int argc, char **argv, CoreContext * context) {
    if(context == NULL) {
        std::cerr << __FUNCTION__ << ": core context if NULL" << std::endl;
        return;
    }
    if(argc < 0 || argv == NULL) {
        std::cerr << __FUNCTION__ << ": args error" << std::endl;
        return;
    }

    /**
     * init core
     */
    S3DCore::context = context;

    /**
     * init glut window
     */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_MULTISAMPLE);
    glutInitWindowSize(S3DCore::context->window_width, S3DCore::context->window_height);
    glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - S3DCore::context->window_width) / 2,
                           (glutGet(GLUT_SCREEN_HEIGHT) - S3DCore::context->window_height) / 2
                           );
    S3DCore::context->windowHandle = glutCreateWindow(S3DCore::context->window_title);

    if(S3DCore::context->windowHandle < 1) {
        std::cerr << __FUNCTION__ << ": failed to create window" << std::endl;
        return;
    }

    S3DCore::context->graphics = new Graphics3D(S3DCore::context->windowHandle);
    if(S3DCore::context->graphics == NULL) {
        std::cerr << __FUNCTION__ << ": failed to init renderer" << std::endl;
        return;
    }

    /**
     * register callbacks
     */

    //exit evt
    atexit(exitEvent);

    //rendering
    glutDisplayFunc(renderScene);
    glutReshapeFunc(reshape);

    //control events
    glutKeyboardFunc(keyboardFunc);
    glutSpecialFunc(specialFunc);
    glutKeyboardUpFunc(keyboardUpFunc);
    glutSpecialUpFunc(specialUpFunc);
    glutIgnoreKeyRepeat(1);
    glutMouseFunc(evt_mouseButton);
    glutPassiveMotionFunc(evt_mouseMove);

    /**
     * init OpenGL
     */

    //opengl config
    glEnable(GL_SCISSOR_TEST);
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glEnable(GL_MULTISAMPLE);
    glHint(GL_MULTISAMPLE_FILTER_HINT_NV, GL_NICEST);
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_POINT_SMOOTH);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}


S3DCore::~S3DCore() {
    if(S3DCore::context) {
        destruct();
    }
}


bool S3DCore::run() {
    if(S3DCore::context == NULL) {
        std::cerr << __FUNCTION__ << ": core context is NULL\n";
        return false;
    }

    CONTEXT = S3DCore::context;
    glutSetWindow(CONTEXT->windowHandle);

    interrupt_resize = false;
    interrupt_render = false;
    interrupt_update = false;
    interrupt_press_key = false;
    interrupt_release_key = false;
    interrupt_mouse_move = false;
    interrupt_mouse_button = false;
    running = true;

    if(pthread_create(&thread_update, NULL, updateLoop, NULL)) {
        return false;
    }

    renderLoop(0);

    if(!glut_main_loop) {
        glut_main_loop = true;
        glutMainLoop();
    }

    return true;
}


void S3DCore::stop() {
    interrupt_resize = true;
    interrupt_render = true;
    interrupt_update = true;
    interrupt_press_key = true;
    interrupt_release_key = true;
    interrupt_mouse_move = true;
    interrupt_mouse_button = true;
    running = false;
}


Texture * S3DCore::loadTexture(const char * path, bool rgba_mode) {
    if(S3DCore::context == NULL) {
        std::cerr << __FUNCTION__ << ": context is NULL" << std::endl;
        return NULL;
    }

    Texture * tex = UTIL_loadTextureBMP(path, rgba_mode);
    if(tex == NULL) {
        std::cerr << __FUNCTION__ << ": failed to create texture [" << path << "]" << std::endl;
        return NULL;
    }
    S3DCore::context->textures.push_back(tex);

    return tex;
}


std::vector<Texture*> * S3DCore::getTextures() {
    if(S3DCore::context == NULL) {
        std::cerr << __FUNCTION__ << ": context is NULL" << std::endl;
        return NULL;
    }

    return &CONTEXT->textures;
}


Model * S3DCore::loadModel(const char * path) {
    if(S3DCore::context == NULL) {
        std::cerr << __FUNCTION__ << ": context is NULL" << std::endl;
        return NULL;
    }

    Model * model = new Model(path);
    if(model == NULL) {
        std::cerr << __FUNCTION__ << ": failed to load model [" << path << "]" << std::endl;
        return NULL;
    }

    S3DCore::context->models.push_back(model);

    return model;
}


std::vector<Model*> * S3DCore::getModels() {
    if(S3DCore::context == NULL) {
        std::cerr << __FUNCTION__ << ": context is NULL" << std::endl;
        return NULL;
    }

    return &CONTEXT->models;
}


Scene * S3DCore::createScene() {
    if(S3DCore::context == NULL) {
        std::cerr << __FUNCTION__ << ": context is NULL" << std::endl;
        return NULL;
    }

    Scene * scene = new Scene();
    if(scene == NULL) {
        std::cerr << __FUNCTION__ << ": faild to create scene" << std::endl;
        return NULL;
    }
    S3DCore::context->scenes.push_back(scene);
    return scene;
}


Scene::Scene() {
    Scene::camera = new Camera();
    if(Scene::camera == NULL) {
        std::cerr << __FUNCTION__ << ": faild to create camera" << std::endl;
        return;
    }
    Scene::mouseCamControl = false;
    Scene::visibleCursor = true;
    Scene::mouseCenter = false;
    Scene::min_renderDistance = 0.05f;
    Scene::max_renderDistance = 200.0f;
}


Scene::~Scene() {
    for(Object * obj : Scene::objects) {
        if(obj) delete obj;
    }

    if(Scene::camera) {
        delete Scene::camera;
    }
}


bool Scene::addObject(Object * object) {
    if(object == NULL) {
        std::cerr << __FUNCTION__ << ": new object is NULL" << std::endl;
        return false;
    }

    Scene::objects.push_back(object);

    return true;
}


Camera * Scene::getCamera() {
    return Scene::camera;
}

Light * Scene::addLight(Vertex3 position, Color color) {
    Light * l = (Light*) malloc(sizeof(Light));
    if(l == NULL) {
        std::cerr << __FUNCTION__ << ": failed to allocate memory" << std::endl;
        return NULL;
    }

    l->position = position;
    l->color = color;
    Scene::lights.push_back(l);

    return l;
}

bool S3DCore::setActiveScene(Scene * scene) {
    if(S3DCore::context == NULL) {
        std::cerr << __FUNCTION__ << ": context is NULL" << std::endl;
        return false;
    }
    if(scene == NULL) {
        std::cerr << __FUNCTION__ << ": the scene to be set as active is NULL" << std::endl;
        return false;
    }

    //set active scene in core context
    bool status = false;
    if(S3DCore::context->activeScene == NULL) {
        S3DCore::context->activeScene = scene;
        status = true;
    } else {
        status = switchSceneData(scene);
    }

    //bing light buffer for Graphics3D
    ((Graphics3D*)S3DCore::context->graphics)->bindLightVector(&(scene->lights));

    //call onload event for all objects
    for(Object * obj : S3DCore::context->activeScene->objects) {
        if(obj) {
            obj->onLoad(S3DCore::context->activeScene->objects);
        }
    }

    //cursor
    if(S3DCore::context->activeScene) {
        if(!S3DCore::context->activeScene->visibleCursor) {
            glutSetCursor(GLUT_CURSOR_NONE);
        }
    }

    return status;
}


bool S3DCore::deleteScene(Scene * scene) {
    if(S3DCore::context == NULL) {
        std::cerr << __FUNCTION__ << ": context is NULL\n";
        return false;
    }

    int i = -1, j = 0;
    for(Scene * s : S3DCore::context->scenes) {
        if(s == scene) {
            i = j;
            break;
        }
        ++j;
    }
    if(i >= 0) {
        S3DCore::context->scenes.erase(S3DCore::context->scenes.begin() + i);
        delete scene;
    }

    return true;
}


std::vector<Scene*> * S3DCore::getScenes() {
    if(S3DCore::context == NULL) {
        std::cerr << __FUNCTION__ << ": context is NULL\n";
        return NULL;
    }
    return &S3DCore::context->scenes;
}



//###############################################################################
//STATIC ENGINE FUNCTIONS
//###############################################################################



static void reshape(int w, int h) {
    if(CONTEXT == NULL) return;
    if(CONTEXT->activeScene == NULL) return;
    resize_event.resize_ratio_horizontal = (double) w / (double) CONTEXT->window_width;
    resize_event.resize_ratio_vertical = (double) h / (double) CONTEXT->window_height;
    resize_event.current_window_width = w;
    resize_event.current_window_height = h;

    CONTEXT->window_width = w;
    CONTEXT->window_height = h;

    for(Object * obj : CONTEXT->activeScene->objects) {
        if(interrupt_resize) {
            interrupt_resize = false;
            break;
        }
        if(obj) {
            obj->resize(&resize_event);
        }
    }

    //use the Projection Matrix
    glMatrixMode(GL_PROJECTION);

    //reset Matrix
    glLoadIdentity();

    //set the viewport to be the entire window
    glViewport(0, 0, w, h);

    //set perspective
    if (h == 0) h = 1;
    float ratio =  w * 1.0 / h;
    ((Graphics3D*)CONTEXT->graphics)->computeProjectionMatrix(
                45.0, ratio, CONTEXT->activeScene->min_renderDistance,
                CONTEXT->activeScene->max_renderDistance);

    //get Back to the Modelview
    glMatrixMode(GL_MODELVIEW);
}


//###############################################################################
//FPS
//###############################################################################
static int frame = 0;
static float fps = 0.0;
static int time_now = 0;
static int time_last = 0;

float CORE_getFPS() {
    return fps;
};
//###############################################################################

static void renderScene() {
    if(CONTEXT == NULL) return;
    if(CONTEXT->graphics == NULL) return;

    /**
     * init render event
     */
    render_event.window_width = CONTEXT->window_width;
    render_event.window_height = CONTEXT->window_height;
    render_event.sender = NULL;


    /**
     * begin rendering
     */
    Graphics * graphics = CONTEXT->graphics;
    graphics->begin(&render_event, &CONTEXT->clearColor);

    /**
     * No active scene
     */
    if(CONTEXT->activeScene == NULL) {
        glutSwapBuffers();
        return;
    }

    /**
     * 3D objects rendering (on background of window)
     */

    //apply camera transformation
    Camera * cam = CONTEXT->activeScene->getCamera();
    if(cam) cam->viewTransformation();

    //render 3D objects first
    for(Object * obj : CONTEXT->activeScene->objects) {
        if(interrupt_render) {
            interrupt_render = false;
            break;
        }
        if(obj) {
            if(obj->type == Obj3D) {
                glPushMatrix();
                obj->render(graphics, &render_event);
                glPopMatrix();
            }
        }
    }

    /**
     * 2D objects rendering (on foreground of window)
     */

    graphics->setOrthographicProjection(&render_event);
    glPushMatrix();
    glLoadIdentity();

    //render 2D objects
    for(Object * obj : CONTEXT->activeScene->objects) {
        if(interrupt_render) {
            interrupt_render = false;
            break;
        }
        if(obj) {
            if(obj->type == Obj2D) {
                glPushMatrix();
                obj->render(graphics, &render_event);
                glPopMatrix();
            }
        }
    }

    //show FPS
    static char buffer[64];
    sprintf(buffer, "FPS: %.2f", fps);
    graphics->setFont(S3D_BITMAP_8_BY_13, 10);
    graphics->setColorRGB(1.0, 0.0, 0.0, 1.0);
    ((Graphics2D*)graphics)->drawString(10, 20, buffer);

    //restore perspective projection
    glPopMatrix();
    graphics->restorePerspectiveProjection();

    /**
     * render all
     */
    graphics->render();

    /**
     * FPS
     */
    frame++;
    time_now=glutGet(GLUT_ELAPSED_TIME);
    if (time_now - time_last > 1000) {
        fps = frame*1000.0/(time_now-time_last);
        time_last = time_now;
        frame = 0;
    }
}


static void updateScene() {
    if(CONTEXT == NULL) return;
    if(!running) return;
    if(CONTEXT->activeScene == NULL) return;

    /**
     * Update camera position
     */
    Camera * cam;
    if((cam = CONTEXT->activeScene->getCamera()) != NULL) {
        cam->computePosition();
    }

    /**
     * compute time difference in ses and ns
     */
    struct timespec time = UTIL_getSystemTime();
    __syscall_slong_t diff = time.tv_nsec - update_event.ns_time;
    if (diff < 0) {
        update_event.ns_diff = time.tv_nsec - update_event.ns_time + 1000000000UL;
        update_event.s_diff = time.tv_sec - update_event.s_time + 1;
    } else {
        update_event.ns_diff = diff;
        update_event.s_diff = time.tv_sec - update_event.s_time;
    }

    /**
     * init updat event
     */
    update_event.ns_time = time.tv_nsec;
    update_event.s_time = time.tv_sec;
    update_event.sender = NULL;

    /**
     * update each object of scene
     */
    for(Object * obj : CONTEXT->activeScene->objects) {
        if(interrupt_update) {
            interrupt_update = false;
            break;
        }
        if(obj) {
            obj->update(CONTEXT->activeScene->objects, &update_event);
        }
    }
}


static void renderLoop(int value) {
    if(!CONTEXT) return;
    if(!running) return;
    glutPostRedisplay();
    glutTimerFunc(1000.0/CONTEXT->fps, renderLoop, 0);
}


static void * updateLoop(void * args) {
    while(running) {
        updateScene();
        usleep((unsigned int)(1e6/CONTEXT->ups));
    }
    return NULL;
}


static void keyboardFunc(unsigned char key, int x, int y) {
    int mod = glutGetModifiers();
    evt_pressKey(key, mod == GLUT_ACTIVE_CTRL,
                 mod == GLUT_ACTIVE_ALT, mod == GLUT_ACTIVE_SHIFT, NONE);
}


static void keyboardUpFunc(unsigned char key, int x, int y) {
    int mod = glutGetModifiers();
    evt_releaseKey(key, mod == GLUT_ACTIVE_CTRL,
                   mod == GLUT_ACTIVE_ALT, mod == GLUT_ACTIVE_SHIFT, NONE);
}


static void specialFunc(int key, int x, int y) {
    Arrow_key arrow_key = NONE;
    switch(key)
    {
    case GLUT_KEY_UP:
        arrow_key = UP;
        break;
    case GLUT_KEY_DOWN:
        arrow_key = DOWN;
        break;
    case GLUT_KEY_LEFT:
        arrow_key = LEFT;
        break;
    case GLUT_KEY_RIGHT:
        arrow_key = RIGHT;
        break;
    }

    evt_pressKey(0x0, key == 0x72, key == 0x74, key == 0x70, arrow_key);
}


static void specialUpFunc(int key, int x, int y) {
    Arrow_key arrow_key = NONE;
    switch(key)
    {
    case GLUT_KEY_UP:
        arrow_key = UP;
        break;
    case GLUT_KEY_DOWN:
        arrow_key = DOWN;
        break;
    case GLUT_KEY_LEFT:
        arrow_key = LEFT;
        break;
    case GLUT_KEY_RIGHT:
        arrow_key = RIGHT;
        break;
    }

    evt_releaseKey(0x0, key == 0x72, key == 0x74, key == 0x70, arrow_key);
}


static void evt_pressKey(unsigned char key, bool ctrl,
                         bool alt, bool shift, Arrow_key arrow) {
    if(CONTEXT == NULL) return;
    if(!running) return;
    if(CONTEXT->activeScene == NULL) return;

    /**
     * init key press event
     */
    key_event_press.key = key;
    key_event_press.ctrl = ctrl;
    key_event_press.alt = alt;
    key_event_press.shift = shift;
    key_event_press.arrow = arrow;
    key_event_press.sender = NULL;

    /**
     * Control camera of active scene
     */
    Camera * cam;
    if((cam = CONTEXT->activeScene->getCamera()) != NULL) {
        switch(key)
        {
        case 'w': case 'W':
            cam->deltaPos.z = cam->speed;
            break;
        case 's': case 'S':
            cam->deltaPos.z = -cam->speed;
            break;
        case 'a': case 'A':
            cam->deltaPos.x = -cam->speed;
            break;
        case 'd': case 'D':
            cam->deltaPos.x = cam->speed;
            break;
        case EVT_C_SPACE:
            cam->deltaPos.y = cam->speed;
            break;
        default:
            if(shift) {
                cam->deltaPos.y = -cam->speed;
            }
        }
    }

    /**
     * invoke event for each object of scene
     */
    for(Object * obj : CONTEXT->activeScene->objects) {
        if(interrupt_press_key) {
            interrupt_press_key = false;
            break;
        }
        if(obj) {
            obj->pressKeyEvt(CONTEXT->activeScene->objects, &key_event_press);
        }
    }
}


static void evt_releaseKey(unsigned char key, bool ctrl,
                           bool alt, bool shift, Arrow_key arrow) {
    if(CONTEXT == NULL) return;
    if(!running) return;
    if(CONTEXT->activeScene == NULL) return;

    /**
     * init key release event
     */
    key_event_release.key = key;
    key_event_release.ctrl = ctrl;
    key_event_release.alt = alt;
    key_event_release.shift = shift;
    key_event_release.arrow = arrow;
    key_event_release.sender = NULL;

    /**
     * Control camera of active scene
     */
    Camera * cam;
    if((cam = CONTEXT->activeScene->getCamera()) != NULL) {
        switch(key)
        {
        case 'w': case 'W': case 's': case 'S':
            cam->deltaPos.z = 0;
            break;
        case 'a': case 'A': case 'd': case 'D':
            cam->deltaPos.x = 0;
            break;
        case EVT_C_SPACE:
            cam->deltaPos.y = 0;
            break;
        default:
            if(shift) {
                cam->deltaPos.y = 0;
            }
        }
    }

    /**
     * invoke event for each object of scene
     */
    for(Object * obj : CONTEXT->activeScene->objects) {
        if(interrupt_release_key) {
            interrupt_release_key = false;
            break;
        }
        if(obj) {
            obj->releaseKeyEvt(CONTEXT->activeScene->objects, &key_event_release);
        }
    }
}


static bool center_cursor = false;

static void evt_mouseMove(int x, int y) {
    if(CONTEXT == NULL) return;
    if(!running) return;
    if(CONTEXT->activeScene == NULL) return;

    /**
     * control camera direction by mouse moving
     */
    if(CONTEXT->activeScene->mouseCamControl) {
        Camera * cam;
        if((cam = CONTEXT->activeScene->getCamera()) != NULL) {
            if(center_cursor) {
                //centerize mouse cursor
                if(CONTEXT->activeScene->mouseCenter) {
                    glutWarpPointer(CONTEXT->window_width / 2, CONTEXT->window_height / 2);
                }

                //compute diference in y and x axis
                cam->deltaAngleY = (y - mouse_event_move.y)/1000.0f;
                cam->deltaAngleXZ = (x - mouse_event_move.x)/1000.0f;

                //compute recompute direction of camera
                cam->computeDirection();
            }
            center_cursor = !center_cursor;
        }
    }

    /**
     * init mouse move event
     */
    mouse_event_move.x = x;
    mouse_event_move.y = y;
    mouse_event_button.sender = NULL;

    /**
     * invoke event for each object of scene
     */
    for(Object * obj : CONTEXT->activeScene->objects) {
        if(interrupt_mouse_move) {
            interrupt_mouse_move = false;
            break;
        }
        if(obj) {
            obj->mouseMoveEvt(CONTEXT->activeScene->objects, &mouse_event_move);
        }
    }
}


static void evt_mouseButton(int button, int state, int x, int y) {
    if(CONTEXT == NULL) return;
    if(!running) return;
    if(CONTEXT->activeScene == NULL) return;

    /**
     * init mouse button event
     */
    mouse_event_button.button = button;
    mouse_event_button.state = state;
    mouse_event_button.x = x;
    mouse_event_button.y = y;
    mouse_event_button.y = y;
    mouse_event_button.sender = NULL;

    /**
     * invoke event for each object of scene
     */
    for(Object * obj : CONTEXT->activeScene->objects) {
        if(interrupt_mouse_button) {
            interrupt_mouse_button = false;
            break;
        }
        if(obj) {
            obj->mouseButtonEvt(CONTEXT->activeScene->objects, &mouse_event_button);
        }
    }
}


static bool switchSceneData(Scene * scene) {
    if(scene == NULL) {
        std::cerr << __FUNCTION__ << ": scene is NULL\n";
        return false;
    }
    if(CONTEXT == NULL) {
        std::cerr << __FUNCTION__ << ": context is NULL\n";
        return false;
    }

    //interrupt everyting
    interrupt_resize = true;
    interrupt_render = true;
    interrupt_update = true;
    interrupt_press_key = true;
    interrupt_release_key = true;
    interrupt_mouse_move = true;
    interrupt_mouse_button = true;

    CONTEXT->activeScene = scene;

    return true;
}


static void exitEvent() {
    if(CONTEXT != NULL) {
        //stop engine
        running = false;

        //interrupt everyting
        interrupt_resize = true;
        interrupt_render = true;
        interrupt_update = true;
        interrupt_press_key = true;
        interrupt_release_key = true;
        interrupt_mouse_move = true;
        interrupt_mouse_button = true;

        //destruct data
        sleep(1);
        destruct();
    }
}


static void destruct() {
    if(CONTEXT == NULL) return;

    //clear scenes
    for(Scene * scene : CONTEXT->scenes) {
        if(scene) delete scene;
    }

    //clear textures
    for(Texture * tex : CONTEXT->textures) {
        if(tex) free(tex);
    }

    //clear models
    for(Model * model : CONTEXT->models) {
        if(model) delete model;
    }
}

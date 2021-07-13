#include "core.h"


#include "engine_object.h"
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <iostream>


static CoreContext * CONTEXT = NULL;

static pthread_t thread_update;
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
 * @brief Update eache E_Obj of current scene
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
 * @brief Render each E_Obj of current scene
 */
static void renderScene();

/**
 * @brief Exit event of engine
 */
static void exitEvent();

/**
 * @brief destruct
 */
static bool destruct(CoreContext * cntx);


S3DCore::S3DCore(int argc, char **argv, CoreContext * context) {
    if(context == NULL) {
        std::cerr << __FUNCTION__ << ": core context if NULL\n";
        return;
    }
    if(argc < 0 || argv == NULL) {
        std::cerr << __FUNCTION__ << ": args error\n";
        return;
    }

    //init core
    S3DCore::context = context;

    S3DCore::context->scenes = new std::vector<Scene*>();
    if(S3DCore::context->scenes == NULL) {
        std::cerr << __FUNCTION__ << ": failed to allocate vector of scenes\n";
        return;
    }

    S3DCore::context->textures = new std::vector<Texture*>();
    if(S3DCore::context->textures == NULL) {
        delete S3DCore::context->scenes;
        std::cerr << __FUNCTION__ << ": failed to allocate vector of textures\n";
        return;
    }

    //init glut window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_MULTISAMPLE);
    glutInitWindowSize(S3DCore::context->window_width, S3DCore::context->window_height);
    glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - S3DCore::context->window_width) / 2,
                           (glutGet(GLUT_SCREEN_HEIGHT) - S3DCore::context->window_height) / 2
                           );
    S3DCore::context->windowHandle = glutCreateWindow(S3DCore::context->windonw_title);

    if(S3DCore::context->windowHandle < 1) {
        std::cerr << __FUNCTION__ << ": failed to create window\n";
        return;
    }

    S3DCore::context->graphics = new Graphics3D(S3DCore::context->windowHandle);
    if(S3DCore::context->graphics == NULL) {
        std::cerr << __FUNCTION__ << ": failed to init renderer\n";
        return;
    }

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

    //opengl config
    glEnable(GL_SCISSOR_TEST);
    glDepthFunc(GL_NEVER);
    glEnable(GL_MULTISAMPLE);
    glHint(GL_MULTISAMPLE_FILTER_HINT_NV, GL_NICEST);
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_POINT_SMOOTH);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //cursor
    if(S3DCore::context->scene) {
        if(!S3DCore::context->scene->visibleCursor) {
            glutSetCursor(GLUT_CURSOR_NONE);
        }
    }
}

S3DCore::~S3DCore() {
    if(S3DCore::context) {
        destruct(S3DCore::context);
    }
}

bool S3DCore::run() {
    if(S3DCore::context == NULL) {
        std::cerr << __FUNCTION__ << ": core context is NULL\n";
        return false;
    }

    CONTEXT = S3DCore::context;
    glutSetWindow(CONTEXT->windowHandle);

    interrupt_resize = true;
    interrupt_render = true;
    interrupt_update = true;
    interrupt_press_key = true;
    interrupt_release_key = true;
    interrupt_mouse_move = true;
    interrupt_mouse_button = true;
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
    interrupt_resize = false;
    interrupt_render = false;
    interrupt_update = false;
    interrupt_press_key = false;
    interrupt_release_key = false;
    interrupt_mouse_move = false;
    interrupt_mouse_button = false;
    running = false;
}

Texture * S3DCore::loadTexture(const char * path, bool rgba_mode) {
    if(S3DCore::context == NULL) {
        std::cerr << __FUNCTION__ << ": context is NULL\n";
        return NULL;
    }
    if(S3DCore::context->textures == NULL) {
        std::cerr << __FUNCTION__ << ": vector of textures is NULL\n";
        return NULL;
    }

    Texture * tex = UTIL_loadTextureBMP(path, rgba_mode);
    if(tex == NULL) {
        std::cerr << __FUNCTION__ << ": failed to create texture\n";
        return NULL;
    }
    S3DCore::context->textures->push_back(tex);

    return tex;
}

std::vector<Texture*> * S3DCore::getTextures() {
    if(S3DCore::context == NULL) {
        std::cerr << __FUNCTION__ << ": context is NULL\n";
        return NULL;
    }
    if(S3DCore::context->textures == NULL) {
        std::cerr << __FUNCTION__ << ": vector of textures is NULL\n";
        return NULL;
    }

    return CONTEXT->textures;
}

Scene * S3DCore::createScene() {
    if(S3DCore::context == NULL) {
        std::cerr << __FUNCTION__ << ": context is NULL\n";
        return NULL;
    }

    Scene * scene = new Scene();
    if(scene == NULL) {
        std::cerr << __FUNCTION__ << ": faild to create scene";
        return NULL;
    }
    S3DCore::context->scenes->push_back(scene);
    return scene;
}

Scene::Scene() {
    Scene::objects = new std::vector<EngineObject*>();
    Scene::mouseCamControl = false;
    Scene::visibleCursor = true;
}

Scene::~Scene() {
    if(Scene::objects) {
        for(EngineObject * obj : *Scene::objects) {
            if(obj) delete obj;
        }
        delete Scene::objects;
    }
}

bool Scene::addObject(EngineObject * object) {
    if(Scene::objects == NULL) {
        std::cerr << __FUNCTION__ << ": object vector in current scene is NULL\n";
        return false;
    }
    if(object == NULL) {
        std::cerr << __FUNCTION__ << ": new object is NULL\n";
        return false;
    }
    Scene::objects->push_back(object);
    return true;
}


bool S3DCore::setActiveScene(Scene * scene) {
    if(S3DCore::context == NULL) {
        std::cerr << __FUNCTION__ << ": context is NULL\n";
        return false;
    }
    if(scene == NULL) {
        std::cerr << __FUNCTION__ << ": the scene to be set as active is NULL\n";
        return false;
    }

    bool status = false;
    if(S3DCore::context->scene == NULL) {
        S3DCore::context->scene = scene;
        status = true;
    } else {
        status = switchSceneData(scene);
    }

    for(EngineObject * obj : *S3DCore::context->scene->objects) {
        if(obj) {
            obj->onLoad(S3DCore::context->scene->objects);
        }
    }

    return status;
}

bool S3DCore::deleteScene(Scene * scene) {
    if(S3DCore::context == NULL) {
        std::cerr << __FUNCTION__ << ": context is NULL\n";
        return false;
    }

    if(S3DCore::context->scenes == NULL) {
        std::cerr << __FUNCTION__ << ": vector with scenes is NULL\n";
        return false;
    }

    int i = -1, j = 0;
    for(Scene * s : *S3DCore::context->scenes) {
        if(s == scene) {
            i = j;
            break;
        }
        ++j;
    }
    if(i >= 0) {
        S3DCore::context->scenes->erase(S3DCore::context->scenes->begin() + i);
        delete scene;
    }

    return true;
}

std::vector<Scene*> * S3DCore::getScenes() {
    if(S3DCore::context == NULL) {
        std::cerr << __FUNCTION__ << ": context is NULL\n";
        return NULL;
    }
    return S3DCore::context->scenes;
}


//###################################################################################
//STATIC FUNCTIONS
//###################################################################################


static void reshape(int w, int h) {
    if(CONTEXT != NULL) {
        resize_event.resize_ratio_horizontal = (double) w / (double) CONTEXT->window_width;
        resize_event.resize_ratio_vertical = (double) h / (double) CONTEXT->window_height;
        resize_event.current_window_width = w;
        resize_event.current_window_height = h;

        CONTEXT->window_width = w;
        CONTEXT->window_height = h;
        glViewport(0, 0, w, h);       /* Establish viewing area to cover entire window. */
        glMatrixMode(GL_PROJECTION);  /* Start modifying the projection matrix. */
        glLoadIdentity();             /* Reset project matrix. */
        glOrtho(0, w, 0, h, -1, 1);   /* Map abstract coords directly to window coords. */
        glScalef(1, -1, 1);           /* Invert Y axis so increasing Y goes down. */
        glTranslatef(0, -h, 0);       /* Shift origin up to upper-left corner. */

        if(CONTEXT->scene != NULL) {
            if(CONTEXT->scene->objects != NULL) {
                for(EngineObject * obj : *CONTEXT->scene->objects) {
                    if(interrupt_resize) {
                        interrupt_resize = false;
                        break;
                    }
                    if(obj) {
                        obj->resize(&resize_event);
                    }
                }
            }
        }
    }
}


static void renderScene() {
    if(CONTEXT == NULL) return;
    if(CONTEXT->graphics == NULL) return;

    render_event.window_width = CONTEXT->window_width;
    render_event.window_height = CONTEXT->window_height;
    render_event.sender = NULL;

    Graphics * graphics = CONTEXT->graphics;
    graphics->begin(&render_event, &CONTEXT->clearColor);

    if(CONTEXT->scene == NULL) {
        glutSwapBuffers();
        return;
    }
    if(CONTEXT->scene->objects == NULL) {
        glutSwapBuffers();
        return;
    }

    for(EngineObject * obj : *CONTEXT->scene->objects) {
        if(interrupt_render) {
            interrupt_render = false;
            break;
        }
        if(obj) {
            obj->render(&render_event, graphics);
        }
    }

    glutSwapBuffers();
}

static void updateScene() {
    if(CONTEXT == NULL) return;
    if(!running) return;

    if(CONTEXT->scene != NULL) {
        if(CONTEXT->scene->objects != NULL) {

            struct timespec time = UTIL_getSystemTime();
            //diff
            __syscall_slong_t diff = time.tv_nsec - update_event.ns_time;
            if (diff < 0) {
                update_event.ns_diff = time.tv_nsec - update_event.ns_time + 1000000000UL;
                update_event.s_diff = time.tv_sec - update_event.s_time + 1;
            } else {
                update_event.ns_diff = diff;
                update_event.s_diff = time.tv_sec - update_event.s_time;
            }
            //current time
            update_event.ns_time = time.tv_nsec;
            update_event.s_time = time.tv_sec;
            update_event.sender = NULL;

            //update all
            for(EngineObject * obj : *CONTEXT->scene->objects) {
                if(interrupt_update) {
                    interrupt_update = false;
                    break;
                }
                if(obj) {
                    obj->update(CONTEXT->scene->objects, &update_event);
                }
            }
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
    key_event_press.key = key;
    key_event_press.ctrl = ctrl;
    key_event_press.alt = alt;
    key_event_press.shift = shift;
    key_event_press.arrow = arrow;
    key_event_press.sender = NULL;

    if(CONTEXT == NULL) return;
    if(!running) return;
    if(CONTEXT->scene == NULL) return;
    if(CONTEXT->scene->objects == NULL) return;

    for(EngineObject * obj : *CONTEXT->scene->objects) {
        if(interrupt_press_key) {
            interrupt_press_key = false;
            break;
        }
        if(obj) {
            obj->pressKeyEvt(CONTEXT->scene->objects, &key_event_press);
        }
    }
}

static void evt_releaseKey(unsigned char key, bool ctrl,
                           bool alt, bool shift, Arrow_key arrow) {
    key_event_release.key = key;
    key_event_release.ctrl = ctrl;
    key_event_release.alt = alt;
    key_event_release.shift = shift;
    key_event_release.arrow = arrow;
    key_event_release.sender = NULL;

    if(CONTEXT == NULL) return;
    if(!running) return;
    if(CONTEXT->scene == NULL) return;
    if(CONTEXT->scene->objects == NULL) return;

    for(EngineObject * obj : *CONTEXT->scene->objects) {
        if(interrupt_release_key) {
            interrupt_release_key = false;
            break;
        }
        if(obj) {
            obj->releaseKeyEvt(CONTEXT->scene->objects, &key_event_release);
        }
    }
}

static void evt_mouseMove(int x, int y) {
    mouse_event_move.x = x;
    mouse_event_move.y = y;
    mouse_event_button.sender = NULL;

    if(CONTEXT == NULL) return;
    if(!running) return;
    if(CONTEXT->scene == NULL) return;
    if(CONTEXT->scene->objects == NULL) return;

    for(EngineObject * obj : *CONTEXT->scene->objects) {
        if(interrupt_mouse_move) {
            interrupt_mouse_move = false;
            break;
        }
        if(obj) {
            obj->mouseMoveEvt(CONTEXT->scene->objects, &mouse_event_move);
        }
    }
}

static void evt_mouseButton(int button, int state, int x, int y) {
    mouse_event_button.button = button;
    mouse_event_button.state = state;
    mouse_event_button.x = x;
    mouse_event_button.y = y;
    mouse_event_button.y = y;
    mouse_event_button.sender = NULL;

    if(CONTEXT == NULL) return;
    if(!running) return;
    if(CONTEXT->scene == NULL) return;
    if(CONTEXT->scene->objects == NULL) return;

    for(EngineObject * obj : *CONTEXT->scene->objects) {
        if(interrupt_mouse_button) {
            interrupt_mouse_button = false;
            break;
        }
        if(obj) {
            obj->mouseButtonEvt(CONTEXT->scene->objects, &mouse_event_button);
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

    interrupt_resize = false;
    interrupt_render = false;
    interrupt_update = false;
    interrupt_press_key = false;
    interrupt_release_key = false;
    interrupt_mouse_move = false;
    interrupt_mouse_button = false;

    CONTEXT->scene = scene;

    return true;
}

static void exitEvent() {
    if(CONTEXT != NULL) {
        running = false;
        interrupt_resize = false;
        interrupt_render = false;
        interrupt_update = false;
        interrupt_press_key = false;
        interrupt_release_key = false;
        interrupt_mouse_move = false;
        interrupt_mouse_button = false;
        sleep(1);
        destruct(CONTEXT);
    }
}

static bool destruct(CoreContext * cntx) {
    if(cntx == NULL) return false;

    //clear scenes
    if(cntx->scenes != NULL) {
        for(Scene * scene : *cntx->scenes) {
            if(scene) {
                delete scene;
            }
        }
        delete cntx->scenes;
    }
    cntx->scenes = NULL;

    //clear textures
    if(cntx->textures != NULL) {
        for(Texture * tex : *cntx->textures) {
            if(tex) free(tex);
        }
        delete cntx->textures;
    }
    cntx->textures = NULL;

    return true;
}

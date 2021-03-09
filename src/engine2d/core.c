/**
 * <------------------------------------------------------------------>
 * @name    2D Engine
 * @author  Martin Krcma
 * @date    28. 2. 2021
 * <------------------------------------------------------------------>
 * @file    core.c
 * @brief   Implementation of core.h
 * <------------------------------------------------------------------>
 */

#include "core.h"

#include "engine_object.h"


static CORE * _core = NULL;


/* Private func declaration -------------------------------------------------------- */

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
 * @param x     none
 * @param y     none
 * @param ctrl  CTRL is down?
 * @param alt   ALT is down?
 * @param shift SHIFT is down?
 */
static void evt_pressKey(unsigned char key, int x, int y, bool ctrl, bool alt, bool shift);

/**
 * @brief Key release event
 * @param key   Released key (char)
 * @param x     none
 * @param y     none
 * @param ctrl  CTRL is down?
 * @param alt   ALT is down?
 * @param shift SHIFT is down?
 */
static void evt_releaseKey(unsigned char key, int x, int y, bool ctrl, bool alt, bool shift);

/**
 * @brief Mouse move event
 * @param x         X position of mouse cursore
 * @param y         Y position of mouse cursore
 */
static void CORE_evt_mouseMove(int x, int y);

/**
 * @brief Mouse button event
 * @param button    Button ID
 * @param state     Button state
 * @param x         none
 * @param y         none
 */
static void CORE_evt_mouseButton(int button, int state, int x, int y);

/**
 * @brief GLUT reshape function
 * @param w Window width
 * @param h Window height
 */
static void reshape(int w, int h);

float f = 0;
/**
 * @brief Main update loop
 */
static void updateLoop();

/**
 * @brief Main render loop
 */
static void renderScene();


bool CORE_init(int argc, char **argv, CORE * core) {
    if(_core != NULL || core == NULL || argc < 0 || argv == NULL) return false;

    //init core struct
    _core = core;
    _core->context = NULL;

    //init glut window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_MULTISAMPLE);
    glutInitWindowSize(core->window_width, core->window_height);
    glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - core->window_width) / 2,
                           (glutGet(GLUT_SCREEN_HEIGHT) - core->window_height) / 2
                           );
    glutCreateWindow(core->windonw_title);


    //rendering
    glutDisplayFunc(renderScene);
    glutIdleFunc(renderScene);
    glutReshapeFunc(reshape);

    //control events
    glutKeyboardFunc(keyboardFunc);
    glutSpecialFunc(specialFunc);
    glutKeyboardUpFunc(keyboardUpFunc);
    glutSpecialUpFunc(specialUpFunc);
    glutIgnoreKeyRepeat(1);
    glutMouseFunc(CORE_evt_mouseButton);
    glutPassiveMotionFunc(CORE_evt_mouseMove);

    //opengl config
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
    if(!core->visibleCursor) {
        glutSetCursor(GLUT_CURSOR_NONE);
    }

    return true;
}

bool CORE_setContex(Context * contx) {
    if(_core == NULL || contx == NULL) return false;

    _core->context = contx;

    return true;
}

bool CORE_run() {
    if(_core == NULL) return false;

    _core->running = true;
    updateLoop();
    //renderLoop();
    glutMainLoop();

    return true;
}


void CORE_stop() {
    if(_core == NULL) return;

    _core->running = false;
}


bool CORE_destruct() {
    if(_core == NULL) return false;

    if(Context_destruct(_core->context)) {
        _core->context = NULL;
    }
    free(_core->windonw_title);

    return true;
}

bool Context_init(Context * contx) {
    if(contx == NULL) return NULL;

    contx->gameData = malloc(sizeof(LinkedList));
    contx->textures = malloc(sizeof(Vector));
    contx->files = malloc(sizeof(Vector));
    if(!LinkedList_init(contx->gameData)) return false;

    return true;
}

bool Context_destruct(Context * contx) {
    if(contx == NULL) return NULL;

    if(contx) {
        if(contx->gameData) {
            LinkedList_dectruct(contx->gameData);
        }
        if(contx->textures) {
            Vector_destruct(contx->textures);
        }
        if(contx->files) {
            Vector_destruct(contx->files);
        }
        free(contx);
    }

    return true;
}

static void reshape(int w, int h) {
    glViewport(0, 0, w, h);       /* Establish viewing area to cover entire window. */
    glMatrixMode(GL_PROJECTION);  /* Start modifying the projection matrix. */
    glLoadIdentity();             /* Reset project matrix. */
    glOrtho(0, w, 0, h, -1, 1);   /* Map abstract coords directly to window coords. */
    glScalef(1, -1, 1);           /* Invert Y axis so increasing Y goes down. */
    glTranslatef(0, -h, 0);       /* Shift origin up to upper-left corner. */
}

static void renderScene() {
    if(_core == NULL) return;

    Render_clear(NULL);

    if(_core->context == NULL) {
        glutSwapBuffers();
        return;
    }
    if(_core->context->gameData == NULL) {
        glutSwapBuffers();
        return;
    }

    E_Obj * obj;
    LinkedList_Element * el = _core->context->gameData->first;
    while(el != NULL) {
        if(el->data != NULL) {
            obj = (E_Obj*) el->data;
            if(obj->render) obj->render(obj, _core->context);
        }
        el = LinkedList_next(el);
    }

    Point2D p[4] = {
        {0, 0, {1, 1, 1, 1}},
        {200 + f, 200 + f, {1, 1, 1, 1}},
        {400, 150, {1, 1, 1, 1}},
        {500, 600, {1, 1, 1, 1}}
    };
    Texture texture;
    if(UTIL_loadBMP(&texture, "data/img.bmp"))
        Render_drawImage(&p[1], &texture, true);

    Render_fillPolygon(p, 4);
    Render_setColorRGB(1.0, 0.4, 0.0, 1.0);
    Render_drawString(&p[1], "2D engine test");

    glutSwapBuffers();
}

static void updateLoop() {
    if(_core == NULL) return;
    if(!_core->running) return;
    //f += 0.5f;
    glutTimerFunc(1000.0/_core->ups, updateLoop, 0);
}

static void keyboardFunc(unsigned char key, int x, int y) {
    int mod = glutGetModifiers();
    evt_pressKey(key, x, y, mod == GLUT_ACTIVE_CTRL,
                      mod == GLUT_ACTIVE_ALT, mod == GLUT_ACTIVE_SHIFT);
}

static void keyboardUpFunc(unsigned char key, int x, int y) {
    int mod = glutGetModifiers();
    evt_releaseKey(key, x, y, mod == GLUT_ACTIVE_CTRL,
                        mod == GLUT_ACTIVE_ALT, mod == GLUT_ACTIVE_SHIFT);
}

static void specialFunc(int key, int x, int y) {
    evt_pressKey(0x0, x, y, key == 0x72, key == 0x74, key == 0x70);
}

static void specialUpFunc(int key, int x, int y) {
    evt_releaseKey(0x0, x, y, key == 0x72, key == 0x74, key == 0x70);
}

static void evt_pressKey(unsigned char key, int x, int y, bool ctrl, bool alt, bool shift) {

}

static void evt_releaseKey(unsigned char key, int x, int y, bool ctrl, bool alt, bool shift) {

}

static void CORE_evt_mouseMove(int x, int y) {

}

static void CORE_evt_mouseButton(int button, int state, int x, int y) {

}

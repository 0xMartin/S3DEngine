/**
 * <------------------------------------------------------------------>
 * @name    2D Engine
 * @author  Martin Krcma
 * @date    28. 2. 2021
 * <------------------------------------------------------------------>
 * @file    core.h
 * @brief
 * <------------------------------------------------------------------>
 */

#ifndef GAME_CORE_H
#define GAME_CORE_H

#include "api.h"
#include "util.h"
#include "linkedlist.h"
#include "vector.h"
#include "render.h"
#include <stdbool.h>


#define CORE_DEFAULT_CONIFG {\
    800,\
    600,\
    "Window",\
    false,\
    false,\
    50,\
    50,\
    true,\
    NULL\
    }

//SPECIAL CHARS
#define EVT_C_SPACE 0x20
#define EVT_C_BACKSPACE 0x8
#define EVT_C_DEL 0x7f
#define EVT_C_ENTER 0xd
#define EVT_C_TAB 0x9
#define EVT_C_ESC 0x1b


typedef struct {
    LinkedList * gameData;  /** game data, list consisting only from <E_Obj> engine_object.h */
    Vector * textures;    /** vector of all textures, consisting only from <Texture> util.h */
    Vector * files; /** vector of all opened files */
} Context;

typedef struct {
    unsigned int window_width;  /** Window width */
    unsigned int window_height; /** Window height */
    char * windonw_title;   /** Window title */
    bool window_fullScreen; /** True -> fullscreen mode */
    bool running;   /** True -> core is running */
    unsigned int fps;   /** Frames per second */
    unsigned int ups;   /** Updates per second */
    bool visibleCursor; /** Is cursor visible? */
    Context * context;  /** Core context */
} CORE;


/**
 * @brief CORE_init
 * @param argc
 * @param argv
 * @param core
 * @return
 */
E2API bool E2APIENTRY CORE_init(int argc, char **argv, CORE * core);

/**
 * @brief CORE_setCData
 * @param contx
 * @return
 */
E2API bool E2APIENTRY CORE_setContex(Context * contx);

/**
 * @brief CORE_run
 * @param core
 * @return
 */
E2API bool E2APIENTRY CORE_run();

/**
 * @brief CORE_stop
 */
E2API void E2APIENTRY CORE_stop();

/**
 * @brief CORE_destruct
 */
E2API bool E2APIENTRY CORE_destruct();

/**
 * @brief Context_init
 * @param data
 * @return
 */
E2API bool E2APIENTRY Context_init(Context * contx);

/**
 * @brief Context_destruct
 * @param contx
 * @return
 */
E2API bool E2APIENTRY Context_destruct(Context * contx);


#endif // CORE_H

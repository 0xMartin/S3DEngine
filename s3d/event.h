/******************************************************************************
 * S3D Engine
 *
 * @file       event.h
 * @brief      XXXX Function
 *
 * @author     Martin Krcma
 * @date       2021/07/20
 *****************************************************************************/

#ifndef EVENT_H
#define EVENT_H


#include <time.h>
#include <stdbool.h>

#if __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


#define EVT_C_SPACE 0x20
#define EVT_C_BACKSPACE 0x8
#define EVT_C_DEL 0x7f
#define EVT_C_ENTER 0xd
#define EVT_C_TAB 0x9
#define EVT_C_ESC 0x1b

#define EVT_M_LEFT GLUT_LEFT_BUTTON
#define EVT_M_RIGHT GLUT_RIGHT_BUTTON
#define EVT_M_MIDDLE GLUT_MIDDLE_BUTTON

#define EVT_M_DOWN GLUT_DOWN
#define EVT_M_UP GLUT_UP



/*------------------------------------CoreEvents--------------------------------------------------*/
typedef enum {
    NONE,
    LEFT,
    RIGHT,
    DOWN,
    UP
} Arrow_key;


//key event
typedef struct {
    unsigned char key;  /** pressed/released key*/
    bool ctrl;  /** true -> ctrl pressed */
    bool alt;   /** true -> alt pressed */
    bool shift; /** true -> shift pressed */
    Arrow_key arrow; /** pressed arrow id */
    void * sender; /** object that triggered the event */
} Event_Key;

//mouse envent
typedef struct {
    int button; /** pressed button*/
    int state;  /** button state*/
    int x;  /** x position of cursore*/
    int y;  /** y position of cursore*/
    void * sender; /** object that triggered the event */
} Event_Mouse;

//render event
typedef struct {
    unsigned int window_width;  /** Window width */
    unsigned int window_height; /** Window height */
    GLfloat x; /** camera position X */
    GLfloat y; /** camera position Y */
    GLfloat z; /** camera position Z */
    void * sender; /** object that triggered the event */
} Event_Render;

//resize event
typedef struct {
    double resize_ratio_vertical; /** Resize ratio vertical */
    double resize_ratio_horizontal; /** Resize ratio horizontal */
    unsigned int current_window_width;  /** Window width */
    unsigned int current_window_height; /** Window height */
    void * sender; /** object that triggered the event */
} Event_Resize;

//update event
typedef struct {
    __syscall_slong_t ns_time;  /** current ns system time*/
    __time_t s_time;    /** current sec system time*/
    __syscall_slong_t ns_diff;   /** ns difference */
    __time_t s_diff;    /** s difference*/
    void * sender; /** object that triggered the event */
} Event_Update;
/*------------------------------------------------------------------------------------------------*/


/*------------------------------------UI-events---------------------------------------------------*/
typedef void (*Event_action)(void * sender, const void * evt);

#define UI_EVENTS_INIT (UI_Events){.focus=false, .hover=false,\
    .enabled=true, .resizable=false, .visible=true, .mousePressAction=NULL,\
    .mouseReleaseAction=NULL, .keyPressedAction=NULL, .keyReleaseAction=NULL,\
    .mouseMovedAction=NULL, .contentChangedAction=NULL}

typedef struct {
    //events
    bool focus;
    bool hover;
    bool enabled;
    bool resizable;
    bool visible;
    Event_action mousePressAction;
    Event_action mouseReleaseAction;
    Event_action keyPressedAction;
    Event_action keyReleaseAction;
    Event_action mouseMovedAction;
    Event_action contentChangedAction;
} UI_Events;
/*------------------------------------------------------------------------------------------------*/


#endif // EVENT_H

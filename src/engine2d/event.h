/**
 * <------------------------------------------------------------------>
 * @name    2D Engine
 * @author  Martin Krcma
 * @date    10. 3. 2021
 * <------------------------------------------------------------------>
 * @file    event.h
 * @brief
 * <------------------------------------------------------------------>
 */

#ifndef EVENT_H
#define EVENT_H

#include <time.h>
#include <stdbool.h>

//key event
typedef struct {
    unsigned char key;  /** pressed/released key*/
    bool ctrl;  /** true -> ctrl pressed */
    bool alt;   /** true -> alt pressed */
    bool shift; /** true -> shift pressed */
} Event_Key;

//mouse envent
typedef struct {
    int button; /** pressed button*/
    int state;  /** button state*/
    int x;  /** x position of cursore*/
    int y;  /** y position of cursore*/
} Event_Mouse;

//render event
typedef struct {
    unsigned int window_width;  /** Window width */
    unsigned int window_height; /** Window height */
} Event_Render;

//update event
typedef struct {
    __syscall_slong_t ns_time;  /** current ns system time*/
    __time_t s_time;    /** current sec system time*/
} Event_Update;

typedef void (*Event_action)(void * sender, void * evt);

#define UI_EVENTS_INIT (UI_Events){false, false, NULL, NULL, NULL, NULL, NULL, NULL}

//UI events
typedef struct {
    bool focus;
    bool hover;
    Event_action mousePressAction;
    Event_action mouseReleaseAction;
    Event_action keyPressedAction;
    Event_action keyReleaseAction;
    Event_action mouseMovedAction;
    Event_action contentChangedAction;
} UI_Events;

#endif // EVENT_H

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
    bool press;   /** true [key press], false [key release]*/
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

typedef void (*Event_action)(void * sender);

#endif // EVENT_H

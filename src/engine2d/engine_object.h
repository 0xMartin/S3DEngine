/**
 * <------------------------------------------------------------------>
 * @name    2D Engine
 * @author  Martin Krcma
 * @date    28. 2. 2021
 * <------------------------------------------------------------------>
 * @file    engine_object.h
 * @brief
 * <------------------------------------------------------------------>
 */

#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "core.h"
#include "linkedlist.h"
#include "event.h"


typedef struct _E_Obj_Data {
    void * value;   /** Pointer on data */
    void (*destruct)(struct _E_Obj_Data * obj); /** Destruct data */
} E_Obj_Data;

typedef struct _E_Obj {
    LinkedList * data;  /** object data, list consisting only from E_Obj_Data */
    void (*destruct)(struct _E_Obj * obj, Context * cntx);  /** Destruct object */
    void (*render)(struct _E_Obj * obj, Context * cntx, Event_Render * evt);    /** Render object */
    void (*update)(struct _E_Obj * obj, Context * cntx, Event_Update * evt);    /** Update object */
    void (*mouseMoveEvt)(struct _E_Obj * obj, Context * cntx, Event_Mouse * evt); /** Mouse move event */
    void (*mouseButtonEvt)(struct _E_Obj * obj, Context * cntx, Event_Mouse * evt); /** Mouse button event */
    void (*pressKeyEvt)(struct _E_Obj * obj, Context * cntx, Event_Key * evt); /** Key pressed event */
    void (*releaseKeyEvt)(struct _E_Obj * obj, Context * cntx, Event_Key * evt);    /** Key released event */
} E_Obj;


/**
 * @brief G_Obj_init
 * @param g_obj
 */
void E_Obj_init(E_Obj * g_obj);

/**
 * @brief G_Obj_destruct
 * @param g_obj
 */
void E_Obj_destruct(E_Obj * g_obj);


#endif // ENGINE_OBJECT_H

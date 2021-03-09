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


typedef struct _E_Obj_Data {
    void * value;   /** Pointer on data */
    void (*destruct)(struct _E_Obj_Data * obj); /** Destruct data */
} E_Obj_Data;

typedef struct _E_Obj {
    LinkedList * data;  /** object data, list consisting only from E_Obj_Data */
    void (*destruct)(struct _E_Obj * obj, Context * cntx);  /** Destruct object */
    void (*render)(struct _E_Obj * obj, Context * cntx);    /** Render object */
    void (*update)(struct _E_Obj * obj, Context * cntx);    /** Update object */
    void (*mouseClickEvt)(struct _E_Obj * obj, Context * cntx); /** Mouse click event */
    void (*keyPressedEvt)(struct _E_Obj * obj, Context * cntx); /** Key pressed event */
    void (*keyReleasedEvt)(struct _E_Obj * obj, Context * cntx);    /** Key released event */
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

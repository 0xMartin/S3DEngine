/**
 * <------------------------------------------------------------------>
 * @name    2D Engine
 * @author  Martin Krcma
 * @date    28. 2. 2021
 * <------------------------------------------------------------------>
 * @file    object_virtual_functions.h
 * @brief
 * <------------------------------------------------------------------>
 */

#ifndef EVENT_VIRTUAL_FUNCTIONS_H
#define EVENT_VIRTUAL_FUNCTIONS_H

#include "core.h"
#include "engine_object.h"

static void destruct(void * ptr);  /** Destruct object */

static void render(struct _E_Obj * obj, Event_Render * evt);    /** Render object */

static void update(struct _E_Obj * obj, Context * cntx, Event_Update * evt);    /** Update object */

static void mouseMoveEvt(struct _E_Obj * obj, Context * cntx, Event_Mouse * evt); /** Mouse move event */

static void mouseButtonEvt(struct _E_Obj * obj, Context * cntx, Event_Mouse * evt); /** Mouse button event */

static void pressKeyEvt(struct _E_Obj * obj, Context * cntx, Event_Key * evt); /** Key pressed event */

static void releaseKeyEvt(struct _E_Obj * obj, Context * cntx, Event_Key * evt);    /** Key released event */

#endif // OBJECT_VIRTUAL_FUNCTIONS_H

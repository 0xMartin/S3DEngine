/***************************************************************************
 *
 *  File:       object.h
 *  Date:       20.07.2021
 *
 *  Github:     https://github.com/0xMartin
 *  Email:      martin.krcma1@gmail.com
 *
 *  Copyright (C) 2022 Martin Krcma
 *
 *  Permission is hereby granted, free of charge, to any person
 *  obtaining a copy of this software and associated documentation
 *  files (the "Software"), to deal in the Software without
 *  restriction, including without limitation the rights to use,
 *  copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following
 *  conditions:
 *
 *  The above copyright notice and this permission notice shall be
 *  included in all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 *  OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 *  HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 *  WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 *  OTHER DEALINGS IN THE SOFTWARE.
 *
 ***************************************************************************/

#ifndef OBJECT_H
#define OBJECT_H

#include "api.h"
#include "graphics3d.h"
#include "event.h"
#include <vector>


typedef S3D_EXPORT enum {
    None,
    Obj3D,
    Obj2D
} ObjType;


/**
 * @brief The Object class [ABSTRACT]
 */
class S3D_EXPORT Object
{
public:
    /**
     * @brief Type of object (2D, 3D or none)
     */
    const ObjType type;



    Object(ObjType t);

    virtual ~Object();

    /**
     * @brief Render object core event
     * @param graphics Graphics rendered
     * @param evt Event_Render
     */
    virtual void render(Graphics * graphics, const Event_Render * evt);

    /**
     * @brief Resize object core event
     * @param evt Event_Resize
     */
    virtual void resize(const Event_Resize * evt);

    /**
     * @brief Update object core event
     * @param objects All objects on scene
     * @param evt Event_Update
     */
    virtual void update(std::vector<Object*> & objects,
                        const Event_Update * evt);

    /**
     * @brief Mouse move core event
     * @param objects All objects on scene
     * @param evt Event_Mouse
     */
    virtual void mouseMoveEvt(std::vector<Object*> & objects,
                              const Event_Mouse * evt);

    /**
     * @brief Mouse button core event
     * @param objects All objects on scene
     * @param evt Event_Mouse
     */
    virtual void mouseButtonEvt(std::vector<Object*> & objects,
                                const Event_Mouse * evt);

    /**
     * @brief Key pressed core event
     * @param objects All objects on scene
     * @param evt Event_Key
     */
    virtual void pressKeyEvt(std::vector<Object*> & objects,
                             const Event_Key * evt);

    /**
     * @brief Key released core event
     * @param objects All objects on scene
     * @param evt Event_Key
     */
    virtual void releaseKeyEvt(std::vector<Object*> & objects,
                               const Event_Key * evt);

    /**
     * @brief On scene load core event
     * @param objects All objects on scene
     */
    virtual void onLoad(std::vector<Object*> & objects);

};


/**
 * @brief The Object2D class [ABSTRACT]
 */
class S3D_EXPORT Object2D : public Object
{
public:
    Point position;

    Object2D();
    virtual ~Object2D();
};


/**
 * @brief The Object3D class [ABSTRACT]
 */
class S3D_EXPORT Object3D : public Object
{
public:
    Vertex3 position;

    Object3D();
    virtual ~Object3D();
};


#endif // OBJECT_H

/***************************************************************************
 *
 *  File:       object.cpp
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

#include "object.h"

Object::Object(ObjType t) : type(t){}

Object::~Object() {}

void Object::render(Graphics * graphics, const Event_Render * evt) {}

void Object::resize(const Event_Resize * evt) {}

void Object::update(std::vector<Object*> & objects, const Event_Update * evt) {}

void Object::mouseMoveEvt(std::vector<Object*> & objects, const Event_Mouse * evt){}

void Object::mouseButtonEvt(std::vector<Object*> & objects, const Event_Mouse * evt) {}

void Object::pressKeyEvt(std::vector<Object*> & objects, const Event_Key * evt) {}

void Object::releaseKeyEvt(std::vector<Object*> & objects, const Event_Key * evt) {}

void Object::onLoad(std::vector<Object*> & objects) {}


Object2D::Object2D() : Object(Obj2D){

}

Object2D::~Object2D() {

}

Object3D::Object3D() : Object(Obj3D){

}

Object3D::~Object3D() {

}

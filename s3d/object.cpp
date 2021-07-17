#include "object.h"

Object::Object(ObjType t) : type(t){}

Object::~Object() {}

void Object::render(Graphics * graphics, const Event_Render * evt) {}

void Object::resize(const Event_Resize * evt) {}

void Object::update(std::vector<Object*> * objects, const Event_Update * evt) {}

void Object::mouseMoveEvt(std::vector<Object*> * objects, const Event_Mouse * evt){}

void Object::mouseButtonEvt(std::vector<Object*> * objects, const Event_Mouse * evt) {}

void Object::pressKeyEvt(std::vector<Object*> * objects, const Event_Key * evt) {}

void Object::releaseKeyEvt(std::vector<Object*> * objects, const Event_Key * evt) {}

void Object::onLoad(std::vector<Object*> * objects) {}


Object2D::Object2D() : Object(Obj2D){

}

Object2D::~Object2D() {

}

Object3D::Object3D() : Object(Obj3D){

}

Object3D::~Object3D() {

}

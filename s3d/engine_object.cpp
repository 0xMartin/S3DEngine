#include "engine_object.h"


EngineObject::~EngineObject() {
}

void EngineObject::render(const Event_Render * evt, Graphics * graphics) {
}

void EngineObject::resize(const Event_Resize * evt) {
}

void EngineObject::update(std::vector<EngineObject*> * objects,
                          const Event_Update * evt) {
}

void EngineObject::mouseMoveEvt(std::vector<EngineObject*> * objects,
                                const Event_Mouse * evt) {
}

void EngineObject::mouseButtonEvt(std::vector<EngineObject*> * objects,
                                  const Event_Mouse * evt) {
}

void EngineObject::pressKeyEvt(std::vector<EngineObject*> * objects,
                               const Event_Key * evt) {
}

void EngineObject::releaseKeyEvt(std::vector<EngineObject*> * objects,
                                 const Event_Key * evt) {
}

void EngineObject::onLoad(std::vector<EngineObject*> * objects) {
}

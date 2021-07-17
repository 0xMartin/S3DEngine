#include "ui_obj.h"

UI_obj::~UI_obj() {
}

void UI_obj::render(Graphics * graphics, const Event_Render * evt) {
}

void UI_obj::resize(const Event_Resize * evt) {
    if(UI_obj::events.resizable) {
        UI_obj::position.x *= evt->resize_ratio_horizontal;
        UI_obj::position.y *= evt->resize_ratio_vertical;
        UI_obj::width *= evt->resize_ratio_horizontal;
        UI_obj::height *= evt->resize_ratio_vertical;
    }
}

void UI_obj::update(std::vector<Object*> * objects,
                    const Event_Update * evt) {
}

void UI_obj::mouseMoveEvt(std::vector<Object*> * objects,
                          const Event_Mouse * evt) {
    if(!UI_obj::events.enabled || !UI_obj::events.visible) return;

    if(evt->x >= 0 && evt->y >= 0) {
        if(IN_RANGE(evt->x, UI_obj::position.x, UI_obj::position.x + UI_obj::width)) {
            if(IN_RANGE(evt->y, UI_obj::position.y, UI_obj::position.y + UI_obj::height)) {
                UI_obj::events.hover = true;
                if(UI_obj::events.mouseMovedAction) UI_obj::events.mouseMovedAction(this, evt);
                return;
            }
        }
    }
    UI_obj::events.hover = false;
}

void UI_obj::mouseButtonEvt(std::vector<Object*> * objects,
                            const Event_Mouse * evt) {
    if(!UI_obj::events.enabled || !UI_obj::events.visible) return;

    UI_obj::events.focus = false;
    if(evt->x >= 0 && evt->y >= 0) {
        if(IN_RANGE(evt->x, UI_obj::position.x, UI_obj::position.x + UI_obj::width)) {
            if(IN_RANGE(evt->y, UI_obj::position.y, UI_obj::position.y + UI_obj::height)) {
                UI_obj::events.focus = true;
                if(evt->state == EVT_M_DOWN) {
                    if(UI_obj::events.mousePressAction) UI_obj::events.mousePressAction(this, evt);
                } else if(evt->state == EVT_M_UP) {
                    if(UI_obj::events.mouseReleaseAction) UI_obj::events.mouseReleaseAction(this, evt);
                }
            }
        }
    }
}

void UI_obj::pressKeyEvt(std::vector<Object*> * objects,
                         const Event_Key * evt) {
    if(!UI_obj::events.enabled || !UI_obj::events.visible) return;

    if(UI_obj::events.focus) {
        if(UI_obj::events.keyPressedAction) UI_obj::events.keyPressedAction(this, evt);
    }
}

void UI_obj::releaseKeyEvt(std::vector<Object*> * objects,
                           const Event_Key * evt) {
    if(!UI_obj::events.enabled || !UI_obj::events.visible) return;

    if(UI_obj::events.focus) {
        if(UI_obj::events.keyPressedAction) UI_obj::events.keyPressedAction(this, evt);
    }
}

void UI_obj::onLoad(std::vector<Object*> * objects) {
}

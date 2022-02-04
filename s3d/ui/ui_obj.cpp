/***************************************************************************
 *
 *  File:       ui_obj.cpp
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

void UI_obj::update(std::vector<Object*> & objects,
                    const Event_Update * evt) {
}

void UI_obj::mouseMoveEvt(std::vector<Object*> & objects,
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

void UI_obj::mouseButtonEvt(std::vector<Object*> & objects,
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

void UI_obj::pressKeyEvt(std::vector<Object*> & objects,
                         const Event_Key * evt) {
    if(!UI_obj::events.enabled || !UI_obj::events.visible) return;

    if(UI_obj::events.focus) {
        if(UI_obj::events.keyPressedAction) UI_obj::events.keyPressedAction(this, evt);
    }
}

void UI_obj::releaseKeyEvt(std::vector<Object*> & objects,
                           const Event_Key * evt) {
    if(!UI_obj::events.enabled || !UI_obj::events.visible) return;

    if(UI_obj::events.focus) {
        if(UI_obj::events.keyPressedAction) UI_obj::events.keyPressedAction(this, evt);
    }
}

void UI_obj::onLoad(std::vector<Object*> & objects) {
}

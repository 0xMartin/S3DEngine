/***************************************************************************
 *
 *  File:       panel.cpp
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

#include "panel.h"


#define MOUSE_POS_THRESHOLD 15


Panel::Panel(int x, int y, size_t width, size_t height) {
    Panel::events = UI_EVENTS_INIT;

    Panel::background = UI_PANEL_BG_COLOR;
    Panel::position.x = x;
    Panel::position.y = y;
    Panel::width = width;
    Panel::height = height;
}

Panel::~Panel() {

}

void Panel::setBGColor(Color color) {
    Panel::background = color;
}

bool Panel::addObject(Object * object) {
    if(object == NULL) return false;
    Panel::childs.push_back(object);
    return true;
}

void Panel::render(Graphics * graphics, const Event_Render * evt) {
    if(!Panel::events.visible) return;

    Event_Render panel_evt;
    panel_evt.window_width = Panel::width;
    panel_evt.window_height = Panel::height;
    panel_evt.sender = this;

    Graphics2D * g2 = (Graphics2D*)graphics;

    //draw panel
    g2->setColor(&(Panel::background));
    g2->fillRectangle(&(Panel::position), Panel::width, Panel::height);
    Color border_color = COLOR_LIGHTER(Panel::background, 0.1);
    g2->setColor(&border_color);
    g2->drawRectangle(&(Panel::position), Panel::width, Panel::height);


    //render childs
    g2->setScissor(Panel::position.x, Panel::position.y + Panel::height,
                   Panel::width, Panel::height, evt);
    g2->applyOffset(Panel::position.x, Panel::position.y, 0.0);

    for(Object * child : Panel::childs) {
        if(child) child->render(graphics, &panel_evt);
    }

    g2->clearOffset();
    g2->resetScissor(evt);
}

void Panel::resize(const Event_Resize * evt) {
    if(Panel::events.resizable) {
        Panel::position.x *= evt->resize_ratio_horizontal;
        Panel::position.y *= evt->resize_ratio_vertical;
        Panel::width *= evt->resize_ratio_horizontal;
        Panel::height *= evt->resize_ratio_vertical;

        Event_Resize panel_evt = *evt;
        panel_evt.current_window_width = Panel::width;
        panel_evt.current_window_height = Panel::height;
        panel_evt.sender = this;

        for(Object * child : Panel::childs) {
            if(child) child->resize(&panel_evt);
        }
    }
}

void Panel::update(std::vector<Object*> & objects,
                   const Event_Update * evt) {
    Event_Update panel_evt = *evt;
    panel_evt.sender = this;

    for(Object * child : Panel::childs) {
        if(child) child->update(objects, &panel_evt);
    }
}

void Panel::mouseMoveEvt(std::vector<Object*> & objects,
                         const Event_Mouse * evt) {
    if(!Panel::events.enabled || !Panel::events.visible) return;

    if(IN_RANGE(evt->x, Panel::position.x - MOUSE_POS_THRESHOLD,
                Panel::position.x + Panel::width + MOUSE_POS_THRESHOLD)) {
        if(IN_RANGE(evt->y, Panel::position.y - MOUSE_POS_THRESHOLD,
                    Panel::position.y + Panel::height + MOUSE_POS_THRESHOLD)) {

            Event_Mouse panel_evt = *evt;
            panel_evt.x -= Panel::position.x;
            panel_evt.y -= Panel::position.y;
            panel_evt.sender = this;

            for(Object * child : Panel::childs) {
                if(child) child->mouseMoveEvt(objects, &panel_evt);
            }
        }
    }
}

void Panel::mouseButtonEvt(std::vector<Object*> & objects,
                           const Event_Mouse * evt) {
    if(!Panel::events.enabled || !Panel::events.visible) return;

    Panel::events.focus = false;
    if(IN_RANGE(evt->x, Panel::position.x - MOUSE_POS_THRESHOLD,
                Panel::position.x + Panel::width + MOUSE_POS_THRESHOLD)) {
        if(IN_RANGE(evt->y, Panel::position.y - MOUSE_POS_THRESHOLD,
                    Panel::position.y + Panel::height + MOUSE_POS_THRESHOLD)) {
            Panel::events.focus = true;

            Event_Mouse panel_evt = *evt;
            panel_evt.x -= Panel::position.x;
            panel_evt.y -= Panel::position.y;
            panel_evt.sender = this;

            for(Object * child : Panel::childs) {
                if(child) child->mouseButtonEvt(objects, &panel_evt);
            }
        }
    }
}

void Panel::pressKeyEvt(std::vector<Object*> & objects,
                        const Event_Key * evt) {
    if(!Panel::events.enabled || !Panel::events.visible) return;

    if(Panel::events.focus) {
        Event_Key panel_evt = *evt;
        panel_evt.sender = this;

        for(Object * child : Panel::childs) {
            if(child) child->pressKeyEvt(objects, &panel_evt);
        }
    }
}

void Panel::releaseKeyEvt(std::vector<Object*> & objects,
                          const Event_Key * evt) {
    if(!Panel::events.enabled || !Panel::events.visible) return;

    if(Panel::events.focus) {
        Event_Key panel_evt = *evt;
        panel_evt.sender = this;

        for(Object * child : Panel::childs) {
            if(child) child->releaseKeyEvt(objects, &panel_evt);
        }
    }
}

void Panel::onLoad(std::vector<Object*> & objects) {
    for(Object * child : Panel::childs) {
        if(child) child->onLoad(objects);
    }
}

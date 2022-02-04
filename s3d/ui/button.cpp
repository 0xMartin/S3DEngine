/***************************************************************************
 *
 *  File:       button.cpp
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

#include "button.h"

Button::Button(int x, int y, size_t width, size_t heigth,
               const char * const txt) {
    if(txt == NULL) return;

    Button::events = UI_EVENTS_INIT;
    Button::background = UI_BUTTON_BG_COLOR;
    Button::foreground = UI_BUTTON_FG_COLOR;
    Button::events.enabled = true;
    Button::position.x = x;
    Button::position.y = y;
    Button::width = width;
    Button::height = heigth;
    if(txt != NULL) {
        snprintf(Button::text, LABEL_MAX_LENGTH, "%s", txt);
    }
}

void Button::setBGColor(Color color) {
    Button::background = color;
}

void Button::setFGColor(Color color) {
    Button::foreground = color;
}

bool Button::setText(char * txt) {
    if(txt == NULL) return false;
    snprintf(Button::text, LABEL_MAX_LENGTH, "%s", txt);
    return true;
}

char * Button::getText() {
    return Button::text;
}

void Button::render(Graphics * graphics, const Event_Render * evt) {
    if(!Button::events.visible) return;

    Graphics2D * g2 = (Graphics2D*)graphics;

    g2->setColor(&(Button::background));
    g2->drawRectangle(&(Button::position), Button::width, Button::height);

    if(Button::events.hover) {
        g2->fillRectangle(&(Button::position), Button::width, Button::height);
        Color foreground_hover = COLOR_LIGHTER(Button::foreground, 0.6);
        g2->setColor(&foreground_hover);
    } else {
        g2->setColor(&(Button::foreground));
    }

    g2->drawString(
                Button::position.x + (Button::width - g2->getStringWidth(Button::text))/2,
                Button::position.y + (Button::height + g2->getStringHeight())/2,
                Button::text);
}

void Button::mouseMoveEvt(std::vector<Object*> & objects,
                          const Event_Mouse * evt) {
    if(!Button::events.enabled || !Button::events.visible) return;

    if(evt->x >= 0 && evt->y >= 0) {
        if(IN_RANGE(evt->x, Button::position.x, Button::position.x + Button::width)) {
            if(IN_RANGE(evt->y, Button::position.y, Button::position.y + Button::height)) {
                Button::events.hover = true;
                if(Button::events.mouseMovedAction) Button::events.mouseMovedAction(this, evt);
                return;
            }
        }
    }
    Button::events.hover = false;
}

void Button::mouseButtonEvt(std::vector<Object*> & objects,
                            const Event_Mouse * evt){
    if(!Button::events.enabled || !Button::events.visible) return;

    Button::events.focus = false;
    if(evt->x >= 0 && evt->y >= 0) {
        if(IN_RANGE(evt->x, Button::position.x, Button::position.x + Button::width)) {
            if(IN_RANGE(evt->y, Button::position.y, Button::position.y + Button::height)) {
                Button::events.focus = true;
                if(evt->state == EVT_M_DOWN) {
                    if(Button::events.mousePressAction) Button::events.mousePressAction(this, evt);
                } else if(evt->state == EVT_M_UP) {
                    if(Button::events.mouseReleaseAction) Button::events.mouseReleaseAction(this, evt);
                }
            }
        }
    }
}


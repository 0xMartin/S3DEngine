/***************************************************************************
 *
 *  File:       checkbox.cpp
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

#include "checkbox.h"


CheckBox::CheckBox(int x, int y, size_t size, bool value,
                   const char * const txt) {
    CheckBox::events = UI_EVENTS_INIT;
    CheckBox::position.x = x;
    CheckBox::position.y = y;
    CheckBox::value = value;
    CheckBox::width = size;
    CheckBox::height = size;
    CheckBox::background = UI_CHECK_BG_COLOR;
    CheckBox::borderColor = UI_CHECK_BORDER_COLOR;
    CheckBox::foreground = UI_CHECK_FG_COLOR;
    CheckBox::label = new Label(size + 10, 0, txt);
}

CheckBox::~CheckBox() {
    if(CheckBox::label) delete CheckBox::label;
}

void CheckBox::setBGColor(Color color) {
    CheckBox::background = color;
}

void CheckBox::setFGColor(Color color) {
    CheckBox::foreground = color;
}

Label * CheckBox::getLabel() {
    return CheckBox::label;
}

void CheckBox::render(Graphics * graphics, const Event_Render * evt) {
    if(!CheckBox::events.visible) return;

    Graphics2D * g2 = (Graphics2D*)graphics;

    g2->setColor(&(CheckBox::background));
    g2->fillRectangle(&(CheckBox::position), CheckBox::width, CheckBox::height);
    g2->setColor(&(CheckBox::borderColor));
    g2->drawRectangle(&(CheckBox::position), CheckBox::width, CheckBox::height);

    if(CheckBox::value) {
        g2->setColor(&(CheckBox::foreground));
        Point pts[3];
        pts[0].x = CheckBox::position.x + (int)CheckBox::width / 4;
        pts[0].y = CheckBox::position.y + (int)CheckBox::height / 4;
        pts[1].x = CheckBox::position.x + (int)CheckBox::width / 2;
        pts[1].y = CheckBox::position.y + (int)CheckBox::height * 0.7;
        pts[2].x = CheckBox::position.x + (int)CheckBox::width * 1.2;
        pts[2].y = CheckBox::position.y - (int)CheckBox::height / 6;
        g2->lineWidth(2.5);
        g2->drawLines(pts, 3);
        g2->lineWidth(DEFAULT_LINE_WIDTH);
    }

    if(CheckBox::label != NULL) {
        int center = CheckBox::height/2 + g2->getStringHeight()/3;
        //shift origin
        glTranslatef(CheckBox::position.x, CheckBox::position.y + center, 0);

        //render
        CheckBox::label->render(graphics, evt);

        //shift origin back
        glTranslatef(-CheckBox::position.x, -CheckBox::position.y - center, 0);
    }
}

void CheckBox::mouseButtonEvt(std::vector<Object*> & objects,
                              const Event_Mouse * evt) {
    if(!CheckBox::events.enabled || !CheckBox::events.visible) return;

    CheckBox::events.focus = false;
    if(evt->x >= 0 && evt->y >= 0) {
        if(IN_RANGE(evt->x, CheckBox::position.x, CheckBox::position.x + CheckBox::width)) {
            if(IN_RANGE(evt->y, CheckBox::position.y, CheckBox::position.y + CheckBox::height)) {
                CheckBox::events.focus = true;

                if(evt->state == EVT_M_DOWN) {
                    CheckBox::value = !CheckBox::value;
                    if(CheckBox::events.mousePressAction) CheckBox::events.mousePressAction(this, evt);
                } else if(evt->state == EVT_M_UP) {
                    if(CheckBox::events.mouseReleaseAction) CheckBox::events.mouseReleaseAction(this, evt);
                }
            }
        }
    }
}


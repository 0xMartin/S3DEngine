/***************************************************************************
 *
 *  File:       label.cpp
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

#include "label.h"

#include <string.h>


Label::Label(int x, int y, const char * const txt) {
    Label::events = UI_EVENTS_INIT;
    Label::foreground = UI_LABEL_FG_COLOR;
    Label::position.x = x;
    Label::position.y = y;
    Label::centered = false;
    if(txt != NULL) {
        snprintf(Label::text, LABEL_MAX_LENGTH, "%s", txt);
    }
}

void Label::changeText(const char * const txt) {
    if(txt != NULL) {
        snprintf(Label::text, LABEL_MAX_LENGTH, "%s", txt);
    }
}

void Label::setCentered(bool centered) {
    Label::centered = centered;
}

void Label::render(Graphics * graphics, const Event_Render * evt) {
    if(!Label::events.visible) return;

    Graphics2D * g2 = (Graphics2D*)graphics;

    g2->setColor(&(Label::foreground));
    if(Label::centered) {
        g2->drawString(
                    Label::position.x - g2->getStringWidth(Label::text) / 2,
                    Label::position.y,
                    Label::text);
    } else {
        g2->drawString(
                    Label::position.x,
                    Label::position.y,
                    Label::text);
    }
}

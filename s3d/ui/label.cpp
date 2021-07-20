/******************************************************************************
 * S3D Engine
 *
 * @file       label.cpp
 * @brief      XXXX Function
 *
 * @author     Martin Krcma
 * @date       2021/07/20
 *****************************************************************************/

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

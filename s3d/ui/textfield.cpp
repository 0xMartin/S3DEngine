#include "textfield.h"

#include <stdlib.h>
#include <string.h>
#include <ctype.h>

TextField::TextField(int x, int y, size_t width, size_t heigth,
                     size_t max_str_len) {
    TextField::events = UI_EVENTS_INIT;
    TextField::position.x = x;
    TextField::position.y = y;
    TextField::width = width;
    TextField::height = heigth;
    TextField::caret_position = 0;
    TextField::caret_offset = 0;
    TextField::background = UI_TEXTFIELD_BG_COLOR;
    TextField::foreground = UI_TEXTFIELD_FG_COLOR;
    TextField::caret = UI_TEXTFIELD_CARET_COLOR;
    TextField::maxTextLength = max_str_len;
    TextField::text = (char*) calloc(max_str_len + 1, sizeof (char));
}

TextField::~TextField() {
    if(TextField::text) free(TextField::text);
}

bool TextField::setText(const char * const txt) {
    if(txt == NULL) return false;

    size_t txt_length = strlen(txt);
    unsigned int i;
    for(i = 0; i < TextField::maxTextLength - 1 && i < txt_length; ++i) {
        *(TextField::text + i) = *(txt + i);
    }
    *(TextField::text + i) = 0;

    return true;
}

void TextField::render(Graphics * graphics, const Event_Render * evt) {
    if(!TextField::events.visible) return;

    Graphics2D * g2 = (Graphics2D*)graphics;
    TextField::graphics = graphics;

    g2->disableVertexColor();
    if(TextField::events.focus) {
        Color darker_bg = COLOR_DARKER(TextField::background, 0.4);
        g2->setColor(&darker_bg);
    } else {
        g2->setColor(&(TextField::background));
    }
    g2->fillRectangle(&(TextField::position), TextField::width, TextField::height);
    Color border = COLOR_LIGHTER(TextField::background, 0.2);
    g2->setColor(&border);
    g2->drawRectangle(&(TextField::position), TextField::width, TextField::height);


    g2->setColor(&(TextField::foreground));

    float line_start = (TextField::height + g2->getStringHeight())/2;

    g2->setScissor(TextField::position.x + 5, TextField::position.y + TextField::height,
                   TextField::width - 10, TextField::height, evt);
    g2->drawString(TextField::position.x + 5 - g2->getStringWidthRange(
                       TextField::text, TextField::caret_position - abs(TextField::caret_offset), TextField::caret_position),
                   TextField::position.y + line_start,
                   TextField::text);

    if(TextField::events.focus) {
        if(TextField::caret_time % 2 == 0) {
            Point p1, p2;
            p1.x = TextField::position.x + 5 + g2->getStringWidthIndex(TextField::text, TextField::caret_position + TextField::caret_offset) + 2;
            p2.x = p1.x;
            p1.y = TextField::position.y + line_start;
            p2.y = TextField::position.y + line_start - g2->getStringHeight();
            g2->setColor(&(TextField::caret));
            g2->drawLine(&p1, &p2);
        }
    }

    g2->resetScissor(evt);
}

void TextField::update(std::vector<Object*> * objects,
                       const Event_Update * evt) {
    TextField::caret_time = evt->ns_time/4e8;
}

void TextField::mouseMoveEvt(std::vector<Object*> * objects,
                             const Event_Mouse * evt) {
    if(!TextField::events.enabled || !TextField::events.visible) return;

    if(evt->x >= 0 && evt->y >= 0) {
        if(IN_RANGE(evt->x, TextField::position.x, TextField::position.x + TextField::width)) {
            if(IN_RANGE(evt->y, TextField::position.y, TextField::position.y + TextField::height)) {
                TextField::events.hover = true;
                if(TextField::events.mouseMovedAction) TextField::events.mouseMovedAction(this, evt);
                return;
            }
        }
    }
    TextField::events.hover = false;
}

void TextField::mouseButtonEvt(std::vector<Object*> * objects,
                               const Event_Mouse * evt) {
    if(!TextField::events.enabled || !TextField::events.visible) return;

    TextField::events.focus = false;
    if(evt->x >= 0 && evt->y >= 0) {
        if(IN_RANGE(evt->x, TextField::position.x, TextField::position.x + TextField::width)) {
            if(IN_RANGE(evt->y, TextField::position.y, TextField::position.y + TextField::height)) {
                TextField::events.focus = true;
                if(evt->state == EVT_M_DOWN) {
                    if(TextField::events.mousePressAction) TextField::events.mousePressAction(this, evt);
                } else if(evt->state == EVT_M_UP) {
                    if(TextField::events.mouseReleaseAction) TextField::events.mouseReleaseAction(this, evt);
                }

                int min = INT16_MAX;
                int v;
                int index = 0;
                for(size_t i = 0; i <= TextField::maxTextLength; ++i) {
                    v = TextField::position.x + 5 + TextField::graphics->getStringWidthIndex(TextField::text, i) + 2 ;
                    v -= TextField::graphics->getStringWidthRange(
                                TextField::text, TextField::caret_position - abs(TextField::caret_offset), TextField::caret_position);
                    v = abs(v - evt->x);
                    if(v < min) {
                        min = v;
                        index = i;
                    }
                }
                TextField::caret_position = index;
            }
        }
    }
}

void TextField::pressKeyEvt(std::vector<Object*> * objects,
                            const Event_Key * evt) {
    if(!TextField::events.enabled || !TextField::events.visible) return;

    if(TextField::events.focus) {
        if(TextField::events.keyPressedAction) TextField::events.keyPressedAction(this, evt);

        if(isprint(evt->key)) {
            if(strlen(TextField::text) + 1 <= (unsigned long)TextField::maxTextLength) {
                for(int i = strlen(TextField::text); i > TextField::caret_position; --i) {
                    TextField::text[i] = TextField::text[i - 1];
                }
                TextField::text[TextField::caret_position] = evt->key;
                TextField::caret_position++;

                if((unsigned long) TextField::graphics->getStringWidthIndex(
                            TextField::text, TextField::caret_position + TextField::caret_offset) > TextField::width - 10) {
                    TextField::caret_offset--;
                }
            }
        } else {
            switch(evt->key) {
            case EVT_C_BACKSPACE:
                if(TextField::caret_position > 0) {
                    for(unsigned long i = TextField::caret_position - 1; i < strlen(TextField::text); ++i) {
                        TextField::text[i] = TextField::text[i + 1];
                    }
                    if(TextField::caret_offset < 0) {
                        TextField::caret_offset++;
                    }
                    TextField::caret_position--;
                }
                break;
            }
            switch(evt->arrow) {
            case LEFT:
                if(TextField::caret_position > 0) {
                    TextField::caret_position--;
                }
                break;
            case RIGHT:
                if((unsigned long)TextField::caret_position < strlen(TextField::text)) {
                    TextField::caret_position++;
                }
                break;
            }
        }
    }
}

void TextField::releaseKeyEvt(std::vector<Object*> * objects,
                              const Event_Key * evt) {
    if(!TextField::events.enabled || !TextField::events.visible) return;

    if(TextField::events.focus) {
        if(TextField::events.keyPressedAction) TextField::events.keyPressedAction(this, evt);
    }
}

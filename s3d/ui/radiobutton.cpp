#include "radiobutton.h"


RadioButton::RadioButton(int x, int y, size_t size, bool value,
                         const char * const txt) {
    RadioButton::events = UI_EVENTS_INIT;
    RadioButton::position.x = x;
    RadioButton::position.y = y;
    RadioButton::width = size;
    RadioButton::height = size;
    RadioButton::value = value;
    RadioButton::group = NULL;
    RadioButton::background = UI_CHECK_BG_COLOR;
    RadioButton::borderColor = UI_CHECK_BORDER_COLOR;
    RadioButton::foreground = UI_CHECK_FG_COLOR;
    RadioButton::label = new Label(size + 10, 0, txt);
}

RadioButton::~RadioButton() {
    if(RadioButton::label) {
        delete RadioButton::label;
    }
}

void RadioButton::setBGColor(Color color) {

}

void RadioButton::setFGColor(Color color) {

}

Label * RadioButton::getLabel() {

}

void RadioButton::setValue(bool value) {

}

bool RadioButton::getValue() {

}

void RadioButton::render(Graphics * graphics, const Event_Render * evt) {
    if(!RadioButton::events.visible) return;

    Point p = RadioButton::position;
    p.x += RadioButton::width/2;
    p.y += RadioButton::height/2;

    Graphics2D * g2 = (Graphics2D*)graphics;

    g2->disableVertexColor();
    g2->setColor(&(RadioButton::background));
    g2->setColor(&(RadioButton::borderColor));
    g2->lineWidth(2);
    g2->drawEllipse(&p, RadioButton::width/2, RadioButton::height/2);
    g2->lineWidth(DEFAULT_LINE_WIDTH);

    if(RadioButton::value) {
        g2->setColor(&(RadioButton::foreground));
        g2->fillEllipse(&p, RadioButton::width/3, RadioButton::height/3);
    }

    if(RadioButton::label != NULL) {
        int center = RadioButton::height/2 + g2->getStringHeight()/3;
        //shift origin
        glTranslatef(RadioButton::position.x, RadioButton::position.y + center, 0);

        //render
        RadioButton::label->render(graphics, evt);

        //shift origin back
        glTranslatef(-RadioButton::position.x, -RadioButton::position.y - center, 0);
    }
}

void RadioButton::mouseButtonEvt(std::vector<Object*> * objects,
                                 const Event_Mouse * evt) {
    if(!RadioButton::events.enabled || !RadioButton::events.visible) return;

    RadioButton::events.focus = false;
    if(evt->x >= 0 && evt->y >= 0) {
        if(IN_RANGE(evt->x, RadioButton::position.x, RadioButton::position.x + RadioButton::width)) {
            if(IN_RANGE(evt->y, RadioButton::position.y, RadioButton::position.y + RadioButton::height)) {
                RadioButton::events.focus = true;
                if(evt->state == EVT_M_DOWN) {

                    //change value of radio button, set false value for all in group
                    RadioButton::value = true;
                    if(RadioButton::group) {
                        for(void * btn : *group->radiobuttons) {
                            if(btn == this) continue;
                            ((RadioButton*)btn) ->value = false;
                        }
                    }

                    if(RadioButton::events.mousePressAction) RadioButton::events.mousePressAction(this, evt);
                } else if(evt->state == EVT_M_UP) {
                    if(RadioButton::events.mouseReleaseAction) RadioButton::events.mouseReleaseAction(this, evt);
                }
            }
        }
    }
}

RadioButtonGroup::RadioButtonGroup() {
    RadioButtonGroup::radiobuttons = new std::vector<void*>();
}

RadioButtonGroup::~RadioButtonGroup() {
    if(RadioButtonGroup::radiobuttons) {
        delete RadioButtonGroup::radiobuttons;
    }
}

bool RadioButtonGroup::addRadioButton(void * btn) {
    if(RadioButtonGroup::radiobuttons == NULL) return false;
    ((RadioButton*)btn)->group = this;
    RadioButtonGroup::radiobuttons->push_back(btn);
    return true;
}

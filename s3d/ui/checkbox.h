#ifndef CHECKBOX_H
#define CHECKBOX_H


#include "ui_obj.h"
#include "label.h"
#include "../graphics2d.h"


class CheckBox : public UI_obj
{
protected:
    bool value;
    Color background;
    Color borderColor;
    Color foreground;
    Label * label;

public:
    CheckBox(int x, int y, size_t size, bool value,
             const char * const txt);

    virtual ~CheckBox();

    void setBGColor(Color color);

    void setFGColor(Color color);

    Label * getLabel();

    virtual void render(Graphics * graphics, const Event_Render * evt);

    virtual void mouseButtonEvt(std::vector<Object*> * objects,
                                const Event_Mouse * evt);

};


#endif // CHECKBOX_H

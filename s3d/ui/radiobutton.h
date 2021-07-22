/******************************************************************************
 * S3D Engine
 *
 * @file       radiobutton.h
 * @brief      XXXX Function
 *
 * @author     Martin Krcma
 * @date       2021/07/20
 *****************************************************************************/

#ifndef RADIOBUTTON_H
#define RADIOBUTTON_H

#include "ui_obj.h"
#include "../graphics2d.h"
#include "label.h"
#include <vector>


class RadioButtonGroup : public Object2D
{
public:
    std::vector<void*> * radiobuttons;

    RadioButtonGroup();
    ~RadioButtonGroup();

    bool addRadioButton(void * btn);
};


class RadioButton : public UI_obj
{
protected:
    bool value;
    Color background;
    Color borderColor;
    Color foreground;
    Label * label;

public:
    RadioButtonGroup * group;

    RadioButton(int x, int y, size_t size, bool value,
                const char * const txt);
    virtual ~RadioButton();

    void setBGColor(Color color);

    void setFGColor(Color color);

    Label * getLabel();

    void setValue(bool value);

    bool getValue();

    virtual void render(Graphics * graphics, const Event_Render * evt);

    virtual void mouseButtonEvt(std::vector<Object*> & objects,
                                const Event_Mouse * evt);
};


#endif // RADIOBUTTON_H

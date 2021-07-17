#ifndef BUTTON_H
#define BUTTON_H

#include "ui_obj.h"
#include "../graphics2d.h"


class Button : public UI_obj
{
protected:
    Color background;
    Color foreground;
    char text[LABEL_MAX_LENGTH];
public:
    Button(int x, int y, size_t width, size_t heigth,
           const char * const txt);

    void setBGColor(Color color);

    void setFGColor(Color color);

    bool setText(char * txt);

    char * getText();

    virtual void render(Graphics * graphics, const Event_Render * evt);

    virtual void mouseMoveEvt(std::vector<Object*> * objects,
                              const Event_Mouse * evt);

    virtual void mouseButtonEvt(std::vector<Object*> * objects,
                                const Event_Mouse * evt);

};


#endif // BUTTON_H

#ifndef LABEL_H
#define LABEL_H

#include "ui_obj.h"
#include "../graphics2d.h"


class Label : public UI_obj
{

protected:
    char text[LABEL_MAX_LENGTH];
    Color foreground;
    bool centered;

public:
    Label(int x, int y, const char * const txt);

    void changeText(const char * const txt);

    void setCentered(bool centered);

    virtual void render(const Event_Render * evt, Graphics * graphics);
};

#endif // LABEL_H

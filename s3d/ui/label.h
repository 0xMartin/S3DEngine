/******************************************************************************
 * S3D Engine
 *
 * @file       label.h
 * @brief      XXXX Function
 *
 * @author     Martin Krcma
 * @date       2021/07/20
 *****************************************************************************/

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

    virtual void render(Graphics * graphics, const Event_Render * evt);
};

#endif // LABEL_H

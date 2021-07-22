/******************************************************************************
 * S3D Engine
 *
 * @file       ui_obj.h
 * @brief      XXXX Function
 *
 * @author     Martin Krcma
 * @date       2021/07/20
 *****************************************************************************/

#ifndef UI_OBJ_H
#define UI_OBJ_H

#include "../object.h"
#include "../event.h"
#include "../graphics2d.h"



//background of window
#define UI_BG_COLOR (Color){0.050, 0.065, 0.090, 1.000}

//panel
#define UI_PANEL_BG_COLOR (Color){0.10, 0.120, 0.170, 0.900}

//button
#define UI_BUTTON_BG_COLOR (Color){0.259, 0.267, 0.314, 0.800}
#define UI_BUTTON_FG_COLOR (Color){0.251, 0.251, 0.271, 1.000}


//check box
#define UI_CHECK_BG_COLOR (Color){0.050, 0.065, 0.090, 1.000}
#define UI_CHECK_BORDER_COLOR (Color){0.259, 0.267, 0.314, 1.000}
#define UI_CHECK_FG_COLOR (Color){0.400, 0.400, 0.500, 1.000}

//label
#define UI_LABEL_FG_COLOR (Color){0.525, 0.533, 0.535, 1.000}

//textfiled
#define UI_TEXTFIELD_BG_COLOR (Color){0.15, 0.15, 0.15, 1.0}
#define UI_TEXTFIELD_FG_COLOR (Color){0.800, 0.800, 0.800, 1.000}
#define UI_TEXTFIELD_CARET_COLOR (Color){1.0, 1.0, 1.0, 1.0}

#define LABEL_MAX_LENGTH 255




class UI_obj : public Object2D
{
public:
    GLfloat width; /** width of UI object */
    GLfloat height; /** height of UI object */

    /**
     * @brief events
     */
    UI_Events events;

    virtual ~UI_obj();

    virtual void render(Graphics * graphics, const Event_Render * evt);

    virtual void resize(const Event_Resize * evt);

    virtual void update(std::vector<Object*> & objects,
                        const Event_Update * evt);

    virtual void mouseMoveEvt(std::vector<Object*> & objects,
                              const Event_Mouse * evt);

    virtual void mouseButtonEvt(std::vector<Object*> & objects,
                                const Event_Mouse * evt);

    virtual void pressKeyEvt(std::vector<Object*> & objects,
                             const Event_Key * evt);

    virtual void releaseKeyEvt(std::vector<Object*> & objects,
                               const Event_Key * evt);

    virtual void onLoad(std::vector<Object*> & objects);
};

#endif // UI_OBJ_H

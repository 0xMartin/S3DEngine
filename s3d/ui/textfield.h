#ifndef TEXTFIELD_H
#define TEXTFIELD_H

#include "ui_obj.h"
#include "../graphics2d.h"


class TextField : public UI_obj
{
private:
    Graphics * graphics;
protected:
    Color background;
    Color foreground;
    Color caret;
    int caret_position;
    int caret_offset;
    int caret_time;
    size_t maxTextLength;

public:
    char * text;

    TextField(int x, int y, size_t width, size_t heigth,
              size_t max_str_len);
    virtual ~TextField();

    bool setText(const char * const txt);

    virtual void render(const Event_Render * evt, Graphics * graphics);

    virtual void update(std::vector<EngineObject*> * objects,
                        const Event_Update * evt);

    virtual void mouseMoveEvt(std::vector<EngineObject*> * objects,
                              const Event_Mouse * evt);

    virtual void mouseButtonEvt(std::vector<EngineObject*> * objects,
                                const Event_Mouse * evt);

    virtual void pressKeyEvt(std::vector<EngineObject*> * objects,
                             const Event_Key * evt);

    virtual void releaseKeyEvt(std::vector<EngineObject*> * objects,
                               const Event_Key * evt);
};

#endif // TEXTFIELD_H

#ifndef PANEL_H
#define PANEL_H


#include "ui_obj.h"
#include "../object.h"
#include "../graphics2d.h"
#include <vector>


class Panel : public UI_obj
{
protected:
    Color background;

public:
    std::vector<Object*> * childs;

    Panel(int x, int y, size_t width, size_t height);
    virtual ~Panel();

    void setBGColor(Color color);

    bool addObject(Object * object);

    virtual void render(Graphics * graphics, const Event_Render * evt);

    virtual void resize(const Event_Resize * evt);

    virtual void update(std::vector<Object*> * objects,
                        const Event_Update * evt);

    virtual void mouseMoveEvt(std::vector<Object*> * objects,
                              const Event_Mouse * evt);

    virtual void mouseButtonEvt(std::vector<Object*> * objects,
                                const Event_Mouse * evt);

    virtual void pressKeyEvt(std::vector<Object*> * objects,
                             const Event_Key * evt);

    virtual void releaseKeyEvt(std::vector<Object*> * objects,
                               const Event_Key * evt);

    virtual void onLoad(std::vector<Object*> * objects);
};

#endif // PANEL_H

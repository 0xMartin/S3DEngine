#ifndef PANEL_H
#define PANEL_H


#include "ui_obj.h"
#include "../engine_object.h"
#include "../graphics2d.h"
#include <vector>


class Panel : public UI_obj
{
protected:
    Color background;

public:
    std::vector<EngineObject*> * childs;

    Panel(int x, int y, size_t width, size_t height);
    virtual ~Panel();

    void setBGColor(Color color);

    bool addObject(EngineObject * object);

    virtual void render(const Event_Render * evt, Graphics * graphics);

    virtual void resize(const Event_Resize * evt);

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

    virtual void onLoad(std::vector<EngineObject*> * objects);
};

#endif // PANEL_H

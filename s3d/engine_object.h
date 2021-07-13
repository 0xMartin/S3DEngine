#ifndef ENGINE_OBJECT_H
#define ENGINE_OBJECT_H


#include "graphics.h"
#include "event.h"
#include <vector>


/**
 * @brief The EngineObject class [ABSTRACT]
 */
class EngineObject
{

public:
    virtual ~EngineObject();

    /**
     * @brief Render object event
     * @param obj
     * @param evt
     */
    virtual void render(const Event_Render * evt, Graphics * graphics);

    /**
     * @brief Resize object event
     * @param evt
     */
    virtual void resize(const Event_Resize * evt);

    /**
     * @brief Update object event
     * @param objects
     * @param evt
     */
    virtual void update(std::vector<EngineObject*> * objects,
                        const Event_Update * evt);

    /**
     * @brief Mouse move event
     * @param objects
     * @param evt
     */
    virtual void mouseMoveEvt(std::vector<EngineObject*> * objects,
                              const Event_Mouse * evt);

    /**
     * @brief Mouse button event
     * @param objects
     * @param evt
     */
    virtual void mouseButtonEvt(std::vector<EngineObject*> * objects,
                                const Event_Mouse * evt);

    /**
     * @brief Key pressed event
     * @param objects
     * @param evt
     */
    virtual void pressKeyEvt(std::vector<EngineObject*> * objects,
                             const Event_Key * evt);

    /**
     * @brief Key released event
     * @param objects
     * @param evt
     */
    virtual void releaseKeyEvt(std::vector<EngineObject*> * objects,
                               const Event_Key * evt);

    /**
     * @brief On scene load event
     * @param objects
     */
    virtual void onLoad(std::vector<EngineObject*> * objects);

};


#endif // ENGINE_OBJECT_H

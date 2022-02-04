/***************************************************************************
 *
 *  File:       panel.h
 *  Date:       20.07.2021
 *
 *  Github:     https://github.com/0xMartin
 *  Email:      martin.krcma1@gmail.com
 *
 *  Copyright (C) 2022 Martin Krcma
 *
 *  Permission is hereby granted, free of charge, to any person
 *  obtaining a copy of this software and associated documentation
 *  files (the "Software"), to deal in the Software without
 *  restriction, including without limitation the rights to use,
 *  copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following
 *  conditions:
 *
 *  The above copyright notice and this permission notice shall be
 *  included in all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 *  OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 *  HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 *  WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 *  OTHER DEALINGS IN THE SOFTWARE.
 *
 ***************************************************************************/

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
    std::vector<Object*> childs;

    Panel(int x, int y, size_t width, size_t height);
    virtual ~Panel();

    void setBGColor(Color color);

    bool addObject(Object * object);

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

#endif // PANEL_H

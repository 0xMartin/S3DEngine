/***************************************************************************
 *
 *  File:       textfield.h
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

    virtual void render(Graphics * graphics, const Event_Render * evt);

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
};

#endif // TEXTFIELD_H

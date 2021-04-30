/**
 * <------------------------------------------------------------------>
 * @name    TicTacToe
 * @author  Martin Krcma
 * @date    28. 2. 2021
 * <------------------------------------------------------------------>
 * @file    main.c
 * @brief
 * <------------------------------------------------------------------>
 */

#include "s3d/core.h"
#include "s3d/engine_object.h"
#include <stdlib.h>
#include <stdio.h>

#include "s3d/ui/colors.h"
#include "s3d/ui/button.h"
#include "s3d/ui/label.h"
#include "s3d/ui/textfield.h"
#include "s3d/ui/image.h"
#include "s3d/ui/panel.h"
#include "s3d/ui/checkbox.h"
#include "s3d/ui/radiobutton.h"


static void event(void * sender, const void * evt) {
    Button * btn = (Button*) sender;
    btn->background.red = 0.6;
    Render_scale(0.5, 1);
}

int main(int argc, char **argv) {
    CORE core = CORE_DEFAULT_CONIFG;
    sprintf(core.windonw_title, "%s", "Engine");
    CORE_init(argc, argv, &core);
    core.clearColor = UI_BG_COLOR;

    Context contx;
    Context_init(&contx);
    CORE_setContext(&contx);


    Panel * pan;
    pan = Panel_create(10, 10, 300, 400);
    E_Obj_insertToList(contx.gameData, (E_Obj*) pan);

    Button * btn;
    char buffer[255];
    for(int i = 0; i < 7; ++i) {
        sprintf(buffer, "Button %d", i);
        btn = Button_create(-40 + i * 10, 20 + i * 50, 100, 40, buffer);
        btn->events.mousePressAction = event;
        //E_Obj_insertToList(contx.gameData, (E_Obj*) btn);
        Panel_insertChild(pan, (E_Obj*) btn);
    }

    CheckBox * cb;
    cb = CheckBox_create(110, 10, 20, true, "CheckBox 1");
    //E_Obj_insertToList(contx.gameData, (E_Obj*) cb);
    Panel_insertChild(pan, (E_Obj*) cb);


    RadioButtonGroup * group = RadioButtonGroup_create();
    RadioButton * rb;
    for(int i = 0; i < 3; ++i) {
        sprintf(buffer, "RadioBtn %d", i);
        rb = RadioButton_create(110, 50 + i * 30, 20, false, buffer);
        //E_Obj_insertToList(contx.gameData, (E_Obj*) cb);
        RadioButtonGroup_add(group, rb);
        Panel_insertChild(pan, (E_Obj*) rb);
    }

    CORE_run();

    return 0;
}

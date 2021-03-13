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

#include "engine2d/core.h"
#include "engine2d/ui/button.h"
#include "engine2d/ui/label.h"
#include "engine2d/ui/textfield.h"
#include <stdlib.h>
#include <stdio.h>

static void event(void * sender, void * evt) {
    Button * btn = (Button*) sender;
    btn->background.red = 0.6;
    Render_scale(0.5, 1);
}

static void event2(void * sender, void * evt) {
    Button * btn = (Button*) sender;
    btn->foreground.green = 0.6;
}

int main(int argc, char **argv) {

    CORE core = CORE_DEFAULT_CONIFG;
    core.windonw_title = "Engine";
    CORE_init(argc, argv, &core);
    Context contx;
    Context_init(&contx);
    CORE_setContext(&contx);

    E_Obj * obj;

    Label * lab;
    lab = Label_create(100, 50, "Label");
    obj = Label_createObject(lab);
    E_Obj_insertToList(contx.gameData, obj);

    TextField * tf;
    tf = TextField_create(300, 50, 200, 40, 255);
    sprintf(tf->text, "%s", "textfield");
    obj = TextField_createObject(tf);
    E_Obj_insertToList(contx.gameData, obj);

    Button * btn;
    char buffer[255];
    for(int i = 0; i < 7; ++i) {
        sprintf(buffer, "Button %d", i);
        btn = Button_create(100, 100 + i * 50, 100, 40, buffer);
        btn->events.mousePressAction = event;
        btn->events.mouseMovedAction = event2;
        obj = Button_createObject(btn);
        E_Obj_insertToList(contx.gameData, obj);
    }

    CORE_loadTexture("data/img.bmp");

    CORE_run();
    CORE_destruct();

    return 0;
}

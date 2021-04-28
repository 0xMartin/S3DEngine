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

#include "s3d/ui/button.h"
#include "s3d/ui/label.h"
#include "s3d/ui/textfield.h"
#include "s3d/ui/image.h"


static void event(void * sender, const void * evt) {
    Button * btn = (Button*) sender;
    btn->background.red = 0.6;
    Render_scale(0.5, 1);
}

static void event2(void * sender, const void * evt) {
    Button * btn = (Button*) sender;
    btn->foreground.green = 0.6;
}

int main(int argc, char **argv) {
    CORE core = CORE_DEFAULT_CONIFG;
    sprintf(core.windonw_title, "%s", "Engine");
    CORE_init(argc, argv, &core);

    Context contx;
    Context_init(&contx);
    CORE_setContext(&contx);


    Label * lab;
    lab = Label_create(100, 50, "Label");
    E_Obj_insertToList(contx.gameData, (E_Obj*) lab);

    TextField * tf;
    tf = TextField_create(300, 50, 200, 40, 255);
    sprintf(tf->text, "%s", "textfield");
    E_Obj_insertToList(contx.gameData, (E_Obj*) tf);

    Image * img;
    Texture * texture1;
    CORE_loadTexture("data/img.bmp", &texture1);
    img = Image_create(400, 300, IMAGE_SIZE_AUTO, IMAGE_SIZE_AUTO, texture1);
    E_Obj_insertToList(contx.gameData, (E_Obj*) img);

    Button * btn;
    char buffer[255];
    for(int i = 0; i < 7; ++i) {
        sprintf(buffer, "Button %d", i);
        btn = Button_create(100, 100 + i * 50, 100, 40, buffer);
        btn->events.mousePressAction = event;
        btn->events.mouseMovedAction = event2;
        E_Obj_insertToList(contx.gameData, (E_Obj*) btn);
    }

    CORE_run();
    CORE_destruct();

    return 0;
}

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
#include <stdlib.h>
#include <stdio.h>

static void event(void * sender) {
    (void) sender;
    printf("ahoj\n");
}

int main(int argc, char **argv) {

    CORE core = CORE_DEFAULT_CONIFG;
    core.windonw_title = "Engine";

    CORE_init(argc, argv, &core);

    Context contx;
    Context_init(&contx);
    CORE_setContext(&contx);

    E_Obj * obj;
    E2_Button * btn;

    btn = E2_Button_create(100, 100, 100, 40, "Button 1", event);
    obj = E2_Button_createObject(btn);
    E_Obj_insertToList(contx.gameData, obj);

    CORE_run();
    CORE_destruct();

    return 0;
}

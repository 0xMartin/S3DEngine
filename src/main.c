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
#include <stdlib.h>

int main(int argc, char **argv) {

    CORE core = CORE_DEFAULT_CONIFG;
    core.windonw_title = "TicTacToe";

    CORE_init(argc, argv, &core);

    Context contx;
    Context_init(&contx);
    CORE_setContex(&contx);

    CORE_run();
    CORE_destruct();

    return 0;
}

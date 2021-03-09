/**
 * <------------------------------------------------------------------>
 * @name    TicTacToe
 * @author  Martin Krcma
 * @date    28. 2. 2021
 * <------------------------------------------------------------------>
 * @file    player.h
 * @brief
 * <------------------------------------------------------------------>
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "../engine2d/engine_object.h"
#include "../engine2d/ai.h"

#include <stdbool.h>


typedef struct {
    unsigned int score;
    char * name;
    AI * ai;
    E_Obj * token;
} Player;


/**
 * @brief Player_init
 * @param player
 * @return
 */
bool Player_init(Player * player);

/**
 * @brief Player_Destruct
 * @param player
 */
void Player_Destruct(Player * player);


#endif // PLAYER_H

/**
 * <------------------------------------------------------------------>
 * @name    TicTacToe
 * @author  Martin Krcma
 * @date    28. 2. 2021
 * <------------------------------------------------------------------>
 * @file    game.h
 * @brief
 * <------------------------------------------------------------------>
 */

#ifndef GAME_H
#define GAME_H

#include "../engine2d/engine_object.h"
#include "player.h"

#include <stdbool.h>

typedef struct {
    unsigned int row;
    unsigned int cols;
    E_Obj * tiles;
    E_Obj * line;
} Board;


typedef struct _Game {
    bool firstOnTurn;
    Player * winner;
    Player * player1;
    Player * player2;
    Board * board;

    void (*render)(struct _Game * game);
    void (*update)(struct _Game * game);
} Game;


/**
 * @brief GAME_init
 * @param game
 * @param player1
 * @param player2
 * @param size
 * @return
 */
bool GAME_init(Game * game, Player * player1, Player * player2, unsigned int size);

/**
 * @brief GAME_destruct
 * @param game
 */
void GAME_destruct(Game * game);

/**
 * @brief GAME_reset
 * @param game
 */
void GAME_reset(Game * game);

/**
 * @brief GAME_checkForWin
 * @param game
 */
void GAME_checkForWin(Game * game);

#endif // GAME_H

#ifndef BOARD_H
#define BOARD_H

#include "../includes.h"
#include "../move/move.h"
#include "../piece/piece.h"

void init_board(board_t board);
void update_board(board_t board, move_t move);


#endif

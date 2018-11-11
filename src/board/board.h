#ifndef BOARD_H
#define BOARD_H

#include "../includes.h"
#include "../move/move.h"
#include "../piece/piece.h"

extern char char_board[8][8];
void init_board(board_t board, char cha_board[][8]);


#endif

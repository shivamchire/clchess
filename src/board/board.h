#ifndef BOARD_PIECES_H
#define BOARD_PIECES_H

#include "includes.h"
#include "list/g_slnl.h"
#include "pieces_list.h"
#define ABS(x) ((x) > 0 ? (x) : (-(x)))
#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define MIN(x, y) ((x) < (y) ? (x) : (y))


void init_board();
void update_board(move_t move);

move_t conv_str_move(char *move);
#endif

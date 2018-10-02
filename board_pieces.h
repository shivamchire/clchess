#ifndef BOARD_PIECES_H
#define BOARD_PIECES_H

#include "includes.h"

typedef struct move {
	int src;
	int src_rank;
	int dest;
	int dest_rank;
} move_t;
extern char board[8][9];
void update_board(move_t move);
move_t conv_str_move(char *move);

#endif

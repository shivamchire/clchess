#ifndef BOARD_PIECES_H
#define BOARD_PIECES_H

#include "includes.h"
#define ABS(x) ((x) > 0 ? (x) : (-(x)))
#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define MIN(x, y) ((x) < (y) ? (x) : (y))

typedef struct move {
	int src;
	int src_rank;
	int dest;
	int dest_rank;
} move_t;
enum ps {P, B, N, R, Q, K, p, b, n, r, q, k};
enum pieces {PAWN, BISHOP, NIGHT, ROOK, QUEEN, KING, pawn, bishop, night, rook, queen, king};

extern char board[8][9];
void update_board(move_t move);
move_t conv_str_move(char *move);
/*
 * check if there is pieces in between the two tiles between which movement of
 * some other piece is going to take place
 * retval
 * 	1 - yes there is piece in btw
 * 	0 - no
 * 	-1- invalid move
 */
int inbtw(move_t move);

#endif

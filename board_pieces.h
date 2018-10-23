#ifndef BOARD_PIECES_H
#define BOARD_PIECES_H

#include "includes.h"
#include "list/g_slnl.h"
#include "pieces_list.h"
#define ABS(x) ((x) > 0 ? (x) : (-(x)))
#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define MIN(x, y) ((x) < (y) ? (x) : (y))

//stores pos of board
//x = cols
//y = ranks
typedef struct pos {
	unsigned x;
	unsigned y;
}pos_t;


typedef struct pawn {
	bool enpassant;
	bool twomoves;
	bool pin;
}pawn_t;

typedef struct bishop {
	bool pin;
}bishop_t;

typedef struct night {
	bool pin;
}night_t;

typedef struct rook {
	bool pin;
}rook_t;

typedef struct queen {
	bool pin;
}queen_t;

typedef struct king {
	bool castle;
	int last_man_standing;
	bool check;
}king_t;

typedef list_t piece_list_t;
//this struct will be use as node in list which is in struct of each piece_type
//eg: protected_by, protecting, attack_by, attacking
//and also in board[]
typedef struct piece {
	char piece;
	pos_t pos;
	void *ptr;//pointing to type of piece and there special properties
	piece_list_t protected_by, protecting, attack_by, attacking;
}piece_t;

typedef struct move {
	int src;
	int src_rank;
	int dest;
	int dest_rank;
}move_t;

extern piece_t *(board[8][8]);
void init_board();
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

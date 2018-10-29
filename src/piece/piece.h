#ifndef PIECES_H
#define PIECES_H


#include "includes.h"
#include "list/g_slnl.h"
#include "pieces_list.h"
#define ABS(x) ((x) > 0 ? (x) : (-(x)))
#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define MIN(x, y) ((x) < (y) ? (x) : (y))

#define WHITE 1
#define BLACK 0
#define COLOR_Mask 1
#define COLOR(x) ((x) & COLOR_Mask)

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

extern piece_t *(board[8][8]);

#endif

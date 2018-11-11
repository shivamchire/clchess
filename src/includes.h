#ifndef INCLUDES_H
#define INCLUDES_H

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include "debug.h"
#include "piece/list/slnl.h"
#define ABS(x) ((x) > 0 ? (x) : (-(x)))
#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define MIN(x, y) ((x) < (y) ? (x) : (y))
//stores pos of board
//x = cols
//y = ranks
typedef struct pos {
	int x;
	int y;
}pos_t;
typedef list_t piece_list_t;
//this struct will be use as node in list which is in struct of each piece_type
//eg: protected_by, protecting, attack_by, attacking
//and also in board[]
typedef struct piece {
	char piece;
	pos_t pos;
	uint64_t bitpiece;
	piece_list_t protected_by, protecting, attack_by, attacking;
}piece_t;

typedef piece_t *** board_t;

typedef struct move {
	int x1;
	int y1;
	int x2;
	int y2;
}move_t;

typedef struct chess {
	uint8_t player;
	board_t board;
	move_t move;
	piece_t *captured_piece;
	piece_t *wking;
	piece_t *bking;
}chess_t;

#endif

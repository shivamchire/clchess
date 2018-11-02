#include "../includes.h"
#include "../move/move.h"

typedef struct chess {
	uint8_t player;
	board_t board;
	move_t move;
}chess_t;

void init_chess(chess_t *chess);

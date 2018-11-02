#include "chess.h"
#include "../board/board.h"

void init_chess(chess_t *chess) {
	int i;
	chess->player = WHITE;
	chess->board = (piece_t ***)malloc(sizeof(piece_t **) * 8);
	for(i = 0; i < 8; i++) {
		chess->board[i] = (piece_t **)malloc(sizeof(piece_t *) * 8);
	}
	init_board(chess->board);
}

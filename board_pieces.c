#include "board_pieces.h"
#include <string.h>

/*
 * capital = white, small = black
 * R, r = Rook
 * N, n = Knight
 * B, b = Bishop
 * Q, q = Queen
 * K, k = King
 * P, p = pawn
 */
char board[8][9] = {
	{'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'},
	{'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
	{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
	{'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'}
};

/*
 * convert to structred move
 * only accept moves in following format
 * 	e 2	 e 4 (without spaces)
 * 	starting ending
 * 	address	 address
 * no caps allowed
 * return structure_move
 * and set str_move.src to -1 if invalid move(out of board bound move)
 */
move_t conv_str_move(char *move) {

	move_t str_move;
	if(move[0] >= 'a' && move[0] <= 'h' &&
	   move[1] >= '1' && move[1] <= '8' &&
	   move[2] >= 'a' && move[2] <= 'h' &&
	   move[3] >= '1' && move[3] <= '8') {
		str_move.src = move[0] - 'a';
		str_move.src_rank = move[1] - '0' - 1;
		str_move.dest = move[2] - 'a';
		str_move.dest_rank = move[3] - '0' - 1;
	}
	else {
		str_move.src = -1;
	}
	return str_move;
}

/*
 * update board according to move
 */
void update_board(move_t move) {
	char tmp = board[move.src_rank][move.src];
	board[move.src_rank][move.src] = ' ';
	board[move.dest_rank][move.dest] = tmp;
}

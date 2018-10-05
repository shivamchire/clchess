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
	board[move.dest_rank][move.dest]= board[move.src_rank][move.src];
	board[move.src_rank][move.src] = ' ';
}
/*
 * check if there is pieces in between the two tiles between which movement of
 * some other piece is going to take place
 * retval
 * 	1 - yes there is piece in btw
 * 	0 - no
 * 	-1- invalid move
 */
int inbtw(move_t move) {
	int i, j;
	int min_rank = MIN(move.src_rank, move.dest_rank),
	    max_rank = MAX(move.src_rank, move.dest_rank),
	    min_col = MIN(move.src, move.dest),
	    max_col = MAX(move.src, move.dest);
	//no movement
	if(min_col == max_col && min_rank == max_rank) {
		return -1;
	}
	//horizontal movement
	else if(min_rank == max_rank) {
		for(i = min_col + 1; i < max_col; i++) {
			if(board[min_rank][i] != ' ') {
				return 1;
			}
		}
	}
	//vertical movement
	else if(min_col == max_col) {
		for(i = min_rank + 1; i < max_rank; i++) {
			if(board[i][min_col] != ' ') {
				return 1;
			}
		}
	}
	//diagonal movement
	else if(max_col - min_col == max_rank - min_rank) {
		for(i = min_rank + 1, j = min_col + 1; i < max_rank &&
				j < max_col; i++, j++) {
			if(board[i][j] != ' ') {
				return 1;
			}
		}
	}
	//knight movement
	else if((max_rank - min_rank == 2 &&
		max_col - min_col == 1) ||
		(max_col - min_col == 2 &&
		 max_rank - min_rank == 1)) {
		return 0;
	}
	//anything else
	else {
		return -1;
	}
	return 0;
}

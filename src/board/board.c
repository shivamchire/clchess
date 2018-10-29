#include "board_pieces.h"
#include <string.h>


/*
 * first index = rank, second index = col
 * capital = white, small = black
 * R, r = Rook
 * N, n = Knight
 * B, b = Bishop
 * Q, q = Queen
 * K, k = King
 * P, p = pawn
 */
piece_t *(board[8][8]);
char char_board[8][8] = {
	{'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'},
	{'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
	{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
	{'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'}
};
void init_board() {

	print4("Initializing board\n");
	pos_t pos;
	int i, j;
	print3("Making structure for all pieces\n");
	for(i = 0; i < 8; i++) {
		for(j = 0; j < 8; j++) {
			if(char_board[i][j] != ' ') {
				board[i][j] = (piece_t *)malloc(sizeof(piece_t));
				pos.x = j;
				pos.y = i;
				init_piece(board[i][j], char_board[i][j], pos);
			}
			else {
				board[i][j] = NULL;
			}
		}
	}
}


/*
 * update board according to move
 */
void update_board(move_t move) {
	board[move.dest_rank][move.dest] = board[move.src_rank][move.src];
	board[move.src_rank][move.src] = NULL;
}

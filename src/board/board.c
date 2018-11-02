#include <string.h>
#include "board.h"


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
char char_board[8][8] = {
	{'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'},
	{'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
	{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
	{'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}
};
void init_board(board_t board) {

	print4("Initializing board");
	pos_t pos;
	int i, j;
	print3("Making structure for all pieces");
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
void update_board(board_t board, move_t move) {
	print2("Updating board");
	piece_t *src_piece = board[move.y1][move.x1];
	pos_t pos;
	pos.x = move.x2;
	pos.y = move.y2;
	src_piece->pos = pos;
	//TODO destroy dest_piece
	board[move.y2][move.x2] = board[move.y1][move.x1];
	board[move.y1][move.x1] = NULL;
}

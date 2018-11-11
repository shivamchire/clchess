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
	{'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'},
	{'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
	{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
	{'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'}
};
void init_board(board_t board, char cha_board[][8]) {
	print4("Initializing board");
	pos_t pos;
	int i, j;
	print3("Making structure for all pieces");
	for(i = 0; i < 8; i++) {
		for(j = 0; j < 8; j++) {
			if(cha_board[i][j] != ' ') {
				board[i][j] = (piece_t *)malloc(sizeof(piece_t));
				pos.x = j;
				pos.y = i;
				init_piece(board[i][j], cha_board[i][j], pos);
			}
			else {
				board[i][j] = NULL;
			}
		}
	}
}

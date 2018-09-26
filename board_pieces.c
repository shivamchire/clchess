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

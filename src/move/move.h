#ifndef MOVE_H
#define MOVE_H

#include "../includes.h"

typedef struct move {
	int x1;
	int y1;
	int x2;
	int y2;
}move_t;

/*
 * check if there is pieces in between the two tiles between which movement of
 * some other piece is going to take place
 * retval
 * 	1 - yes there is piece in btw
 * 	0 - no
 * 	-1- invalid move
 */
int inbtw(board_t board, move_t move);
move_t conv_str_move(char *move);
bool vertical(move_t move);
bool horizontal(move_t move);
bool diagonal(move_t move);
bool nightmove(move_t move);
bool invalid(move_t move);
extern bool (* move_mat[8][8])(move_t);
int islegal(board_t board, move_t move);



#endif

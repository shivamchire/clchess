#ifndef MOVE_H
#define MOVE_H

#include "../includes.h"

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
extern bool (*move_mat[15][15])(piece_t *piece, int x, int y);
int islegal(chess_t *chess, int tocheckmate);
bool pvevertical(piece_t *piece, int x, int y);
bool nvevertical(piece_t *piece, int x, int y);
bool pvehorizontal(piece_t *piece, int x, int y);
bool nvehorizontal(piece_t *piece, int x, int y);
bool nwdiag(piece_t *piece, int x, int y);
bool nediag(piece_t *piece, int x, int y);
bool swdiag(piece_t *piece, int x, int y);
bool sediag(piece_t *piece, int x, int y);
bool nightnwmove(piece_t *piece, int x, int y);
bool nightnemove(piece_t *piece, int x, int y);
bool nightswmove(piece_t *piece, int x, int y);
bool nightsemove(piece_t *piece, int x, int y);
bool nightwnmove(piece_t *piece, int x, int y);
bool nightenmove(piece_t *piece, int x, int y);
bool nightwsmove(piece_t *piece, int x, int y);
bool nightesmove(piece_t *piece, int x, int y);
bool invalid(piece_t *piece, int x, int y);


#endif

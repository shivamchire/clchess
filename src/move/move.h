#ifndef MOVE_H
#define MOVE_H

//stores pos of board
//x = cols
//y = ranks
typedef struct pos {
	unsigned x;
	unsigned y;
}pos_t;


typedef struct move {
	int src;
	int src_rank;
	int dest;
	int dest_rank;
}move_t;

/*
 * check if there is pieces in between the two tiles between which movement of
 * some other piece is going to take place
 * retval
 * 	1 - yes there is piece in btw
 * 	0 - no
 * 	-1- invalid move
 */
int inbtw(move_t move);

#endif

#include "move.h"
#include "../piece/piece.h"
#include "../error/err.h"
bool (*move_mat[8][8])(move_t) = {
	{invalid, horizontal, horizontal, horizontal, horizontal, horizontal, horizontal, horizontal },
	{vertical, diagonal, nightmove, invalid, invalid, invalid, invalid, invalid },
	{vertical, nightmove, diagonal, invalid, invalid, invalid, invalid, invalid },
	{vertical, invalid, invalid, diagonal, invalid, invalid, invalid, invalid },
	{vertical, invalid, invalid, invalid, diagonal, invalid, invalid, invalid },
	{vertical, invalid, invalid, invalid, invalid, diagonal, invalid, invalid },
	{vertical, invalid, invalid, invalid, invalid, invalid, diagonal, invalid },
	{vertical, invalid, invalid, invalid, invalid, invalid, invalid, diagonal }
};
/*
 * convert to structred move
 * only accept moves in following format
 * 	e 2	 e 4 (without spaces)
 * 	starting ending
 * 	address	 address
 * no caps allowed
 * return structure_move
 * and set str_move.x1 to -1 if invalid move(out of board bound move)
 */
move_t conv_str_move(char *move) {

	move_t str_move;
	if(move[0] >= 'a' && move[0] <= 'h' &&
	   move[1] >= '1' && move[1] <= '8' &&
	   move[2] >= 'a' && move[2] <= 'h' &&
	   move[3] >= '1' && move[3] <= '8') {
		str_move.x1 = move[0] - 'a';
		str_move.y1 = 7 - (move[1] - '0' - 1);// 7- since board in array
						    // is opposite of what gets printed
		str_move.x2 = move[2] - 'a';
		str_move.y2 = 7 - (move[3] - '0' - 1);
	}
	else {
		str_move.x1 = -1;
	}
	vprint1("src (%c, %d) dest (%c, %d)", str_move.x1 + 'a', str_move.y1,
		       				str_move.x2 + 'a', str_move.y2);
	return str_move;
}

/*
 * check if there is pieces in between the two tiles between which movement of
 * some other piece is going to take place
 * retval
 * 	1 - yes there is piece in btw
 * 	0 - no
 * 	-1- invalid move
 */
int inbtw(board_t board, move_t move) {
	int i, j;
	int min_rank = MIN(move.y1, move.y2),
	    max_rank = MAX(move.y1, move.y2),
	    min_col = MIN(move.x1, move.x2),
	    max_col = MAX(move.x1, move.x2);
	//no movement
	if(min_col == max_col && min_rank == max_rank) {
		return -1;
	}
	//horizontal movement
	else if(min_rank == max_rank) {
		for(i = min_col + 1; i < max_col; i++) {
			if(board[min_rank][i] != NULL) {
				return 1;
			}
		}
	}
	//vertical movement
	else if(min_col == max_col) {
		for(i = min_rank + 1; i < max_rank; i++) {
			if(board[i][min_col] != NULL) {
				return 1;
			}
		}
	}
	//diagonal movement
	else if(max_col - min_col == max_rank - min_rank) {
		for(i = min_rank + 1, j = min_col + 1; i < max_rank &&
				j < max_col; i++, j++) {
			if(board[i][j] != NULL) {
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

int islegal(board_t board, move_t move) {
	piece_t *src_piece = board[move.y1][move.x1];
	piece_t *dest_piece = board[move.y2][move.x2];
	bool (* ptr)(move_t) = move_mat[ABS(move.y1 - move.y2)]
					[ABS(move.x1 - move.x2)];
	if(!src_piece) {
		print2("No piece at starting tile");
		return ENOPIECE;
	}
	else if(GetPin(src_piece->bitpiece)) {
		print2("Piece Pin");
		return EPIN;
	}
	//check if capture of same side
	if(dest_piece && (~(COLOR(src_piece->bitpiece) ^ COLOR(dest_piece->bitpiece)))) {
		print2("You cant capture your own piece");
		return EOWNCAP;
	}
	return ptr(move);
}

bool vertical(move_t move) {
	print1("In Vertical");
	if(x > 0) {
		return GetVPveField(piece->bitpiece) >= x;
	}
	else {
		return GetVNveField(piece->bitpiece) >= -x;
	}
}
bool horizontal(move_t move) {
	print1("In horizontal");
	if(x > 0) {
		return GetHPveField(piece->bitpiece) >= x;
	}
	else {
		return GetHNveField(piece->bitpiece) >= -x;
	}
}
bool diagonal(move_t move) {
	print1("In diagonal");
	if(x > 0) {
		return GetVPveField(piece->bitpiece) >= x;
	}
	else {
		return GetVNveField(piece->bitpiece) >= -x;
	}
	return 0;
}
bool invalid(move_t move) {
	print1("in invalid");
	return 1;
}
bool nightmove(move_t move) {
	print1("in nightmove");
	return 0;
}

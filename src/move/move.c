#include "move.h"
#include "../piece/piece.h"
#include "../error/err.h"
bool (*move_mat[15][15])(piece_t *piece, int x, int y) = {
	{ swdiag, invalid, invalid, invalid, invalid, invalid, invalid, nvevertical, invalid, invalid, invalid, invalid, invalid, invalid, sediag },
	{ invalid, swdiag, invalid, invalid, invalid, invalid, invalid, nvevertical, invalid, invalid, invalid, invalid, invalid, sediag, invalid },
	{ invalid, invalid, swdiag, invalid, invalid, invalid, invalid, nvevertical, invalid, invalid, invalid, invalid, sediag, invalid, invalid },
	{ invalid, invalid, invalid, swdiag, invalid, invalid, invalid, nvevertical, invalid, invalid, invalid, sediag, invalid, invalid, invalid },
	{ invalid, invalid, invalid, invalid, swdiag, invalid, invalid, nvevertical, invalid, invalid, sediag, invalid, invalid, invalid, invalid },
	{ invalid, invalid, invalid, invalid, invalid, swdiag, nightswmove, nvevertical, nightsemove, sediag, invalid, invalid, invalid, invalid, invalid },
	{ invalid, invalid, invalid, invalid, invalid, nightwsmove, swdiag, nvevertical, sediag, nightesmove, invalid, invalid, invalid, invalid, invalid },
	{ nvehorizontal, nvehorizontal, nvehorizontal, nvehorizontal, nvehorizontal, nvehorizontal, nvehorizontal, invalid, pvehorizontal, pvehorizontal, pvehorizontal, pvehorizontal, pvehorizontal, pvehorizontal, pvehorizontal},
	{ invalid, invalid, invalid, invalid, invalid, nightwnmove, nwdiag, pvevertical, nediag, nightenmove, invalid, invalid, invalid, invalid, invalid },
	{ invalid, invalid, invalid, invalid, invalid, nwdiag, nightnwmove, pvevertical, nightnemove, nediag, invalid, invalid, invalid, invalid, invalid },
	{ invalid, invalid, invalid, invalid, nwdiag, invalid, invalid, pvevertical, invalid, invalid, nediag, invalid, invalid, invalid, invalid },
	{ invalid, invalid, invalid, nwdiag, invalid, invalid, invalid, pvevertical, invalid, invalid, invalid, nediag, invalid, invalid, invalid },
	{ invalid, invalid, nwdiag, invalid, invalid, invalid, invalid, pvevertical, invalid, invalid, invalid, invalid, nediag, invalid, invalid },
	{ invalid, nwdiag, invalid, invalid, invalid, invalid, invalid, pvevertical, invalid, invalid, invalid, invalid, invalid, nediag, invalid },
	{ nwdiag, invalid, invalid, invalid, invalid, invalid, invalid, pvevertical, invalid, invalid, invalid, invalid, invalid, invalid, nediag },
};
bool (**move_mat_mid)(piece_t*, int, int) = &(move_mat[7][7]);
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
		str_move.y1 = (move[1] - '0' - 1);// 7- since board in array
						    // is opposite of what gets printed
		str_move.x2 = move[2] - 'a';
		str_move.y2 = (move[3] - '0' - 1);
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
	int x = move.x2 - move.x1;
	int y = move.y2 - move.y1;
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
//TODO for any move after checking if that move is doable create a second chess
//instance do that move in that chess instance and see if king is under check
//TODO handle castling
int islegal(chess_t *chess) {
	board_t board = chess->board;
	move_t move = chess->move;
	piece_t *src_piece = board[move.y1][move.x1];
	piece_t *dest_piece = board[move.y2][move.x2];
	int x = move.x2 - move.x1;
	int y = move.y2 - move.y1;
	bool (*ptr)(piece_t*, int, int) = move_mat[7 + y]
					[7 + x];
	if(!src_piece) {
		print3("No piece at starting tile");
		return ENOPIECE;
	}
	else if(GetPin(src_piece->bitpiece)) {
		print3("Piece Pin\n");
		return EPIN;
	}
	else if(COLOR(src_piece->bitpiece) ^ chess->player) {
		print3("Play with your own piece");
		return EWCOL;
	}
	//check if capture of same side
	if(dest_piece && (!(COLOR(src_piece->bitpiece) ^ COLOR(dest_piece->bitpiece)))) {
		print3("You cant capture your own piece");
		return EOWNCAP;
	}
	return ptr(src_piece, x, y);
}

bool pvevertical(piece_t *piece, int x, int y) {
	vprint1("%lx %ld", GetVPveField(piece->bitpiece), (uint64_t)y);
	return !(GetVPveField(piece->bitpiece) >= (uint64_t)y);
}
bool nvevertical(piece_t *piece, int x, int y) {
	print1();
	vprint1("%lx %ld", GetVNveField(piece->bitpiece), (uint64_t)-y);
	return !(GetVNveField(piece->bitpiece) >= (uint64_t)-y);
}
bool pvehorizontal(piece_t *piece, int x, int y) {
	print1();
	return !(GetHPveField(piece->bitpiece) >= (uint64_t)x);
}
bool nvehorizontal(piece_t *piece, int x, int y) {
	print1();
	return !(GetHNveField(piece->bitpiece) >= (uint64_t)-x);
}
bool nwdiag(piece_t *piece, int x, int y) {
	print1();
	return !(GetDNWField(piece->bitpiece) >= (uint64_t)y);
}
bool nediag(piece_t *piece, int x, int y) {
	print1();
	return !(GetDNEField(piece->bitpiece) >= (uint64_t)y);
}
bool swdiag(piece_t *piece, int x, int y) {
	print1();
	return !(GetDSWField(piece->bitpiece) >= (uint64_t)-y);
}
bool sediag(piece_t *piece, int x, int y) {
	print1();
	return !(GetDSEField(piece->bitpiece) >= (uint64_t)x);
}
bool nightnwmove(piece_t *piece, int x, int y) {
	return GetNightNW(piece->bitpiece) ^ (NightNWMsk >> NightNWPos);
}
bool nightnemove(piece_t *piece, int x, int y) {
	print1();
	return GetNightNE(piece->bitpiece) ^ (NightNEMsk >> NightNEPos);
}
bool nightswmove(piece_t *piece, int x, int y) {
	print1();
	return GetNightSW(piece->bitpiece) ^ (NightSWMsk >> NightSWPos);
}
bool nightsemove(piece_t *piece, int x, int y) {
	print1();
	return GetNightSE(piece->bitpiece) ^ (NightSEMsk >> NightSEPos);
}
bool nightwnmove(piece_t *piece, int x, int y) {
	print1();
	return GetNightWN(piece->bitpiece) ^ (NightWNMsk >> NightWNPos);
}
bool nightenmove(piece_t *piece, int x, int y) {
	print1();
	return GetNightEN(piece->bitpiece) ^ (NightENMsk >> NightENPos);
}
bool nightwsmove(piece_t *piece, int x, int y) {
	print1();
	return GetNightWS(piece->bitpiece) ^ (NightWSMsk >> NightWSPos);
}
bool nightesmove(piece_t *piece, int x, int y) {
	print1();
	return GetNightES(piece->bitpiece) ^ (NightESMsk >> NightESPos);
}

bool invalid(piece_t *piece, int x, int y) {
	print1("in invalid");
	return 1;
}

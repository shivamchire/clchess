#include "board_pieces.h"
#include <string.h>

void init_pawn_t(pawn_t *ptr) {
	ptr->enpassant = 0;
	ptr->twomoves = 1;
	ptr->pin = 0;
}

void init_bishop_t(bishop_t *ptr) {
	ptr->pin = 0;
}
void init_night_t(night_t *ptr) {
	ptr->pin = 0;
}
void init_rook_t(rook_t *ptr) {
	ptr->pin = 0;
}
void init_queen_t(queen_t *ptr) {
	ptr->pin = 0;
}
void init_king_t(king_t *ptr) {
	ptr->castle = 1;
	ptr->check = 0;
	ptr->last_man_standing = 0;
}
void init_piece(piece_t *piece, char p, pos_t pos) {
	switch(p) {
		case 'p': case 'P':
			piece->ptr = malloc(sizeof(pawn_t));
			init_pawn_t((pawn_t *)piece->ptr);
			break;
		case 'B': case 'b':
			piece->ptr = malloc(sizeof(bishop_t));
			init_bishop_t((bishop_t *)piece->ptr);
			break;
		case 'N': case 'n':
			piece->ptr = malloc(sizeof(night_t));
			init_night_t((night_t *)piece->ptr);
			break;
		case 'R': case 'r':
			piece->ptr = malloc(sizeof(rook_t));
			init_rook_t((rook_t *)piece->ptr);
			break;
		case 'Q': case 'q':
			piece->ptr = malloc(sizeof(queen_t));
			init_queen_t((queen_t *)piece->ptr);
			break;
		case 'K': case 'k':
			piece->ptr = malloc(sizeof(king_t));
			init_king_t((king_t *)piece->ptr);
			break;
		default:
			//free all malloc mem and return
			break;
	}
	if(p != ' ') {
		piece->piece = p;
		piece->pos = pos;
		vprint2("Initializing piecelist for %c\n", p);
		init_piece_list(&(piece->protected_by));
		init_piece_list(&(piece->protecting));
		init_piece_list(&(piece->attack_by));
		init_piece_list(&(piece->attacking));
	}
}

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
	vprint1("src (%c, %d) dest (%c, %d)\n", str_move.src + 'a', str_move.src_rank,
		       				str_move.dest + 'a', str_move.dest_rank);
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

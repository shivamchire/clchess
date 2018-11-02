#include <stdint.h>
#include "piece.h"
#include "../board/board.h"
#include "list/g_slnl.h"


//---- for piece list ----
void init_piece_list(piece_list_t* l) {
	init(l, sizeof(piece_t *));
}

void insert_piece(piece_list_t *l, piece_t *p) {
	insert(l, p, 0);
}

void delete_piece(piece_list_t *l, size_t pos) {
	free(remov(l, pos));
}

piece_t *get_next(piece_list_t *l) {
	static piece_list_t *prev_list = NULL;
	static size_t pos = 1;
	if(l) {
		prev_list = l;
		pos = 1;
	}
	piece_t *piece = (piece_t *)see(l, pos);
	pos++;
	return piece;
}

void destroy_piece_list(piece_list_t *l) {
	destroy(l);
}
const short xaxis[] = { 1, 1, 0, -1, -1, -1, 0, 1 };
const short yaxis[] = { 0, 1, 1, 1, 0, -1, -1, -1 };
//const short bit_shiftpos[] = { HoriFieldPvePos, DiagNEPos, VertFieldPvePos, DiagNWPos,
//			HoriFieldNvePos, DiagSWPos, VertFieldNvePos, DiagSEPos };
//const unsigned long long field_msk[] = { HoriPveMsk, DiagNEMsk, VertPveMsk, DiagNWMsk,
//			HoriNveMsk, DiagSWMsk, VertNveMsk, DiagSEMsk };
/*void gen_list(piece_t *piece) {
	int ind, changex, changey, i, j;
	for(ind = 0; ind < 8; ind++) {
		changex = xaxis[ind];
		changey = yaxis[ind];
		//see for nearest piece in the direction of changex and changey
		for(i = changex, j = changey;
		(i + piece->pos.x) < 8 && (j + piece->pos.y) < 8 && (i + piece->pos.x) >= 0 && (j + piece->pos.y) >= 0;
		 i += changex, j += changey) {
			if(board[j + piece->pos.y][i + piece->pos.x])
				break;
		}
		//can get out this loop by
		//same side piece encouter - update protecting and protected by and move i/j - 1
		//opposite side piece encounter - update attacking and attack by and move i/j
		//end of board - move i/j - 1
		switch(ind) {
			case 0:
				if(GetH(piece->bitpiece)) {
					switch(piece->piece & PieceMsk) {
						case King:
							if(i == 2 || i == 3) {		//for castling
								if(piece->pos.x + i < 8 && piece->pos.x + i >= 0 && board[piece->pos.y][piece->pos.x + i]) {
									if(board[piece->pos.y][piece->pos.x + i]->bitpiece && PieceMsk == Rook







}
*/
//---- for piece list ----

void init_piece(piece_t *piece, char p, pos_t pos) {
	switch(p) {
		case 'P':
			piece->bitpiece = WPawn | SetVPveField(2);
			break;
		case 'p':
			piece->bitpiece = BPawn | SetVNveField(2);
			break;
		case 'R':
			piece->bitpiece = WRook;
			break;
		case 'r':
			piece->bitpiece = BRook;
			break;
		case 'N':
			piece->bitpiece = WNight | SetNightNE | SetNightNW;
			break;
		case 'n':
			piece->bitpiece = BNight | SetNightSE | SetNightSW;
			break;
		case 'B':
			piece->bitpiece = WBishop;
			break;
		case 'b':
			piece->bitpiece = BBishop;
			break;
		case 'Q':
			piece->bitpiece = WQueen;
			break;
		case 'q':
			piece->bitpiece = BQueen;
			break;
		case 'K':
			piece->bitpiece = WKing;
			break;
		case 'k':
			piece->bitpiece = BKing;
		default:
			vprint2("Invalid piece %c", p);
			break;
	}
	if(p != ' ') {
		piece->piece = p;
		piece->pos = pos;
		vprint2("Initializing piecelist for %c", p);
		init_piece_list(&(piece->protected_by));
		init_piece_list(&(piece->protecting));
		init_piece_list(&(piece->attack_by));
		init_piece_list(&(piece->attacking));
	}
}

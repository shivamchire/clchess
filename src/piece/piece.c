

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

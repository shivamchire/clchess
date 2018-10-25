#include "pieces_list.h"

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

#include "chess.h"
#include "../board/board.h"
#include "../piece/piece.h"

void init_chess(chess_t *chess, char chachessboard[][8]) {
	print3();
	int i, j;
	chess->player = WHITE;
	chess->board = (piece_t ***)malloc(sizeof(piece_t **) * 8);
	for(i = 0; i < 8; i++) {
		chess->board[i] = (piece_t **)malloc(sizeof(piece_t *) * 8);
	}
	board_t board = chess->board;
	chess->captured_piece = NULL;
	chess->move.x1 = 0;
	chess->move.x2 = 0;
	chess->move.y1 = 0;
	chess->move.y2 = 0;
	init_board(chess->board, chachessboard);
	init_piece_list(&chess->white);
	init_piece_list(&chess->black);
	for(i = 0; i < 8; i++) {
		for(j = 0; j < 8; j++) {
			if(board[i][j]) {
				if(board[i][j]->piece == 'K') {
					chess->wking = board[i][j];
				}
				else if(board[i][j]->piece == 'k') {
					chess->bking = board[i][j];
				}
				if(COLOR(board[i][j]->bitpiece) ^ WHITE) {
					insert_piece(&chess->black, board[i][j]);
				}
				else {
					insert_piece(&chess->white, board[i][j]);
				}
				gen_list(chess, board, board[i][j]);
				print_all_list(board[i][j]);
				printpieceinfo(board[i][j]);
			}
		}
	}
//	for(i = 0; i < 8; i++) {
//		for(j = 0; j < 8; j++) {
//			if(board[i][j]) {
//				if(GetPiece(board[i][j]->bitpiece) == Pawn && COLOR(board[i][j]->bitpiece) == WHITE) {
//					SetVPveField(board[i][j], 2);
//				}
//				else if(GetPiece(board[i][j]->bitpiece) == Pawn && COLOR(board[i][j]->bitpiece) == BLACK) {
//					SetVNveField(board[i][j], 2);
//				}
//				printpieceinfo(board[i][j]);
//			}
//		}
//	}

	//TODO initialize 4 list of all pieces for initial piece arrangement
//	//rook protecting horse
//	insert_piece(&(board[7][7]->protecting), board[7][6]);
//	insert_piece(&(board[7][6]->protected_by), board[7][7]);
//	//rook protecting pawn on h2
//	insert_piece(&(board[7][7]->protecting), board[6][7]);
//	insert_piece(&(board[6][7]->protected_by), board[7][7]);
//	//horse protecting pawn on e2
//	insert_piece(&(board[7][6]->protecting), board[6][4]);
//	insert_piece(&(board[6][4]->protected_by), board[7][6]);
//	//bishop protecting pawn on g2
//	insert_piece(&(board[7][5]->protecting), board[6][6]);
//	insert_piece(&(board[6][6]->protected_by), board[7][5]);
//	//bishop protecting pawn on e2
//	insert_piece(&(board[7][5]->protecting), board[6][4]);
//	insert_piece(&(board[6][4]->protected_by), board[7][5]);
//	//king protecting pawn on f2
//	insert_piece(&(board[7][4]->protecting), board[6][5]);
//	insert_piece(&(board[6][5]->protected_by), board[7][4]);
//	//king protecting pawn on e2
//	insert_piece(&(board[][]->protecting), board[][]);
//	insert_piece(&(board[][]->protected_by), board[][]);
//	//king protecting pawn on d2
//	insert_piece(&(board[][]->protecting), board[][]);
//	insert_piece(&(board[][]->protected_by), board[][]);
//	//king protecting queen
//	insert_piece(&(board[][]->protecting), board[][]);
//	insert_piece(&(board[][]->protected_by), board[][]);
//	//king protecting bishop
//	insert_piece(&(board[][]->protecting), board[][]);
//	insert_piece(&(board[][]->protected_by), board[][]);
}
void destroy_chess(chess_t *chess) {
	print3();
	board_t board = chess->board;
	int i, j;
	for(i = 0; i < 8; i++) {
		for(j = 0; j < 8; j++) {
			if(board[i][j]) {
				destroy_piece(board[i][j]);
			}
		}
	}
	destroy_piece_list(&chess->black);
	destroy_piece_list(&chess->white);
}
/*
 * update chess according to move
 */
void update_chess(chess_t *chess) {
	int castling = 0;
	print2("Updating chess");
	board_t board = chess->board;
	move_t move = chess->move;

	piece_t *src_piece = board[move.y1][move.x1];
	chess->captured_piece = board[move.y2][move.x2];
	board[move.y2][move.x2] = board[move.y1][move.x1];
	board[move.y1][move.x1] = NULL;
	pos_t pos;
	pos.x = move.x2;
	pos.y = move.y2;
	src_piece->pos = pos;
	if(GetPiece(src_piece->bitpiece) == Pawn) {
		SetTwoMove(src_piece, 0);
	}
	else if(GetPiece(src_piece->bitpiece) == King) {
		SetCastling(src_piece, 0);
		if((move.x2 - move.x1) == 2) {
			castling = 1;
		}
		else if((move.x2 - move.x1) == -2) {
			castling = 2;
		}
	}
	degen_list(chess, board, src_piece);
	gen_list(chess, board, src_piece);
	if(castling == 1) {
		chess->move.x1 = 7;
		chess->move.y1 = src_piece->pos.y;
		chess->move.x2 = 5;
		chess->move.y2 = src_piece->pos.y;
		update_chess(chess);
	}
	else if(castling == 2) {
		chess->move.x1 = 0;
		chess->move.y1 = src_piece->pos.y;
		chess->move.x2 = 3;
		chess->move.y2 = src_piece->pos.y;
		update_chess(chess);
	}
	//TODO destroy dest_piece
	print_all_list(src_piece);
}
void convertchesstochar(chess_t *chess, char chesscopycha[][8]) {
	print1("creating copy of board");
	board_t board = chess->board;
	int i, j;
	for(i = 0; i < 8; i++) {
		for(j = 0; j < 8; j++) {
			if(board[i][j]) {
				vprint1("copy of %c at (%c, %d)", board[i][j]->piece, Coordinate(board[i][j]));
				chesscopycha[i][j] = board[i][j]->piece;
			}
			else {
				chesscopycha[i][j] = ' ';
			}
		}
	}
}
void creatchesscopy(chess_t *chesscopy, chess_t *chess) {
	print1("Creating chesscopy");
	 char chesscopycha[8][8];
	convertchesstochar(chess, chesscopycha);
	init_chess(chesscopy, chesscopycha);
	chesscopy->player = chess->player;
	chesscopy->move = chess->move;
	if(GetCastling(chess->wking->bitpiece) == 0) {
		SetCastling(chesscopy->wking, 0);
	}
	if(GetCastling(chess->bking->bitpiece) == 0) {
		SetCastling(chesscopy->bking, 0);
	}
}
int checkforcheck(chess_t *chess) {
	print1("checking for check");
	int i = 0, dirx, diry;
	piece_t *piece, *p;
	board_t board = chess->board;
	pos_t pos;
	//white to move and its king is under check
	if(chess->player == WHITE) {
		print1("white king selected for checking");
		piece = chess->wking;
	}
	//black to move and its king is under check
	else {
		print1("black king selected for checking");
		piece = chess->bking;
	}
	if(!isempty(&piece->attack_by)) {
		return 1;
	}
//	print1("searching for slide piece");
//	while(i < 8) {
//		dirx = MoveAlongX[i];
//		diry = MoveAlongY[i];
//		vprint1("dirx %d diry %d", dirx, diry);
//		p = findpiece(board, piece->pos.x, piece->pos.y, dirx, diry, &pos.x, &pos.y);
//		if(p && !(pos.x == piece->pos.x && pos.y == piece->pos.y)) {
//			vprint1("found piece %c at (%c, %d)", p->piece, Coordinate(p));
//			bool (*ptr)(piece_t*, int, int) = move_mat[7 + pos.y - piece->pos.y][7 + pos.x - piece->pos.x];
//			//check if capture of same side
//			if(piece && (!(COLOR(piece->bitpiece) ^ COLOR(p->bitpiece)))) {
//				print1("You cant capture your own piece");
//				i++;
//				continue;
//			}
//			if(!ptr(p, pos.x - piece->pos.x, pos.y - piece->pos.y)) {
//				print1("piece can capture king");
//				return 1;
//			}
//			print1("piece cant capture king");
//		}
//		i++;
//	}
//	i = 0;
//	print1("checking for nightmove");
//	while(i < 8) {
//		dirx = NightMoveAlongX[i];
//		diry = NightMoveAlongY[i];
//		vprint1("dirx %d diry %d", dirx, diry);
//		if(piece->pos.x + dirx < 8 && piece->pos.x + dirx >=0 && piece->pos.y + diry < 8 && piece->pos.y + diry >=0) {
//			p = board[piece->pos.y + diry][piece->pos.x + dirx];
//			if(p) {
//				vprint1("found piece %c at (%c, %d)", p->piece, Coordinate(p));
//				if(GetPiece(p->bitpiece) == Night) {
//					print1("found night");
//					//check if capture of same side
//					if(piece && (!(COLOR(piece->bitpiece) ^ COLOR(p->bitpiece)))) {
//						print1("You cant capture your own piece");
//						i++;
//						continue;
//					}
//					print1("king can be capture");
//					return 1;
//				}
//				print1("king cant be capture");
//			}
//		}
//		i++;
//	}

	return 0;
}
int ischeckmate(chess_t *chess) {
	piece_t *piece;
	board_t board = chess->board;
	move_t move = chess->move;
	if(chess->player == WHITE) {
		print1("checking black king for checkmate");
		piece = chess->bking;
	}
	else {
		print1("checking white king for checkmate");
		piece = chess->wking;
	}
	if(!isempty(&piece->attack_by)) {
		print1("king under check");
		if(GetVPveField(piece->bitpiece)) {
			chess->move.x1 = piece->pos.x;
			chess->move.y1 = piece->pos.y;
			chess->move.x2 = piece->pos.x;
			chess->move.y2 = piece->pos.y + 1;
			if(!islegal(chess, 0)) {
				update_chess(chess);
				chess->move.x2 = chess->move.x1;
				chess->move.y2 = chess->move.y1;
				chess->move.x1 = chess->move.x1;
				chess->move.y1 = chess->move.y1 + 1;
				if(isempty(&piece->attack_by)) {
					print1("vertical pve move possible");
					update_chess(chess);
					return 0;
				}
				update_chess(chess);
			}
			else {
				chess->move.x2 = chess->move.x1;
				chess->move.y2 = chess->move.y1;
				chess->move.x1 = chess->move.x1;
				chess->move.y1 = chess->move.y1 + 1;
			}
		}
		if(GetVNveField(piece->bitpiece)) {
			chess->move.x1 = piece->pos.x;
			chess->move.y1 = piece->pos.y;
			chess->move.x2 = piece->pos.x;
			chess->move.y2 = piece->pos.y - 1;
			if(!islegal(chess, 0)) {
				update_chess(chess);
				chess->move.x2 = chess->move.x1;
				chess->move.y2 = chess->move.y1;
				chess->move.x1 = chess->move.x1;
				chess->move.y1 = chess->move.y1 - 1;
				if(isempty(&piece->attack_by)) {
					print1("vertical nve move possible");
					update_chess(chess);
					return 0;
				}
				update_chess(chess);
			}
			else {
				chess->move.x2 = chess->move.x1;
				chess->move.y2 = chess->move.y1;
				chess->move.x1 = chess->move.x1;
				chess->move.y1 = chess->move.y1 - 1;
			}
		}
		if(GetHPveField(piece->bitpiece)) {
			chess->move.x1 = piece->pos.x;
			chess->move.y1 = piece->pos.y;
			chess->move.x2 = piece->pos.x + 1;
			chess->move.y2 = piece->pos.y;
			if(!islegal(chess, 0)) {
				update_chess(chess);
				chess->move.x2 = chess->move.x1;
				chess->move.y2 = chess->move.y1;
				chess->move.x1 = chess->move.x1 + 1;
				chess->move.y1 = chess->move.y1;
				if(isempty(&piece->attack_by)) {
					print1("horizontal pve move possible");
					update_chess(chess);
					return 0;
				}
				update_chess(chess);
			}
			else {
				chess->move.x2 = chess->move.x1;
				chess->move.y2 = chess->move.y1;
				chess->move.x1 = chess->move.x1 + 1;
				chess->move.y1 = chess->move.y1;
			}
		}
		if(GetHNveField(piece->bitpiece)) {
			chess->move.x1 = piece->pos.x;
			chess->move.y1 = piece->pos.y;
			chess->move.x2 = piece->pos.x - 1;
			chess->move.y2 = piece->pos.y;
			if(!islegal(chess, 0)) {
				update_chess(chess);
				chess->move.x2 = chess->move.x1;
				chess->move.y2 = chess->move.y1;
				chess->move.x1 = chess->move.x1 - 1;
				chess->move.y1 = chess->move.y1;
				if(isempty(&piece->attack_by)) {
					print1("horizontal nve move possible");
					update_chess(chess);
					return 0;
				}
				update_chess(chess);
			}
			else {
				chess->move.x2 = chess->move.x1;
				chess->move.y2 = chess->move.y1;
				chess->move.x1 = chess->move.x1 - 1;
				chess->move.y1 = chess->move.y1;
			}
		}
		if(GetDNWField(piece->bitpiece)) {
			chess->move.x1 = piece->pos.x;
			chess->move.y1 = piece->pos.y;
			chess->move.x2 = piece->pos.x + 1;
			chess->move.y2 = piece->pos.y + 1;
			if(!islegal(chess, 0)) {
				update_chess(chess);
				chess->move.x2 = chess->move.x1;
				chess->move.y2 = chess->move.y1;
				chess->move.x1 = chess->move.x1 + 1;
				chess->move.y1 = chess->move.y1 + 1;
				if(isempty(&piece->attack_by)) {
					print1("diag nw move possible");
					update_chess(chess);
					return 0;
				}
				update_chess(chess);
			}
			else {
				chess->move.x2 = chess->move.x1;
				chess->move.y2 = chess->move.y1;
				chess->move.x1 = chess->move.x1 + 1;
				chess->move.y1 = chess->move.y1 + 1;
			}
		}
		if(GetDNEField(piece->bitpiece)) {
			chess->move.x1 = piece->pos.x;
			chess->move.y1 = piece->pos.y;
			chess->move.x2 = piece->pos.x - 1;
			chess->move.y2 = piece->pos.y + 1;
			if(!islegal(chess, 0)) {
				update_chess(chess);
				chess->move.x2 = chess->move.x1;
				chess->move.y2 = chess->move.y1;
				chess->move.x1 = chess->move.x1 - 1;
				chess->move.y1 = chess->move.y1 + 1;
				if(isempty(&piece->attack_by)) {
					print1("diag ne move possible");
					update_chess(chess);
					return 0;
				}
				update_chess(chess);
			}
			else {
				chess->move.x2 = chess->move.x1;
				chess->move.y2 = chess->move.y1;
				chess->move.x1 = chess->move.x1 - 1;
				chess->move.y1 = chess->move.y1 + 1;
			}
		}
		if(GetDSWField(piece->bitpiece)) {
			chess->move.x1 = piece->pos.x;
			chess->move.y1 = piece->pos.y;
			chess->move.x2 = piece->pos.x + 1;
			chess->move.y2 = piece->pos.y - 1;
			if(!islegal(chess, 0)) {
				update_chess(chess);
				chess->move.x2 = chess->move.x1;
				chess->move.y2 = chess->move.y1;
				chess->move.x1 = chess->move.x1 + 1;
				chess->move.y1 = chess->move.y1 - 1;
				if(isempty(&piece->attack_by)) {
					print1("diag sw move possible");
					update_chess(chess);
					return 0;
				}
				update_chess(chess);
			}
			else {
				chess->move.x2 = chess->move.x1;
				chess->move.y2 = chess->move.y1;
				chess->move.x1 = chess->move.x1 + 1;
				chess->move.y1 = chess->move.y1 - 1;
			}
		}
		if(GetDSEField(piece->bitpiece)) {
			chess->move.x1 = piece->pos.x;
			chess->move.y1 = piece->pos.y;
			chess->move.x2 = piece->pos.x - 1;
			chess->move.y2 = piece->pos.y - 1;
			if(!islegal(chess, 0)) {
				update_chess(chess);
				chess->move.x2 = chess->move.x1;
				chess->move.y2 = chess->move.y1;
				chess->move.x1 = chess->move.x1 - 1;
				chess->move.y1 = chess->move.y1 - 1;
				if(isempty(&piece->attack_by)) {
					print1("diag se move possible");
					update_chess(chess);
					return 0;
				}
				update_chess(chess);
			}
			else {
				chess->move.x2 = chess->move.x1;
				chess->move.y2 = chess->move.y1;
				chess->move.x1 = chess->move.x1 - 1;
				chess->move.y1 = chess->move.y1 - 1;
			}
		}
		if(piece == chess->bking) {
			print1("black king cant move");
			return WWIN;
		}
		else {
			print1("white king cant move");
			return BWIN;
		}
	}
	return 0;
}
int castlingpossible(chess_t *chess) {
	move_t move = chess->move;
	piece_t *piece;
	if(chess->player == WHITE) {
		piece = chess->wking;
	}
	else {
		piece = chess->bking;
	}
	if((move.x2 - move.x1) == 2) {
		chess->move.x2 = chess->move.x1 + 1;
		update_chess(chess);
		if(!isempty(&piece->attack_by)) {
			return ECAST;
		}
		chess->move.x1 = chess->move.x2;
		chess->move.x2 = chess->move.x1 + 1;
		update_chess(chess);
		if(!isempty(&piece->attack_by)) {
			return ECAST;
		}
	}
	if((move.x2 - move.x1) == -2) {
		chess->move.x2 = chess->move.x1 - 1;
		update_chess(chess);
		if(!isempty(&piece->attack_by)) {
			return ECAST;
		}
		chess->move.x1 = chess->move.x2;
		chess->move.x2 = chess->move.x1 - 1;
		update_chess(chess);
		if(!isempty(&piece->attack_by)) {
			return ECAST;
		}
	}
	return 0;
}

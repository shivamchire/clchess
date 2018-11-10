#include "chess.h"
#include "../board/board.h"
#include "../piece/piece.h"

void init_chess(chess_t *chess) {
	int i, j;
	chess->player = WHITE;
	chess->board = (piece_t ***)malloc(sizeof(piece_t **) * 8);
	for(i = 0; i < 8; i++) {
		chess->board[i] = (piece_t **)malloc(sizeof(piece_t *) * 8);
	}
	board_t board = chess->board;
	chess->move.x1 = 0;
	chess->move.x2 = 0;
	chess->move.y1 = 0;
	chess->move.y2 = 0;
	init_board(chess->board);
	for(i = 0; i < 8; i++) {
		for(j = 0; j < 8; j++) {
			if(board[i][j]) {
				gen_list(board, board[i][j]);
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
/*
 * update chess according to move
 */
void update_chess(chess_t *chess) {
	print2("Updating chess");
	board_t board = chess->board;
	move_t move = chess->move;

	piece_t *src_piece = board[move.y1][move.x1];
	//TODO destroy dest_piece
	board[move.y2][move.x2] = board[move.y1][move.x1];
	board[move.y1][move.x1] = NULL;
	degen_list(board, src_piece);
	pos_t pos;
	pos.x = move.x2;
	pos.y = move.y2;
	src_piece->pos = pos;
	gen_list(board, src_piece);
	print_all_list(src_piece);
}

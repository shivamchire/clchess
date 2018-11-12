#include "includes.h"
#include "board/board.h"
#include "ui/ui.h"
#include "chess/chess.h"
#include "piece/piece.h"
#define MOVE_LEN 8

char move[MOVE_LEN];
void twoplayer(void);
int main() {
	// TODO main menu
	twoplayer();
}
void twoplayer() {
	int win;
	print4("In twoplayer\n");
	chess_t chess;
	init_chess(&chess, char_board);
	print_board(chess.board);
	while(1) {
		// take next move
		if(chess.player == WHITE) {
			printf("%c->", 'w');
		}
		else {
			printf("%c->", 'b');
		}
		scanf("%s", move);

		//TODO add option of inputing move according to PGN
		// update board according to next move
		chess.move = conv_str_move(move);
		if(chess.move.x1 == -1) {
			print4();
			printf("Invalid move\n");
			continue;
		}
		if((win = islegal(&chess, 1))) {
			print4();
			if(win == WWIN) {
				printf("White win!\n");
				return;
			}
			else if(win == BWIN) {
				printf("Black win!\n");
				return;
			}
			printf("Invalid move\n");
			continue;
		}
		update_chess(&chess);
		print_board(chess.board);

		// change player
		chess.player ^= COLOR_Msk;
	}
}

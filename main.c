#include "includes.h"
#include "board_pieces.h"
#include "ui.h"
#define MOVE_LEN 8

char move[MOVE_LEN], player = 'w';
void twoplayer(void);
int main() {
	// TODO main menu
	twoplayer();
}
void twoplayer() {

	print4("In twoplayer\n");
	init_board();
	print_board();
	move_t str_move;
	while(1) {
		// take next move
		printf("%c->", player);
		if(scanf("%s", move) == -1) {
			printf("\n");
			break;
		}

		//TODO add option of inputing move according to PGN
		// update board according to next move
		str_move = conv_str_move(move);
		if(str_move.src == -1) {
			printf("Invalid move\n");
			continue;
		}
		if(inbtw(str_move)) {
			printf("Invalid move\n");
			continue;
		}
		update_board(str_move);
		print_board();

		// change player
		if(player == 'w') {
			player = 'b';
		}
		else {
			player = 'w';
		}
	}
}

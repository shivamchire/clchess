#include "includes.h"
#define MOVE_LEN 8

char move[MOVE_LEN], player = 'w';
void twoplayer(void);
int main() {
	print_board();
	// TODO main menu
	twoplayer();
}
void twoplayer() {

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
		if(str_move.src != -1) {
			update_board(str_move);
		}
		else {
			printf("Invalid move\n");
			continue;
		}
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

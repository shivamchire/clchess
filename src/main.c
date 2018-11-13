#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <errno.h>
#include "includes.h"
#include "board/board.h"
#include "ui/ui.h"
#include "chess/chess.h"
#include "piece/piece.h"
#define MOVE_LEN 128

char move[MOVE_LEN];
int main() {
	// TODO main menu
	chess_t chess;
	int mode, player, i, j, playermode, oneplayermode;
	while(1) {
		printf("1. To open save game\n");
		printf("2. To start a new two player game\n");
		printf("3. To start a new one player game\n");
		printf("4. Exit\n");
		scanf("%d", &mode);
		if(mode == 1) {
			printf("Enter file name\n");
			char load_file_name[128];
			char cha_board[8][8];
			scanf("%s", load_file_name);
			FILE *load_file = fopen(load_file_name, "r");
			if(!load_file) {
				perror("");
				return errno;
			}
			fscanf(load_file, "%d", &playermode);
			if(playermode == 1) {
				fscanf(load_file, "%d", &oneplayermode);
			}
			fscanf(load_file, "%d", &player);
			for(i = 0; i < 8; i++) {
				for(j = 0; j < 8; j++) {
					fscanf(load_file, "%c", &cha_board[i][j]);
				}
			}
			fclose(load_file);
			if(playermode == 2) {
				twoplayer(&chess, cha_board, player);
			}
			else if(playermode == 1) {
				oneplayer(&chess, cha_board, player, oneplayermode);
			}
		}
		else if(mode == 2) {
			twoplayer(&chess, char_board, WHITE);
			break;
		}
		else if(mode == 3) {
			//one player
			while(1) {
				printf("Mode:\n");
				printf("1. EASY\n");
				printf("2. HARD\n");
				printf("3. EXIT\n");
				scanf("%d", &mode);
				if(mode == 1) {
					oneplayermode = 1;
					break;
				}
				else if(mode == 2) {
					oneplayermode = 2;
					break;
				}
				else if(mode == 3) {
					return 0;
				}
				else {
					continue;
				}
			}
			oneplayer(&chess, char_board, WHITE, mode);
		}
		else if(mode == 4) {
			break;
		}
	}
}
void twoplayer(chess_t *chess, char c_board[][8], int player) {
	int win;
	print4("In twoplayer\n");
	init_chess(chess, c_board);
	chess->player = player;
	print_board(chess->board);
	while(1) {
		// take next move
		if(chess->player == WHITE) {
			printf("%c->", 'w');
		}
		else {
			printf("%c->", 'b');
		}
		scanf("%s", move);
		if(move[0] == 's') {
			int i, j;
			scanf("%s", &move[1]);
			printf("%s\n", &move[1]);
			FILE *save_file = fopen(&move[1], "w");
			char cha_board[8][8];
			fprintf(save_file, "%d", 2);
			fprintf(save_file, "%c", ' ');
			fprintf(save_file, "%d", chess->player);
			convertchesstochar(chess, cha_board);
			for(i = 0; i < 8; i++) {
				for(j = 0; j < 8; j++) {
					fprintf(save_file, "%c", cha_board[i][j]);
				}
			}
			destroy_chess(chess);
			fclose(save_file);
			return;
		}

		//TODO add option of inputing move according to PGN
		// update board according to next move
		chess->move = conv_str_move(move);
		if(chess->move.x1 == -1) {
			print4();
			printf("Invalid move\n");
			continue;
		}
		if((win = islegal(chess, 1))) {
			print4();
			if(win == WWIN) {
				printf("White win!\n");
				destroy_chess(chess);
				return;
			}
			else if(win == BWIN) {
				printf("Black win!\n");
				destroy_chess(chess);
				return;
			}
			printf("Invalid move\n");
			continue;
		}
		update_chess(chess);
		print_board(chess->board);

		// change player
		chess->player ^= COLOR_Msk;
	}
}
void oneplayer(chess_t *chess, char c_board[][8], int player, int mode) {

	int win;
	print4("In oneplayer\n");
	init_chess(chess, c_board);
	chess->player = player;
	print_board(chess->board);
	srand(time(NULL));
	if(mode == 1) {
		while(1) {
			// take next move
			if(chess->player == WHITE) {
				printf("%c->", 'w');
			}
			else {
				printf("%c->", 'b');
			}
			scanf("%s", move);
			if(move[0] == 's') {
				int i, j;
				scanf("%s", &move[1]);
				printf("%s\n", &move[1]);
				FILE *save_file = fopen(&move[1], "w");
				if(!save_file) {
					perror("");
					continue;
				}
				char cha_board[8][8];
				fprintf(save_file, "%d", 1);
				fprintf(save_file, "%c", ' ');
				fprintf(save_file, "%d", mode);
				fprintf(save_file, "%c", ' ');
				fprintf(save_file, "%d", chess->player);
				convertchesstochar(chess, cha_board);
				for(i = 0; i < 8; i++) {
					for(j = 0; j < 8; j++) {
						fprintf(save_file, "%c", cha_board[i][j]);
					}
				}
				destroy_chess(chess);
				fclose(save_file);
				return;
			}
			//TODO add option of inputing move according to PGN
			// update board according to next move
			chess->move = conv_str_move(move);
			if(chess->move.x1 == -1) {
				print4();
				printf("Invalid move\n");
				continue;
			}
			if((win = islegal(chess, 1))) {
				print4();
				if(win == WWIN) {
					printf("White win!\n");
					destroy_chess(chess);
					return;
				}
				else if(win == BWIN) {
					printf("Black win!\n");
					destroy_chess(chess);
					return;
				}
				printf("Invalid move\n");
				continue;
			}
			update_chess(chess);
			print_board(chess->board);

			generaterandommove(chess, chess->player ^ COLOR_Msk);
		}
	}
	else if(mode == 2) {
		printf("Hard mode not implemented\n");
	}
}

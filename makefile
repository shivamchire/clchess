main: ui.c board_pieces.c main.c
	gcc -DDEBUG=1 -std=c99 main.c ui.c pieces_list.c board_pieces.c list/g_slnl.c -o main

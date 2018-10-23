DEBUG_FLAG = 1
main: board_pieces.c main.c debug.h includes.h list/g_slnl.c pieces_list.c ui.c
	gcc -DDEBUG=$(DEBUG_FLAG) -std=c99 board_pieces.c list/g_slnl.c pieces_list.c ui.c main.c -o main

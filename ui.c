#include "ui.h"

void print_board() {

	int i = 0, j = 0, k = 0, l = 0, rank = 1;
	printf("     a   b   c   d   e   f   g   h\n");
	// since in each iteration we are going to print horizontal partioning
	// line (--- --- ---) and a box(made of 3 line) we will print 4 lines
	// for one box therefore 8*4 = 32
	while(i < 32) {
		j = 0;
		// to print 8 columns
		while(j < 8) {
			// depending on which line print
			switch(i % 4) {
				// horizontal partioning
				case 0:
					if(j == 0)
						printf("   ");
					printf(" ---");
					break;
				// vertical partioning and spaces
				case 1: case 3:
					if(j == 0)
						printf("   ");
					printf("|   ");
					break;
				// vertical partioning and pieces in that box
				case 2:
					if(j == 0) {
						printf(" %d ", rank);
						rank++;
					}
					printf("| %c ", board[l][k % 8]);
					k++;
					break;
			}
			j++;
		}
		// print ending vertical partioning
		// not to be printed at line where horizontal partion is printed
		switch(i % 4) {
			case 1: case 2: case 3:
				printf("|");
		}
		printf("\n");
		if(i % 4 == 2) {
			l++;
		}
		i++;
	}
	j = 0;
	printf("   ");
	while(j < 8) {
		printf(" ---");
		j++;
	}
	printf("\n");
	printf("     a   b   c   d   e   f   g   h\n");
}
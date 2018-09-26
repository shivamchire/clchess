#include "ui.h"

void print_board() {

	int i = 0, j = 0, k = 0, l = 0;
	while(i < 32) {
		j = 0;
		while(j < 8) {
			switch(i % 4) {
				case 0:
					printf(" ---");
					break;
				case 1: case 3:
					printf("|   ");
					break;
				case 2:
					printf("| %c ", board[l][k % 8]);
					k++;
					break;
			}
			j++;
		}
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
	while(j < 8) {
		printf(" ---");
		j++;
	}
	printf("\n");
}

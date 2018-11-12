#include "../includes.h"
#include "../move/move.h"

void init_chess(chess_t *chess, char chachessboard[][8]);
void update_chess(chess_t *chess);
void convertchesstocharr(chess_t *chess, char chesscopycha[][8]);
void creatchesscopy(chess_t *chesscopy, chess_t *chess);
int checkforcheck(chess_t *chess);
int ischeckmate(chess_t *chess);
int castlingpossible(chess_t *chess);

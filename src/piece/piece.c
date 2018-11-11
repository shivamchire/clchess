#include <stdint.h>
#include "piece.h"
#include "../board/board.h"


int NightBitsPos[][5] = {
	{ 0, NightSWPos, 0, NightSEPos, 0},
	{ NightWSPos, 0, 0, 0, NightESPos},
	{ 0, 0, 0, 0, 0 },
	{ NightWNPos, 0, 0, 0, NightENPos},
	{ 0, NightNWPos, 0, NightNEPos, 0}
};
/*
 * find piece starting from sx and sy in the direction of dirx and diry and return
 * address of piece found first in that direction OR NULL if no piece is found
 * in both the case saves position of piece or end of board in dx and dy
 */
piece_t *findpiece(board_t board, int sx, int sy, int dirx, int diry, int *dx, int *dy) {
	int i, j;
	piece_t *piece = NULL;
	*dx = -1;
	for(i = sx + dirx, j = sy + diry; i < 8 && j < 8 && i >= 0 && j >= 0; i += dirx, j += diry) {
		if(board[j][i]) {
			piece = board[j][i];
			*dx = i;
			*dy = j;
			break;
		}
	}
	if(*dx == -1) {
		*dx = i - dirx;
		*dy = j - diry;
	}
	return piece;
}
/*
 * set appropriate field of piece according to x or y
 * if movement of piece is possible in that direction
 * see which field to set by checking which of the one is zero
 * if y is zero
 * if x is zero
 * if both are equal
 * if both are zero ignore it
 * do checking for zero as this function is call when one piece want to move between
 * itself and an alias tile therefore x-1 and y-1 is passed
 * returns pos which have co-ordinates where piece can go but not legaly
 * ex: Night can go to the tile where its own color piece lies so pos will set to
 * this coordinates but flag for that direction wont be set as its not a legal move
 */
//TODO add castle move of king
pos_t setfield(board_t board, piece_t *piece, int x, int y) {
	int dirx;
	int diry;
	if(x)
		dirx = x / ABS(x);
	else
		dirx = 0;
	if(y)
		diry = y / ABS(y);
	else
		diry = 0;
	pos_t pos = { .x = 0, .y = 0 };
	int shift;
	if((PieceMsk & piece->bitpiece) == Night) {
		if((ABS(x) == 2 && ABS(y) == 1) ||	(ABS(x) == 1 && ABS(y) == 2)) {
			//set corresponding bit of night to 1 only when there is no piece there
			//or there is a piece which is of opposite color of that of night
			if(!board[piece->pos.y + y][piece->pos.x + x] ||
					(COLOR(piece->bitpiece) ^ COLOR(board[piece->pos.y + y][piece->pos.x + x]->bitpiece))) {
				shift = NightBitsPos[2 + y][2 + x];
				piece->bitpiece |= 1UL << shift;
			}
			//setting pos even if night cant legaly go to tile where same color piece
			//lies beacuse night can protect it and hence should be added to protect
			//list
			pos.x = x;
			pos.y = y;
		}
	}
	else if((ABS(x) == 2 && ABS(y) == 1) ||	(ABS(x) == 1 && ABS(y) == 2)) {
		return pos;
	}
	else if((PieceMsk & piece->bitpiece) == Pawn) {
		if(!(COLOR(piece->bitpiece) ^ WHITE)) {
			if(x == 0 && y > 0) {
				if(y == 1 || GetTwoMove(piece->bitpiece) == 0) {
					if(!board[piece->pos.y + 1][piece->pos.x]) {
						SetVPveField(piece, 1);
						pos.y = 1;
					}
				}
				else {
					if(!board[piece->pos.y + 1][piece->pos.x] && !board[piece->pos.y + 2][piece->pos.x]) {
						SetVPveField(piece, 2);
						pos.y = 2;
					}
					else if(!board[piece->pos.y + 1][piece->pos.x]) {
						SetVPveField(piece, 1);
						pos.y = 1;
					}
				}
			}
			else if(ABS(x) == ABS(y)) {
				if(x > 0 && y > 0 && board[piece->pos.y + 1][piece->pos.x + 1] &&
						(COLOR(board[piece->pos.y + 1][piece->pos.x + 1]->bitpiece) ^ WHITE)) {
					SetDNEField(piece, 1);
					pos.x = pos.y = 1;
				}
				else if(x > 0 && y > 0 && board[piece->pos.y + 1][piece->pos.x + 1] &&
						!(COLOR(board[piece->pos.y + 1][piece->pos.x + 1]->bitpiece) ^ WHITE)) {
					pos.x = pos.y = 1;
				}
				else if(x < 0 && y > 0 && board[piece->pos.y + 1][piece->pos.x - 1] &&
						(COLOR(board[piece->pos.y + 1][piece->pos.x - 1]->bitpiece) ^ WHITE)) {
					SetDNWField(piece, 1);
					pos.x = -1;
					pos.y = 1;
				}
				else if(x < 0 && y > 0 && board[piece->pos.y + 1][piece->pos.x - 1] &&
						!(COLOR(board[piece->pos.y + 1][piece->pos.x - 1]->bitpiece) ^ WHITE)) {
					//TODO this is not working e2e4 e7e5 g1f3
					pos.x = -1;
					pos.y = 1;
				}
			}
		}
		else {
			if(x == 0 && y < 0) {
				if(y == -1 || GetTwoMove(piece->bitpiece) == 0) {
					if(!board[piece->pos.y - 1][piece->pos.x]) {
						SetVNveField(piece, 1);
						pos.y = -1;
					}
				}
				else {
					if(!board[piece->pos.y - 1][piece->pos.x] && !board[piece->pos.y - 2][piece->pos.x]) {
						SetVNveField(piece, 2);
						pos.y = -2;
					}
					else if(!board[piece->pos.y - 1][piece->pos.x]) {
						SetVNveField(piece, 1);
						pos.y = -1;
					}
				}
			}
			else if(ABS(x) == ABS(y)) {
				if(x < 0 && y < 0 && board[piece->pos.y - 1][piece->pos.x - 1] &&
						!(COLOR(board[piece->pos.y - 1][piece->pos.x - 1]->bitpiece) ^ WHITE)) {
					SetDSWField(piece, 1);
					pos.x = pos.y = -1;
				}
				else if(x < 0 && y < 0 && board[piece->pos.y - 1][piece->pos.x - 1] &&
						!(COLOR(board[piece->pos.y - 1][piece->pos.x - 1]->bitpiece) ^ BLACK)) {
					pos.x = pos.y = -1;
				}
				else if(x > 0 && y < 0 && board[piece->pos.y - 1][piece->pos.x + 1] &&
						!(COLOR(board[piece->pos.y - 1][piece->pos.x + 1]->bitpiece) ^ WHITE)) {
					SetDSEField(piece, 1);
					pos.x = 1;
					pos.y = -1;
				}
				else if(x > 0 && y < 0 && board[piece->pos.y - 1][piece->pos.x + 1] &&
						!(COLOR(board[piece->pos.y - 1][piece->pos.x + 1]->bitpiece) ^ BLACK)) {
					SetDSEField(piece, 1);
					pos.x = 1;
					pos.y = -1;
				}
			}
		}
	}
	//since castle depends upon a lot of external factor it will be handled in
	//islegal
	else if(GetPiece(piece->bitpiece) == King) {
		//x and y must not be 0 at the same time
		if(dirx != 0 || diry != 0) {
			//can attack different color when it is not protected by someone
			//but this protected thing change as game progress therefore in
			//islegal always do that move and see if king is under check as
			//we have to do this for discover check and other stuff
			//dont exist or of different color
			if(!board[piece->pos.y + diry][piece->pos.x + dirx] ||
			(COLOR(board[piece->pos.y + diry][piece->pos.x + dirx]->bitpiece) ^
			 COLOR(piece->bitpiece))) {
				if(dirx == 1 && diry == 0) {
					SetHPveField(piece, 1);
				}
				else if(dirx == 1 && diry == 1) {
					SetDNEField(piece, 1);
				}
				else if(dirx == 0 && diry == 1) {
					SetVPveField(piece, 1);
				}
				else if(dirx == -1 && diry == 1) {
					SetDNWField(piece, 1);
				}
				else if(dirx == -1 && diry == 0) {
					SetHNveField(piece, 1);
				}
				else if(dirx == -1 && diry == -1) {
					SetDSWField(piece, 1);
				}
				else if(dirx == 0 && diry == -1) {
					SetVNveField(piece, 1);
				}
				else if(dirx == 1 && diry == -1) {
					SetDSEField(piece, 1);
				}
				pos.x = dirx;
				pos.y = diry;
				return pos;
			}
			//same color
			else {
				pos.x = dirx;
				pos.y = diry;
				return pos;
			}
		}

	}
	//if second piece dont exist or it exist but are of different color
	else if(!board[piece->pos.y + y][piece->pos.x + x] ||
			(COLOR(board[piece->pos.y + y][piece->pos.x + x]->bitpiece) ^
			 COLOR(piece->bitpiece))){
		if(x == 0 && GetV(piece->bitpiece)) {
			if(y > 0) {
				SetVPveField(piece, y);
				pos.y = y;
			}
			else {
				SetVNveField(piece, -y);
				pos.y = y;
			}
		}
		else if(y == 0 && GetH(piece->bitpiece)) {
			if(x > 0) {
				SetHPveField(piece, x);
				pos.x = x;
			}
			else {
				SetHNveField(piece, -x);
				pos.x = x;
			}
		}
		else if(ABS(x) == ABS(y) && GetD(piece->bitpiece)) {
			if(dirx > 0 && diry > 0) {
				SetDNEField(piece, x);
				pos.x = pos.y = x;
			}
			else if(dirx > 0 && diry < 0) {
				SetDSEField(piece, x);
				pos.x = x;
				pos.y = y;
			}
			else if(dirx < 0 && diry > 0) {
				SetDNWField(piece, y);
				pos.x = x;
				pos.y = y;
			}
			else if(dirx < 0 && diry < 0) {
				SetDSWField(piece, -x);
				pos.x = x;
				pos.y = y;
			}
			else {
				eprint("ERROR");
			}
		}
	}
	else {
		if(x == 0 && GetV(piece->bitpiece)) {
			if(y > 0) {
				SetVPveField(piece, y - diry);
				pos.y = y;
			}
			else {
				SetVNveField(piece, -(y - diry));
				pos.y = y;
			}
		}
		else if(y == 0 && GetH(piece->bitpiece)) {
			if(x > 0) {
				SetHPveField(piece, x - dirx);
				pos.x = x;
			}
			else {
				SetHNveField(piece, -(x - dirx));
				pos.x = x;
			}
		}
		else if(ABS(x) == ABS(y) && GetD(piece->bitpiece)) {
			if(dirx > 0 && diry > 0) {
				SetDNEField(piece, x - dirx);
				pos.x = pos.y = x;
			}
			else if(dirx > 0 && diry < 0) {
				SetDSEField(piece, x - dirx);
				pos.x = x;
				pos.y = y;
			}
			else if(dirx < 0 && diry > 0) {
				SetDNWField(piece, y - diry);
				pos.x = x;
				pos.y = y;
			}
			else if(dirx < 0 && diry < 0) {
				SetDSWField(piece, -(x - dirx));
				pos.x = x;
				pos.y = y;
			}
			else {
				//eprint("ERROR");
			}
		}
	}
	return pos;
}
//---- for piece list ----
void init_piece_list(piece_list_t* l) {
	init(l);
}

void deletebypos(piece_list_t *l, int pos) {
	vprint1("deleting from %p", l);
	remov(l, pos);
}

void delete_piece(piece_list_t *l, piece_t *piece) {
	int num;
	if((num = search(l, piece))) {
		vprint1("Deleting %c at (%c, %d) from %p", piece->piece, piece->pos.x + 'a', piece->pos.y, l);
		remov(l, num);
	}
}
/*
 * dont use this since it dont consider case of inbtw delete and insert
 * TODO remove this
 */
/*
piece_t *get_next(piece_list_t *l) {
	static piece_list_t *prev_list = NULL;
	static size_t pos = 1;
	if(l) {
		prev_list = l;
		pos = 1;
	}
	piece_t *piece = (piece_t *)see(l, pos);
	pos++;
	return piece;
}
*/
/*
int search(piece_list_t *l, piece_t *p) {
	int i = 1;
	piece_t *piece = get_next(l);
	while(piece) {
		if(piece == p) {
			return i;
		}
		piece = get_next(NULL);
		i++;
	}
	return -1;
}
*/
void destroy_piece_list(piece_list_t *l) {
	destroy(l);
}
int search_piece(piece_list_t *l, piece_t *p) {
	return search(l, p);
}
void insert_piece(piece_list_t *l, piece_t *p) {
	if(!search_piece(l, p)) {
		vprint1("Inserting %c in list %p", p->piece, (void *)l);
		insert(l, p, 1);
	}
}
int getnumofelem(piece_list_t *l) {
	return getnum(l);
}



//this fuction assumes that piece has moved on board but its pos struct have its
//previous position
//WARNING dont pass piece to setfield since setfield use piece->pos to calculate
//move and since pos has its previous position it will calculate it wrong
void degen_list(chess_t *chess, board_t board, piece_t *piece) {
	//direction along line joining piece in the list and the piece to whom list
	//belong too
	int dirx, diry,
	//to find out position of bit to bit modified in case of Night
		shift;
	//use to traverse list
	piece_t *p,
	//use to store a third piece
			*anotherpiece;
	//to store position of new pieces
	pos_t pos,
		  init_pos = { .x = chess->move.x1, .y = chess->move.y1};
	//empty protecting list also delete pieces in protected_by list of pieces
	//in protecting list
	while(!isempty(&piece->protecting)) {
		p = (piece_t *)see(&piece->protecting, 1);
		vprint1("deleting %c at (%c, %d) from protecting list of %c at (%c, %d)", p->piece, Coordinate(p), piece->piece, Coordinate(piece));
		deletebypos(&piece->protecting, 1);
		delete_piece(&p->protected_by, piece);
	}
	//emptying attacking list
	while(!isempty(&piece->attacking)) {
		p = (piece_t *)see(&piece->attacking, 1);
		vprint1("deleting %c at (%c, %d) from attacking list of %c at (%c, %d)", p->piece, Coordinate(p), piece->piece, Coordinate(piece));
		deletebypos(&piece->attacking, 1);
		delete_piece(&p->attack_by, piece);
	}
	while(!isempty(&piece->protected_by)) {
		p = (piece_t *)see(&piece->protected_by, 1);
		vprint1("deleting %c at (%c, %d) from protected_by list of %c at (%c, %d)", p->piece, Coordinate(p), piece->piece, Coordinate(piece));
		deletebypos(&piece->protected_by, 1);
		delete_piece(&p->protecting, piece);
		if((PieceMsk & p->bitpiece) == Pawn) {
			print1("pawn case");
		}
		else if((PieceMsk & p->bitpiece) == Night) {
			print1("night case");
			shift = NightBitsPos[2 + (init_pos.y - p->pos.y)][2 + (init_pos.x - p->pos.x)];
			p->bitpiece |= 1UL << shift;
		}
		else {
			print1("others case");
			dirx = init_pos.x - p->pos.x;
			diry = init_pos.y - p->pos.y;
			if(dirx)
				dirx = dirx / ABS(dirx);
			if(diry)
				diry = diry / ABS(diry);
			anotherpiece = findpiece(board, p->pos.x, p->pos.y, dirx, diry, &(pos.x), &(pos.y));
			if(anotherpiece != piece) {
				//if anotherpiece dont exist just update the appropriate field
				if(!anotherpiece) {
					print1("anotherpiece not found");
					setfield(board, p, pos.x - p->pos.x, pos.y - p->pos.y);
				}
				//else
				else {
					print1("anotherpiece found");
					//if both the pieces are of different color add anotherpiece
					//to attacking list of p and add p to attack_by list of anotherpiece
					//and set appropriate field of p to x or y
					if(COLOR(anotherpiece->bitpiece) ^ COLOR(p->bitpiece)) {
						pos = setfield(board, p, anotherpiece->pos.x - p->pos.x, anotherpiece->pos.y - p->pos.y);
						if((pos.x != 0 || pos.y != 0) && board[p->pos.y + pos.y][p->pos.x + pos.x]) {
							vprint1("%c can attack %c at (%c, %d)", p->piece, anotherpiece->piece, Coordinate(anotherpiece));
							insert_piece(&p->attacking, anotherpiece);
							insert_piece(&anotherpiece->attack_by, p);
						}
					}
					//else if of same color add anotherpiece in protecting list of
					//p and add p in protected_by list of anotherpiece
					//and set appropriate field of p to x-1 or y-1
					else {
					//	if(anotherpiece->pos.x - p->pos.x == 0 && anotherpiece->pos.y - p->pos.y == 0) {
					//		x = 0;
					//		y = 0;
					//	}
					//	else if(anotherpiece->pos.y - p->pos.y == 0) {
					//		y = 0;
					//		x = (anotherpiece->pos.x - p->pos.x) - 1;
					//	}
					//	else if(anotherpiece->pos.x - p->pos.x == 0) {
					//		x = 0;
					//		y = (anotherpiece->pos.y - p->pos.y) - 1;
					//	}
					//	else {
					//		x = (anotherpiece->pos.x - p->pos.x) - 1;
					//		y = (anotherpiece->pos.y - p->pos.y) - 1;
					//	}

						pos = setfield(board, p, anotherpiece->pos.x - p->pos.x, anotherpiece->pos.y - p->pos.y);
						if((pos.x != 0 || pos.y != 0) && board[p->pos.y + pos.y][p->pos.x + pos.x]) {
							vprint1("%c can protect %c at (%c, %d)", p->piece, anotherpiece->piece, Coordinate(anotherpiece));
							insert_piece(&p->protecting, anotherpiece);
							insert_piece(&anotherpiece->protected_by, p);
						}
					}
				}
			}
		}
	}
	//attack_by list
	while(!isempty(&piece->attack_by)) {
		print1("in attack_by list of degen_list");
		p = (piece_t *)see(&piece->attack_by, 1);
		vprint1("deleting %c at (%c, %d) from attack_by list of %c", p->piece, Coordinate(p), piece->piece);
		deletebypos(&piece->attack_by, 1);
		delete_piece(&p->attacking, piece);
		if(!(p == chess->captured_piece)) {
			if((PieceMsk & p->bitpiece) == Pawn) {
				print1("in pawn case");
				dirx = init_pos.x - p->pos.x;
				if(dirx)
					dirx = dirx / ABS(dirx);
				diry = init_pos.y - p->pos.y;
				if(diry)
					diry = diry / ABS(diry);
				if(dirx > 0 && diry > 0) {
					SetDNEField(p, 0);
				}
				else if(dirx > 0 && diry < 0) {
					SetDSEField(p, 0);
				}
				else if(dirx < 0 && diry > 0) {
					SetDNWField(p, 0);
				}
				else if(dirx < 0 && diry < 0) {
					SetDSWField(p, 0);
				}
				else {
					eprint("ERROR");
				}
			}
			else if((PieceMsk & p->bitpiece) == Night) {
			}
			else if(GetPiece(p->bitpiece) == King) {
			}
			else {
				print1("in other piece case");
				dirx = init_pos.x - p->pos.x;
				diry = init_pos.y - p->pos.y;
				vprint1("in dir (%d, %d)", dirx, diry);
				if(dirx)
					dirx = dirx / ABS(dirx);
				if(diry)
					diry = diry / ABS(diry);
				anotherpiece = findpiece(board, p->pos.x, p->pos.y, dirx, diry, &(pos.x), &(pos.y));
				//if anotherpiece dont exist just update the appropriate field
				if(!anotherpiece) {
					print1("anotherpiece not found");
					setfield(board, p, pos.x - p->pos.x, pos.y - p->pos.y);
				}
				//else
				else {
					print1("anotherpiece found");
					//if both the pieces are of different color add anotherpiece
					//to attacking list of p and add p to attack_by list of anotherpiece
					//and set appropriate field of p to x or y
					if(COLOR(anotherpiece->bitpiece) ^ COLOR(p->bitpiece)) {
						pos = setfield(board, p, anotherpiece->pos.x - p->pos.x, anotherpiece->pos.y - p->pos.y);
						if((pos.x != 0 || pos.y != 0) && board[p->pos.y + pos.y][p->pos.x + pos.x]) {
							vprint1("%c can attack %c at (%c, %d)", p->piece, anotherpiece->piece, Coordinate(anotherpiece));
							insert_piece(&p->attacking, anotherpiece);
							insert_piece(&anotherpiece->attack_by, p);
						}
					}
					//else if of same color add anotherpiece in protecting list of
					//p and add p in protected_by list of anotherpiece
					//and set appropriate field of p to x-1 or y-1
					else {
						pos = setfield(board, p, (anotherpiece->pos.x - p->pos.x) - 1, (anotherpiece->pos.y - p->pos.y) - 1);
						if((pos.x != 0 || pos.y != 0) && board[p->pos.y + pos.y][p->pos.x + pos.x]) {
							vprint1("%c can protect %c at (%c , %d)", p->piece, anotherpiece->piece, Coordinate(anotherpiece));
							insert_piece(&p->protecting, anotherpiece);
							insert_piece(&anotherpiece->protected_by, p);
						}
					}
				}
			}
		}
	}
	if((init_pos.y - 1) >= 0 && board[init_pos.y - 1][init_pos.x] &&
			GetPiece(board[init_pos.y - 1][init_pos.x]->bitpiece) == WPawn) {
		SetVPveField(board[init_pos.y - 1][init_pos.x], 1);
	}
	if(init_pos.y + 1 < 8 && board[init_pos.y + 1][init_pos.x] &&
			GetPiece(board[init_pos.y + 1][init_pos.x]->bitpiece) == BPawn) {
		SetVNveField(board[init_pos.y + 1][init_pos.x], 1);
	}
}

const short MoveAlongX[] = { 1, 1, 0, -1, -1, -1, 0, 1 };
const short MoveAlongY[] = { 0, 1, 1, 1, 0, -1, -1, -1 };
const short NightMoveAlongX[] = { 1, 2, 2, 1, -1, -2, -2, -1};
const short NightMoveAlongY[] = { 2, 1, -1, -2, -2, -1, 1, 2};

//const short bit_shiftpos[] = { HoriFieldPvePos, DiagNEPos, VertFieldPvePos, DiagNWPos,
//			HoriFieldNvePos, DiagSWPos, VertFieldNvePos, DiagSEPos };
//const unsigned long long field_msk[] = { HoriPveMsk, DiagNEMsk, VertPveMsk, DiagNWMsk,
//			HoriNveMsk, DiagSWMsk, VertNveMsk, DiagSEMsk };
//matrix to give Pos of bits in bitpiece from movement
//this fuction assumes that piece has moved on board and its pos struct have its
//current position
void gen_list(chess_t *chess, board_t board, piece_t *piece) {
	vprint1("chess -> %p, board -> %p, piece -> %p %c at (%c, %d)", chess, board, piece, piece->piece, Coordinate(piece));
//TODO write pawn case
	//to see in all 8 direction
	int i = 0,
	//stores change in x and y to go in that direction
		dirx, diry,
	//co-ordintes of end tile
		ex, ey,
		exofanotherpiece, eyofanotherpiece,
	//to store position of piece_t in list_t
		num;
	//p denotes piece in direction of dirx and diry
	//anotherpiece is piece in the direction of opposite to dirx and diry when
	//piece was not inbetween
	piece_t *p, *anotherpiece,
			*captured_piece;
	pos_t pos;
	//if there is a captured element then delete this element from the list of all
	//other piecelist which have it and insert that all other element into opposite
	//list of piece
	if(chess->captured_piece) {
		//TODO when any piece is protecting someone it do not have fields set to
		//go to that tile so either set them when inserting pieces in protecting
		//list but as we check own capture first move will be still invalid
		//or set field in this snipet
		//loss of first method if we move the protected piece then
		//as pawn cant move diagonaly - can be handled at line 392
		//others can move but as they are sliding its fields is going to change
		captured_piece = chess->captured_piece;
		while(!isempty(&captured_piece->protecting)) {
			print1("Inside protecting while loop of captured_piece case of gen_list");
			p = (piece_t *)see(&captured_piece->protecting, 1);
			delete_piece(&captured_piece->protecting, p);
			delete_piece(&p->protected_by, captured_piece);
		}
		while(!isempty(&captured_piece->attacking)) {
			print1("Inside attacking while loop of captured_piece case of gen_list");
			p = (piece_t *)see(&captured_piece->attacking, 1);
			delete_piece(&captured_piece->attacking, p);
			delete_piece(&p->attack_by, captured_piece);
		}
		while(!isempty(&captured_piece->protected_by)) {
			print1("Inside protected_by while loop of captured_piece case of gen_list");
			p = (piece_t *)see(&captured_piece->protected_by, 1);
			delete_piece(&captured_piece->protected_by, p);
			delete_piece(&p->protecting, captured_piece);
			insert_piece(&piece->attack_by, p);
			insert_piece(&p->attacking, piece);
		}
		while(!isempty(&captured_piece->attack_by)) {
			print1("Inside attack_by while loop of captured_piece case of gen_list");
			p = (piece_t *)see(&captured_piece->attack_by, 1);
			delete_piece(&captured_piece->attack_by, p);
			delete_piece(&p->attacking, captured_piece);
			insert_piece(&piece->protected_by, p);
			insert_piece(&p->protecting, piece);
		}
	}
	if(GetPiece(piece->bitpiece) == Night) {
		print1("Inside piece is Night case of gen_list");
		while(i < 8) {
			if(piece->pos.y + NightMoveAlongY[i] < 8 && piece->pos.x + NightMoveAlongX[i] < 8 &&
				piece->pos.y + NightMoveAlongY[i] >= 0 && piece->pos.x + NightMoveAlongX[i] >= 0) {
				p = board[piece->pos.y + NightMoveAlongY[i]][piece->pos.x+NightMoveAlongX[i]];
				pos = setfield(board, piece, NightMoveAlongX[i], NightMoveAlongY[i]);
				if(p) {
					//different color
					if(COLOR(piece->bitpiece) ^ COLOR(p->bitpiece)) {
						vprint1("Inside different color case (%c, %d)", piece->pos.x+NightMoveAlongX[i] + 'a', piece->pos.y + NightMoveAlongY[i]);
						insert_piece(&piece->attacking, p);
						insert_piece(&p->attack_by, piece);
					}
					//same color
					else {
						vprint1("Inside same color case (%c, %d)", piece->pos.x+NightMoveAlongX[i] + 'a', piece->pos.y + NightMoveAlongY[i]);
						insert_piece(&piece->protecting, p);
						insert_piece(&p->protected_by, piece);
					}
				}
			}
			i++;
		}
	}
	i = 0;
	while(i < 8) {
		print1("inside others is night case of gen_list");
		if(piece->pos.y + NightMoveAlongY[i] < 8 && piece->pos.x + NightMoveAlongX[i] < 8 &&
			piece->pos.y + NightMoveAlongY[i] >= 0 && piece->pos.x + NightMoveAlongX[i] >= 0) {
			p = board[piece->pos.y + NightMoveAlongY[i]][piece->pos.x+NightMoveAlongX[i]];
			if(p) {
				if(GetPiece(p->bitpiece) == Night) {
					pos = setfield(board, p, -NightMoveAlongX[i], -NightMoveAlongY[i]);
					//different color
					if(COLOR(piece->bitpiece) ^ COLOR(p->bitpiece)) {
						insert_piece(&p->attacking, piece);
						insert_piece(&piece->attack_by, p);
					}
					//same color
					else {
						insert_piece(&p->protecting, piece);
						insert_piece(&piece->protected_by, p);
					}
				}
			}
		}
		i++;
	}
	i = 0;
	while(i < 8) {
		print1("inside other piece case of gen_list");
		dirx = MoveAlongX[i];
		diry = MoveAlongY[i];
		vprint1("along dir (%d, %d)", dirx, diry);
		p = findpiece(board, piece->pos.x, piece->pos.y, dirx, diry, &ex, &ey);
		if(!p) {
			print1("no piece found");
			setfield(board, piece, ex - piece->pos.x, ey - piece->pos.y);
		}
		else {
			vprint1("%c at (%c, %d) found", p->piece, p->pos.x + 'a', p->pos.y);
			anotherpiece = findpiece(board, piece->pos.x, piece->pos.y, -dirx,
									-diry, &exofanotherpiece, &eyofanotherpiece);
			//if anotherpiece exist
			if(anotherpiece) {
				vprint1("anotherpiece %c at (%c, %d) found", anotherpiece->piece, anotherpiece->pos.x + 'a', anotherpiece->pos.y);
				//if p and anotherpiece are of different color
				if(COLOR(p->bitpiece) ^ COLOR(anotherpiece->bitpiece)) {
					if((num = search_piece(&p->attacking, anotherpiece)))
						deletebypos(&p->attacking, num);
					if((num = search_piece(&p->attack_by, anotherpiece)))
						deletebypos(&p->attack_by, num);
					if((num = search_piece(&anotherpiece->attacking, p)))
						deletebypos(&anotherpiece->attacking, num);
					if((num = search_piece(&anotherpiece->attack_by, p)))
						deletebypos(&anotherpiece->attack_by, num);
				}
				//if p and anotherpiece are of same color
				else {
					if((num = search_piece(&p->protecting, anotherpiece)))
						deletebypos(&p->protecting, num);
					if((num = search_piece(&p->protected_by, anotherpiece)))
						deletebypos(&p->protected_by, num);
					if((num = search_piece(&anotherpiece->protecting, p)))
						deletebypos(&anotherpiece->protecting, num);
					if((num = search_piece(&anotherpiece->protected_by, p)))
						deletebypos(&anotherpiece->protected_by, num);
				}
			}
			//p and piece are of different color
			if(COLOR(piece->bitpiece) ^ COLOR(p->bitpiece)) {
				//if piece can attack p
				pos = setfield(board, piece, ex - piece->pos.x, ey - piece->pos.y);
				if((pos.x != 0 || pos.y != 0) && board[piece->pos.y + pos.y][piece->pos.x + pos.x] && !search_piece(&piece->attacking, p)) {
					vprint1("%c can attack %c", piece->piece, p->piece);
					insert_piece(&piece->attacking, p);
					insert_piece(&p->attack_by, piece);
				}
				//if p can attack piece
				pos = setfield(board, p, piece->pos.x - ex, piece->pos.y - ey);
				if((pos.x != 0 || pos.y != 0) && board[p->pos.y + pos.y][p->pos.x + pos.x] && !search_piece(&p->attacking, piece)) {
					vprint1("%c can attack %c", p->piece, piece->piece);
					insert_piece(&p->attacking, piece);
					insert_piece(&piece->attack_by, p);
				}
			}
			//same color
			else {
				//if piece can protect p
				pos = setfield(board, piece, ex - piece->pos.x, ey - piece->pos.y);
				if((pos.x != 0 || pos.y != 0) && board[piece->pos.y + pos.y][piece->pos.x + pos.x] && !search_piece(&piece->protecting, p)) {
					vprint1("%c can protect %c", piece->piece, p->piece);
					insert_piece(&piece->protecting, p);
					insert_piece(&p->protected_by, piece);
				}
				//if p can protect piece
				pos = setfield(board, p, piece->pos.x - ex, piece->pos.y - ey);
				if((pos.x != 0 || pos.y != 0) && board[p->pos.y + pos.y][p->pos.x + pos.x] && !search_piece(&p->protecting, piece)) {
					vprint1("%c can protect %c", p->piece, piece->piece);
					insert_piece(&p->protecting, piece);
					insert_piece(&piece->protected_by, p);
				}
			}
		}
		i++;
	}
}
//---- for piece list ----

void print_all_list(piece_t *p) {
	piece_t *piece;
	int i = getnumofelem(&(p->protecting));
	print1("Member of protecting");
	while(i) {
		piece = (piece_t *)see(&(p->protecting), i);
		vprint1("%c", piece->piece);
		i--;
	}
	i = getnumofelem(&p->protected_by);
	print1("Member of protected_by");
	while(i) {
		piece = (piece_t *)see(&p->protected_by, i);
		vprint1("%c", piece->piece);
		i--;
	}
	i = getnumofelem(&p->attacking);
	print1("Member of attacking");
	while(i) {
		piece = (piece_t *)see(&p->attacking, i);
		vprint1("%c", piece->piece);
		i--;
	}
	i = getnumofelem(&p->attack_by);
	print1("Member of attack_by");
	while(i) {
		piece = (piece_t *)see(&p->attack_by, i);
		vprint1("%c", piece->piece);
		i--;
	}
}
void printpieceinfo(piece_t *piece) {
	vprint2("piece -> %c", piece->piece);
	vprint2("color -> %lx", COLOR(piece->bitpiece));
	vprint2("Vert -> %lx, Pve -> %lx, Nve -> %lx", GetV(piece->bitpiece),
												GetVPveField(piece->bitpiece),
												GetVNveField(piece->bitpiece));
	vprint2("Hori -> %lx, Pve -> %lx, Nve -> %lx", GetH(piece->bitpiece),
												GetHPveField(piece->bitpiece),
												GetHNveField(piece->bitpiece));
	vprint2("Diagonal -> %lx, NW -> %lx, NE -> %lx, SW -> %lx, SE -> %lx",
												GetD(piece->bitpiece),
												GetDNWField(piece->bitpiece),
												GetDNEField(piece->bitpiece),
												GetDSWField(piece->bitpiece),
												GetDSEField(piece->bitpiece));
	vprint2("TwoMoves : NW -> %lx, NE -> %lx, SW -> %lx, SE -> %lx, WN-> %lx, WS -> %lx, EN -> %lx, ES -> %lx",
												GetNightNW(piece->bitpiece),
												GetNightNE(piece->bitpiece),
												GetNightSW(piece->bitpiece),
												GetNightSE(piece->bitpiece),
												GetNightWN(piece->bitpiece),
												GetNightWS(piece->bitpiece),
												GetNightEN(piece->bitpiece),
												GetNightES(piece->bitpiece));
}
void init_piece(piece_t *piece, char p, pos_t pos) {
	switch(p) {
		case 'P':
			piece->bitpiece = WPawn;
			SetVPveField(piece, 2);
			SetTwoMove(piece, 1);
			break;
		case 'p':
			piece->bitpiece = BPawn;
			SetVNveField(piece, 2);
			SetTwoMove(piece, 1);
			break;
		case 'R':
			piece->bitpiece = WRook;
			break;
		case 'r':
			piece->bitpiece = BRook;
			break;
		case 'N':
			piece->bitpiece = WNight;
			SetNightNE(piece, 1);
			SetNightNW(piece, 1);
			break;
		case 'n':
			piece->bitpiece = BNight;
			SetNightSE(piece, 1);
			SetNightSW(piece, 1);
			break;
		case 'B':
			piece->bitpiece = WBishop;
			break;
		case 'b':
			piece->bitpiece = BBishop;
			break;
		case 'Q':
			piece->bitpiece = WQueen;
			break;
		case 'q':
			piece->bitpiece = BQueen;
			break;
		case 'K':
			piece->bitpiece = WKing;
			break;
		case 'k':
			piece->bitpiece = BKing;
			break;
		default:
			vprint2("Invalid piece %c", p);
			break;
	}
	piece->piece = p;
	piece->pos = pos;
	vprint2("Initializing piecelist for %c at (%c, %d)", p, Coordinate(piece));
	init_piece_list(&(piece->protected_by));
	init_piece_list(&(piece->protecting));
	init_piece_list(&(piece->attack_by));
	init_piece_list(&(piece->attacking));
}

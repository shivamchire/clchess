#ifndef PIECES_H
#define PIECES_H


#include "../includes.h"
/*
 *                  -ve  +ve  -ve  +ve  SW   SE   NE   NW
 * E xLPC TTTT TTTT VVVV VVVV HHHH HHHH DDDD DDDD DDDD DDDD xxCK/Q VHDC
 */
#define WHITE (1)
#define BLACK (0)
#define COLOR_Msk (1)
#define COLOR(x) ((x) & COLOR_Msk)
/* Bit Position */
#define DiagPos (1)
#define HoriPos (2)
#define VertPos (3)
#define KQPos (4)
#define CastlingPos (5)
/* Bits */
#define VertBit (1 << VertPos)
#define HoriBit (1 << HoriPos)
#define DiagBit (1 << DiagPos)
#define KQBit (1 << KQPos)
#define CastlingBit (1 << CastlingPos)
/* Field Position */
#define DiagFieldPos (8 )
#define DiagNWPos (8)
#define DiagNEPos (12)
#define DiagSEPos (16)
#define DiagSWPos (20)
#define HoriFieldPos (24)
#define HoriFieldPvePos (24)
#define HoriFieldNvePos (28)
#define VertFieldPos (32)
#define VertFieldPvePos (32)
#define VertFieldNvePos (36)
#define NightFieldPos (40)
#define NightNEPos (40)
#define NightNWPos (41)
#define NightSEPos (42)
#define NightSWPos (43)
#define NightENPos (44)
#define NightESPos (45)
#define NightWNPos (46)
#define NightWSPos (47)
#define CheckPos (48)
#define PinPos (49)
#define LMSPos (50)
#define TwoMovePos (51)
#define EnPassantPos (52)
/*
 *                  -ve  +ve  -ve  +ve  SW   SE   NE   NW
 * E TLPC TTTT TTTT VVVV VVVV HHHH HHHH DDDD DDDD DDDD DDDD xxCK/Q VHDC
 */
/* Field Mask */
#define DiagMsk (0xffffUL << DiagFieldPos)
#define DiagNWMsk (0xfUL << DiagNWPos)
#define DiagNEMsk (0xfUL << DiagNEPos)
#define DiagSEMsk (0xfUL << DiagSEPos)
#define DiagSWMsk (0xfUL << DiagSWPos)
#define HoriMsk (0xffUL << HoriFieldPos)
#define HoriPveMsk (0xfUL << HoriFieldPvePos)
#define HoriNveMsk (0xfUL << HoriFieldNvePos)
#define VertMsk (0xffUL << VertFieldPos)
#define VertPveMsk (0xfUL << VertFieldPvePos)
#define VertNveMsk (0xfUL << VertFieldNvePos)
#define NightFieldMsk (0xffUL << NightFieldPos)
#define NightNEMsk (0x1UL << NightNEPos)
#define NightNWMsk (0x1UL << NightNWPos)
#define NightSEMsk (0x1UL << NightSEPos)
#define NightSWMsk (0x1UL << NightSWPos)
#define NightENMsk (0x1UL << NightENPos)
#define NightESMsk (0x1UL << NightESPos)
#define NightWNMsk (0x1UL << NightWNPos)
#define NightWSMsk (0x1UL << NightWSPos)
#define CheckMsk (1UL << CheckPos)
#define PinMsk (1UL << PinPos)
#define LMSMsk (1UL << LMSPos)
#define EnPassantMsk (1UL << EnPassantPos)
#define TwoMoveMsk (1UL << TwoMovePos)
/* Set Bits */
#define SetV(x) ((x) |= VertBit)
#define SetH(x) ((x) |= HoriBit)
#define SetD(x) ((x) |= DiagBit)
#define SetK(x) ((x) |= VertBit | HoriBit | DiagBit | KQBit)
/* Set Field */
#define SetCastling(x, y) ((x)->bitpiece |= CastlingBit, (x)->bitpiece &= (((uint64_t)(y) << CastlingPos) | ~CastlingBit))
#define SetVPveField(x, y) ((x)->bitpiece |= VertPveMsk, (x)->bitpiece &= (((uint64_t)(y) << VertFieldPvePos) | ~VertPveMsk))
#define SetVNveField(x, y) ((x)->bitpiece |= VertNveMsk, (x)->bitpiece &= (((uint64_t)(y) << VertFieldNvePos) | ~VertNveMsk))
#define SetHPveField(x, y) ((x)->bitpiece |= HoriPveMsk, (x)->bitpiece &= (((uint64_t)(y) << HoriFieldPvePos) | ~HoriPveMsk))
#define SetHNveField(x, y) ((x)->bitpiece |= HoriNveMsk, (x)->bitpiece &= (((uint64_t)(y) << HoriFieldNvePos) | ~HoriNveMsk))
#define SetDNWField(x, y) ((x)->bitpiece |= DiagNWMsk, (x)->bitpiece &= (((uint64_t)(y) << DiagNWPos) | ~DiagNWMsk))
#define SetDNEField(x, y) ((x)->bitpiece |= DiagNEMsk, (x)->bitpiece &= (((uint64_t)(y) << DiagNEPos) | ~DiagNEMsk))
#define SetDSWField(x, y) ((x)->bitpiece |= DiagSWMsk, (x)->bitpiece &= (((uint64_t)(y) << DiagSWPos) | ~DiagSWMsk))
#define SetDSEField(x, y) ((x)->bitpiece |= DiagSEMsk, (x)->bitpiece &= (((uint64_t)(y) << DiagSEPos) | ~DiagSEMsk))
#define SetNightField(x, y) ((x)->bitpiece |= NightFieldMsk, (x)->bitpiece &= (((uint64_t)(y) << NightFieldPos) | ~NightFieldMsk)
#define SetNightNE(x, y) ((x)->bitpiece |= NightNEMsk, (x)->bitpiece &= (((uint64_t)(y) << NightNEPos) | ~NightNEMsk))
#define SetNightNW(x, y) ((x)->bitpiece |= NightNWMsk, (x)->bitpiece &= (((uint64_t)(y) << NightNWPos) | ~NightNWMsk))
#define SetNightSE(x, y) ((x)->bitpiece |= NightSEMsk, (x)->bitpiece &= (((uint64_t)(y) << NightSEPos) | ~NightSEMsk))
#define SetNightSW(x, y) ((x)->bitpiece |= NightSWMsk, (x)->bitpiece &= (((uint64_t)(y) << NightSWPos) | ~NightSWMsk))
#define SetNightEN(x, y) ((x)->bitpiece |= NightENMsk, (x)->bitpiece &= (((uint64_t)(y) << NightENPos) | ~NightENMsk))
#define SetNightES(x, y) ((x)->bitpiece |= NightESMsk, (x)->bitpiece &= (((uint64_t)(y) << NightESPos) | ~NightESMsk))
#define SetNightWN(x, y) ((x)->bitpiece |= NightWNMsk, (x)->bitpiece &= (((uint64_t)(y) << NightWNPos) | ~NightWNMsk))
#define SetNightWS(x, y) ((x)->bitpiece |= NightWSMsk, (x)->bitpiece &= (((uint64_t)(y) << NightWSPos) | ~NightWSMsk))
#define SetTwoMove(x, y) ((x)->bitpiece |= TwoMoveMsk, (x)->bitpiece &= (((uint64_t)(y) << TwoMovePos) | ~TwoMoveMsk))

/* Get Bits */
#define GetV(x) (((x) & VertBit) >> VertPos)
#define GetH(x) (((x) & HoriBit) >> HoriPos)
#define GetD(x) (((x) & DiagBit) >> DiagPos)
#define GetCastling(x) (((x) & CastlingBit) >> CastlingPos)
/* Get Field */
#define GetVPveField(x) (((x) & VertPveMsk) >> VertFieldPvePos)
#define GetVNveField(x) (((x) & VertNveMsk) >> VertFieldNvePos)
#define GetHPveField(x) (((x) & HoriPveMsk) >> HoriFieldPvePos)
#define GetHNveField(x) (((x) & HoriNveMsk) >> HoriFieldNvePos)
#define GetDNWField(x) (((x) & DiagNWMsk) >> DiagNWPos)
#define GetDNEField(x) (((x) & DiagNEMsk) >> DiagNEPos)
#define GetDSWField(x) (((x) & DiagSWMsk) >> DiagSWPos)
#define GetDSEField(x) (((x) & DiagSEMsk) >> DiagSEPos)
#define GetNightField(x) (((x) & NightFieldMsk) >> NightFieldPos)
#define GetPin(x) (((x) & PinMsk) >> PinPos)
#define GetNightNE(x) (((x) & NightNEMsk) >> NightNEPos)
#define GetNightNW(x) (((x) & NightNWMsk) >> NightNWPos)
#define GetNightSE(x) (((x) & NightSEMsk) >> NightSEPos)
#define GetNightSW(x) (((x) & NightSWMsk) >> NightSWPos)
#define GetNightEN(x) (((x) & NightENMsk) >> NightENPos)
#define GetNightES(x) (((x) & NightESMsk) >> NightESPos)
#define GetNightWN(x) (((x) & NightWNMsk) >> NightWNPos)
#define GetNightWS(x) (((x) & NightWSMsk) >> NightWSPos)
#define GetTwoMove(x) (((x) & TwoMoveMsk) >> TwoMovePos)
/* Pieces */
#define PieceMsk (VertBit | HoriBit | DiagBit | KQBit)
#define GetPiece(x) ((x) & PieceMsk)
#define WPawn (VertBit | DiagBit | WHITE)
#define WRook (VertBit | HoriBit | WHITE)
#define WNight (0x0 | WHITE)
#define WBishop (DiagBit | WHITE)
#define WQueen (VertBit | HoriBit | DiagBit | WHITE)
#define WKing (VertBit | HoriBit | DiagBit | CastlingBit | KQBit | WHITE)
#define BPawn (VertBit | DiagBit)
#define BRook (VertBit | HoriBit)
#define BNight (0x0)
#define BBishop (DiagBit)
#define BQueen (VertBit | HoriBit | DiagBit)
#define BKing (VertBit | HoriBit | DiagBit | CastlingBit | KQBit)
#define King (VertBit | HoriBit | DiagBit | KQBit)
#define Pawn   BPawn
#define Rook   BRook
#define Night  BNight
#define Bishop BBishop
#define Queen  BQueen
#define Coordinate(t) (t)->pos.x + 'a', (t)->pos.y
extern const short MoveAlongX[];
extern const short MoveAlongY[];
extern const short NightMoveAlongX[];
extern const short NightMoveAlongY[];
//---- for piece list ----
void init_piece_list(piece_list_t* l);
void destroy_piece(piece_t *piece);
void insert_piece(piece_list_t *l, piece_t *p);
void delete_piece(piece_list_t *l, piece_t *piece);
piece_t *get_next(piece_list_t *l);
void destroy_piece_list(piece_list_t *l);

void init_piece_list(piece_list_t* l);
void degen_list(chess_t *chess, board_t board, piece_t *piece);
void gen_list(chess_t *chess, board_t board, piece_t *piece);
int getnumofelem(piece_list_t *l);
//---- for piece list ----

void print_all_list(piece_t *p);
void init_piece(piece_t *piece, char p, pos_t pos);
void printpieceinfo(piece_t *piece);
piece_t *findpiece(board_t board, int sx, int sy, int dirx, int diry, int *dx, int *dy);
#endif

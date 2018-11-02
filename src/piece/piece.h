#ifndef PIECES_H
#define PIECES_H


#include "../includes.h"
/*
 *	        NSEW -ve  +ve  -ve  +ve  SW   SE   NE   NW
 *	TE xLPC TTTT VVVV VVVV HHHH HHHH DDDD DDDD DDDD DDDD xxxK/Q VHDC
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
/* Bits */
#define VertBit (1 << VertPos)
#define HoriBit (1 << HoriPos)
#define DiagBit (1 << DiagPos)
#define KQBit (1 << KQPos)
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
#define NightWBitPos (40)
#define NightEBitPos (41)
#define NightSBitPos (42)
#define NightNBitPos (43)
#define CheckPos (44)
#define PinPos (45)
#define LMSPos (46)
#define EnPassantPos (48)
#define TwoMovePos (49)
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
#define NightNEMsk ((1UL << NightNBitPos) | (1UL << NightEBitPos))
#define NightSEMsk ((1UL << NightSBitPos) | (1UL << NightEBitPos))
#define NightSWMsk ((1UL << NightSBitPos) | (1UL << NightWBitPos))
#define NightNWMsk ((1UL << NightNBitPos) | (1UL << NightWBitPos))
#define CheckMsk (1UL << CheckPos)
#define PinMsk (1UL << PinPos)
#define LMSMsk (1UL << LMSPos)
#define EnPassantMsk (1UL << EnPassantPos)
#define TwoMoveMsk (1UL << TwoMovePos)
/*
 *	        NSEW -ve  +ve  -ve  +ve  SW   SE   NE   NW
 *	TE xLPC TTTT VVVV VVVV HHHH HHHH DDDD DDDD DDDD DDDD xxxK/Q VHDC
 */
/* Set Bits */
#define SetV(x) ((x) |= VertBit)
#define SetH(x) ((x) |= HoriBit)
#define SetD(x) ((x) |= DiagBit)
#define SetK(x) ((x) |= VertBit | HoriBit | DiagBit | KQBit)
/* Set Field */
#define SetVPveField(x) ((((uint64_t)x) << VertFieldPvePos) & VertPveMsk)
#define SetVNveField(x) (((uint64_t)(x) << VertFieldNvePos) & VertNveMsk)
#define SetHPveField(x) (((uint64_t)(x) << HoriFieldPvePos) & HoriPveMsk)
#define SetHNveField(x) (((uint64_t)(x) << HoriFieldNvePos) & HoriNveMsk)
#define SetDNWField(x) (((uint64_t)(x) << DiagNWPos) & DiagNWMsk)
#define SetDNEField(x) (((uint64_t)(x) << DiagNEPos) & DiagNEMsk)
#define SetDSWField(x) (((uint64_t)(x) << DiagSWPos) & DiagSWMsk)
#define SetDSEField(x) (((uint64_t)(x) << DiagSEPos) & DiagSEMsk)
#define SetNightNE NightNEMsk
#define SetNightNW NightNWMsk
#define SetNightSE NightSEMsk
#define SetNightSW NightSWMsk

/* Get Bits */
#define GetV(x) ((x) & VertBit)
#define GetH(x) ((x) & HoriBit)
#define GetD(x) ((x) & DiagBit)
/* Get Field */
#define GetVPveField(x) (((x) & VertPveMsk) >> VertFieldPvePos)
#define GetVNveField(x) (((x) & VertNveMsk) >> VertFieldNvePos)
#define GetHPveField(x) (((x) & HoriPveMsk) >> HoriFieldPvePos)
#define GetHNveField(x) (((x) & HoriNveMsk) >> HoriFieldNvePos)
#define GetDNWField(x) (((x) & NightNWMsk) >> NightFieldPos)
#define GetDNEField(x) (((x) & NightNEMsk) >> NightFieldPos)
#define GetDSWField(x) (((x) & NightSWMsk) >> NightFieldPos)
#define GetDSEField(x) (((x) & NightSEMsk) >> NightFieldPos)
#define GetPin(x) (((x) & PinMsk) >> PinPos)

/* Pieces */
#define PieceMsk (VertBit | HoriBit | DiagBit)
#define WPawn (VertBit | DiagBit | WHITE)
#define WRook (VertBit | HoriBit | WHITE)
#define WNight (0x0 | WHITE)
#define WBishop (DiagBit | WHITE)
#define WQueen (VertBit | HoriBit | DiagBit | WHITE)
#define WKing (VertBit | HoriBit | DiagBit | KQBit | WHITE)
#define BPawn (VertBit | DiagBit)
#define BRook (VertBit | HoriBit)
#define BNight (0x0)
#define BBishop (DiagBit)
#define BQueen (VertBit | HoriBit | DiagBit)
#define BKing (VertBit | HoriBit | DiagBit | KQBit)
#define King BKing



//---- for piece list ----
void init_piece_list(piece_list_t* l);
void insert_piece(piece_list_t *l, piece_t *p);
void delete_piece(piece_list_t *l, size_t pos);
piece_t *get_next(piece_list_t *l);
void destroy_piece_list(piece_list_t *l);

void init_piece_list(piece_list_t* l);
//---- for piece list ----

void init_piece(piece_t *piece, char p, pos_t pos);
#endif

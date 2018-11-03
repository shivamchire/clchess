#ifndef PIECES_H
#define PIECES_H


#include "../includes.h"
/*
 *                  -ve  +ve  -ve  +ve  SW   SE   NE   NW
 * E xLPC TTTT TTTT VVVV VVVV HHHH HHHH DDDD DDDD DDDD DDDD xxxK/Q VHDC
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
#define EnPassantPos (51)
//#define TwoMovePos (49)
/*
 *                  -ve  +ve  -ve  +ve  SW   SE   NE   NW
 * E xLPC TTTT TTTT VVVV VVVV HHHH HHHH DDDD DDDD DDDD DDDD xxxK/Q VHDC
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
//#define TwoMoveMsk (1UL << TwoMovePos)
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
#define SetNightField(x) ((uint64_t)(x) << NightFieldPos)
#define SetNightNE NightNEMsk
#define SetNightNW NightNWMsk
#define SetNightSE NightSEMsk
#define SetNightSW NightSWMsk
#define SetNightEN NightENMsk
#define SetNightES NightESMsk
#define SetNightWN NightWNMsk
#define SetNightWS NightWSMsk

/* Get Bits */
#define GetV(x) (((x) & VertBit) >> VertPos)
#define GetH(x) (((x) & HoriBit) >> HoriPos)
#define GetD(x) (((x) & DiagBit) >> DiagPos)
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

#include "data.h"

/*----------------BoardData-----------*/

#if dynamicChess == 1
u64 maxJ = 2;
/*These defaults are updated by fen reader*/
u64         bRow = 8;
u64         bCol = 8;
u64         bSz = bRow * bCol;
u64         pBRow = (bRow + maxJ * 2);
u64         pBCol = (bCol + (maxJ - 1) * 2);
u64         pBSz = pBRow * pBCol;
vector<u64>      pieceAt(pBSz);      // boardPadded
vector<u64>      board(bSz);        // board
vector<u64> boardIndexP(bSz);  // index of board data in pieceAt

#elif dynamicChess == 0

array<u64, pBSz>     pieceAt;
array<u64, bSz>      board;
array<u64, bSz> boardIndexP;
//array<u64, pBSz>     indexAt;
#endif

vector<u64> indexAt(pBSz);

/*----------------BoardData-----------*/

/*---------Pieces Data----------*/

array<u8, 24> dPce{
    "."
	"PNBRQK"
	"pnbrqk"
    "xxxxxx"
	"xxxx"};

s64 knightM[]{jumperP,
              (dN + dN + dE),
              (dN + dN + dW),  //
              (dS + dS + dE),
              (dS + dS + dW),  //
              (dE + dE + dN),
              (dE + dE + dS),  //
              (dW + dW + dN),
              (dW + dW + dS),  //
              0};
s64 bishopM[]{sliderP, dNE, dNW, dSE, dSW, 0};
s64 rookM[]{sliderP, dN, dS, dE, dW, 0};
s64 kingM[]{jumperP, dN, dS, dE, dW, dNE, dNW, dSE, dSW, 0};

s64 *queenM[]{(s64 *)compoundP, rookM, bishopM, nullptr};

s64 wPawnM[]{dN, dNE, dNW, 0};
s64 bPawnM[]{dS, dSE, dSW, 0};

int          activeSide{3};
unsigned int castle{0};
int          ep{invalidPiece};
int          halfMc{0};
int          fullMc{0};
/*---------Pieces Data----------*/

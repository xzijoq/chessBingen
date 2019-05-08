#include "data.h"

/*----------------BoardData-----------*/

#if dynamicChess == 1
short int maxJ = 2;
/*These defaults are updated by fen reader*/
short int         bRow = 8;
short int         bCol = 8;
short int         bSz = bRow * bCol;
short int         pBRow = (bRow + maxJ * 2);
short int         pBCol = (bCol + (maxJ - 1) * 2);
short int         pBSz = pBRow * pBCol;
vector<char>      pBoard(pBSz);      // boardPadded
vector<char>      board(bSz);        // board
vector<short int> boardIndexP(bSz);  // index of board data in pBoard

#elif dynamicChess == 0

array<char, pBSz>     pBoard;
array<char, bSz>      board;
array<short int, bSz> boardIndexP;
#endif
/*----------------BoardData-----------*/

/*---------Pieces Data----------*/


s64 knightM[]{jumperP,
    (dN + dN + dE), (dN + dN + dW),  //
    (dS + dS + dE), (dS + dS + dW),  //
    (dE + dE + dN), (dE + dE + dS),  //
    (dW + dW + dN), (dW + dW + dS),  //
	0
};
s64 bishopM[]{sliderP,dNE, dNW, dSE, dSW,0};
s64 rookM[]{sliderP, dN, dS, dE, dW, 0};
s64 kingM[]{jumperP,dN, dS, dE, dW, dNE, dNW, dSE, dSW, 0};

s64 *queenM[]{(s64*)compoundP,rookM,bishopM,nullptr};

s64 wPawnM[]{dN, dNE, dNW, 0};
s64 bPawnM[]{dS, dSE, dSW,0};


/*---------Pieces Data----------*/

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

array<s64, 8> knightM{
    (dN + dN + dE), (dN + dN + dW),  //
    (dS + dS + dE), (dS + dS + dW),  //
    (dE + dE + dN), (dE + dE + dS),  //
    (dW + dW + dN), (dW + dW + dS)   //
};
array<s64, 4> bishopM{dNE, dNW, dSE, dSW};
array<s64, 4> rookM{dN, dS, dE, dW};
array<s64, 8> kingM{dN, dS, dE, dW, dNE, dNW, dSE, dSW};
array<s64, 3> wPawnM{dN, dNE, dNW};
array<s64, 3> bPawnM{dS, dSE, dSW};


/*---------Pieces Data----------*/

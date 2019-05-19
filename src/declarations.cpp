#include "data.h"

#pragma region Board
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

#pragma endregion

#pragma region Pieces
/*---------Pieces Data----------*/

unordered_map<u8, u8> displayMap{
    {invalidPiece, '+'}, {noPiece, '-'}, {moveDebug, '.'},
    {captureDebug, '*'}, /*Fancy*/
    {wP, 'P'},           {wN, 'N'},      {wB, 'B'},
    {wR, 'R'},           {wQ, 'Q'},      {wK, 'K'}, /*white*/
    {bP, '$'},           {bN, 'n'},      {bB, 'b'},
    {bR, 'r'},           {bQ, 'q'},      {bK, 'k'} /*black*/
};

array<u64, maxPosMv> mvList;
array<u64, maxPosMv> mvListCap;

u64                             wPawnL[50];
u64                             wRookL[50];
u64                             wQueenL[50];
u64                             wBishopL[50];
u64                             wKnightL[50];
u64                             wKingL[50];
u64                             bPawnL[50];
u64                             bRookL[50];
u64                             bQueenL[50];
u64                             bBishopL[50];
u64                             bKnightL[50];
u64                             bKingL[50];
u64                             noPieceL[2];
u64                             invalidPieceList[2];
const unordered_map<u64, u64 *> listOf{

    {wP, wPawnL},
    {bP, bPawnL},
    {wN, wKnightL},
    {bN, bKnightL},
    {wB, wBishopL},
    {bB, bBishopL},
    {wR, wRookL},
    {bR, bRookL},
    {wQ, wQueenL},
    {bQ, bQueenL},
    {wK, wKingL},
    {bK, bKingL},
    {invalidPiece, noPieceL},
    {noPiece, invalidPieceList}

};


//constexpr u64        maxPiece{30};
array<u64, maxPiece> wLongList;
array<u64, maxPiece> bLongList;
array<array<u64, maxPiece>, maxPiece> pieceList;

int wPc{0}, wNc{0}, wBc{0}, wRc{0}, wQc{0}, wKc{0};
int bPc{0}, bNc{0}, bBc{0}, bRc{0}, bQc{0}, bKc{0};


int wPat{0}, wNat{0}, wBat{0}, wRat{0}, wQat{0}, wKat{0};
int bPat{0}, bNat{0}, bBat{0}, bRat{0}, bQat{0}, bKat{0};

int wPstart{0}, wNstart{0}, wBstart{0}, wRstart{0}, wQstart{0}, wKstart{0};
int bPstart{0}, bNstart{0}, bBstart{0}, bRstart{0}, bQstart{0}, bKstart{0};

#pragma endregion
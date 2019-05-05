#include "data.h"

/*----------------BoardData-----------*/

#if dynamicChess == 1
short int maxJ = 2;
/*These defaults are updated by fen reader*/
short int         bRow = 8;
short int         bCol = 8;
short int         bSz = bRow * bCol;
short int         bPRow = (bRow + maxJ * 2);
short int         bPCol = (bCol + (maxJ - 1) * 2);
short int         bPSz = bPRow * bPCol;
vector<char>      boardP(bPSz);      // boardPadded
vector<char>      board(bSz);        // board
vector<short int> boardIndexP(bSz);  // index of board data in boardP

#elif dynamicChess == 0

array<char, bPSz>     boardP;
array<char, bSz>      board;
array<short int, bSz> boardIndexP;
#endif
/*----------------BoardData-----------*/

/*---------Pieces Data----------*/
enum pW /*piecesWhite*/
{
   npW,
   wp,
   wr,
   wn,
   wb,
   wq,
   wk
};
enum pB /*piecesBlack*/
{
   npB,
   bp,
   br,
   bn,
   bb,
   bq,
   bk
};

/*---------Pieces Data----------*/

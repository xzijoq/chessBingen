#pragma once
#include <array>
#include <cassert>
#include <cstring>
#include <iostream>
#include <map>
#include <vector>

#define debug
#ifdef debug
#define D(x) x
#else
#define D(x)
#endif  // DEBUG

// In the Beginning there was nothing but void
#define hailSithis void *
#define convertThis (void *)

using namespace std;
// max board size is 256 (or update in move to square to from square)

#define dynamicChess 0

using u64 = unsigned long long int;
using s64 = signed long long int;
using u8 = unsigned char;
using u32 = unsigned int;

#pragma region BoardStructure
/* --------------BOARD DATA------------------*/
#if dynamicChess == 1
extern u64 maxJ; /*knight can jump 2square out of board*/
/*Boards Data*/
extern u64 bRow; /*board Size Row*/
extern u64 bCol; /*board Size Col*/
extern u64 bSz;  /*board Size*/

extern u64         pBRow;        /*padded Board Row Count*/
extern u64         pBCol;        /*padded Board Col Count*/
extern u64         pBSz;         /*padded Board Size*/
extern vector<u64> pBoard;       // boardPadded
extern vector<u64> board;        // board
extern vector<u64> boardIndexP;  // index of board data in pBoard

#elif dynamicChess == 0
constexpr u64 maxJ = 2;
constexpr u64 bRow{8};
constexpr u64 bCol{8};
constexpr u64 bSz = bRow * bCol;
constexpr u64 pBRow = (bRow + maxJ * 2);
constexpr u64 pBCol = (bCol + (maxJ - 1) * 2);
constexpr u64 pBSz = pBRow * pBCol;
/*The Boards */
extern array<u64, pBSz> pBoard;       // boardPadded
extern array<u64, bSz>  board;        // board
extern array<u64, bSz>  boardIndexP;  // index of board data in pBoard
extern array<u64, pBSz> pBoardC;      // boardPaddedCopy
                                      // extern array<u64, pBSz>       atIndex;
                                      /*TheBoards End*/
#endif

extern vector<u64> atIndex;  // board that index piece

extern int          activeSide;
extern unsigned int castle;
extern int          ep;
extern int          halfMc;
extern int          fullMc;

#define getRank(pos) (((int)(pos / pBCol)) - (maxJ - 1))
#define getFile(pos) (((int)(pos % pBCol)) - (maxJ - 1 - 1))

inline int getPIndex(int cfile, int rank)
{
   if (((cfile - 'a') > (bRow - 1)) || rank > bCol || cfile < 0 || rank < 0)
   {
      cout << "out of bound boardWrongFEn getPindex()";
      cfile = 'a';
      rank = 1;
   }
   cout << " file: " << (u8)(cfile) << " rank: " << rank << endl;
   // cout << "Inde "
   //  cout << boardIndexP[(((cfile - 'a') + (1)) + ((rank - 1) * (bCol))) - 1];
   //<< " ";
   return (int)((((cfile - 'a') + (1) + (maxJ - 1)) + ((rank - 1) * (pBCol))) +
                (maxJ * pBCol) - 1);
}

inline int getPIndex(string pos)
{ /*max 2 digit rank*/
   int cfile, rank;
   cfile = pos[0];
   (pos.size() > 2) ? rank = (((pos[1] * 10) - '0') + (pos[2] - '0'))
                    : rank = (pos[1]) - '0';

   return (int)((((cfile - 'a') + (1) + (maxJ - 1)) + ((rank - 1) * (pBCol))) +
                (maxJ * pBCol) - 1);
}

#pragma endregion BoardStructure

// constexpr u8 invalidPiece = '+';
// constexpr u8 noPiece = '-';

constexpr u8 moveDebug = '.';
constexpr u8 captureDebug = '*';

constexpr int errorFlag_D{123};

#pragma region packedMove
/*           Packed Move DATA
 ffff 0000 00 11 ff ffff
Warning: The number that Gets shifted in should be u64 */
extern u64 pkdMove;                        /*defined in pieces.cpp*/
#define frSq(m) ((m) & (0x3ff))            /*frmSquare      [10] bits(1023)*/
#define toSq(m) (((m) >> 10) & (0x3ff))    /*toSquare       [10]+10=20*/
#define prmP(m) (((m) >> 20) & (0x3f))     /*promoted piece [6] +20=26 (63)*/
constexpr u64 epFg{0x4000000};             /*enPassant flag  27th bit*/
constexpr u64 psFg{0x8000000};             /*PawnStart flag  28th bit*/
constexpr u64 csFg{0x10000000};            /*Castle    flag  29th bit*/
constexpr u64 cpFg{0x20000000};            /*Capture   flag  30th bit*/
#define movP(m) (((m) >> 30) & (0xff))     /*moving   Piece [8]+30=38(255)*/
#define capP(m) (((m) >> 38) & (0xff))     /*captured Piece [8]+38=46(255)*/
#define mVal(m) (((m) >> 46) & (0x3ffff))  /*moveValue [18]+46=64 (262143)*/
constexpr u64 lastBit{0x8000000000000000}; /*The Last Bit   64th bit*/
constexpr u64 noFg{0x0};
inline u64    Mv(u64 frmSq, u64 toSq, u64 flag, u64 prmP, u64 startPiece,
                 u64 capPiece, u64 moveValue)
{ /*TODO add move value*/
   return (frmSq) | (toSq << 10) | (prmP << 20) | (flag) | (startPiece << 30) |
          (capPiece << 38) | (moveValue << 46);
}
/* END PACKED MOVE DATA*/
#pragma endregion

constexpr int maxPosMv{1024}; /*maximum moves possible in a position*/
struct moveList
{
   array<u64, maxPosMv> pkdMv;
   int                  mvCount{0}; /*care Man*/
};
extern moveList mvList;
inline void     pshMv(u64 mv)
{
   mvList.pkdMv[mvList.mvCount] = mv;
   mvList.mvCount++;
}

extern array<u8, 24> dPce;
constexpr int        blackOffset{6};  // 6
extern map<u8, u8>   displayMap;

#pragma region pieceAndDirection

#define dN (pBCol)
#define dS (-dN)
#define dE (1)
#define dW (-1)
#define dNE (dN + dE)
#define dNW (dN + dW)
#define dSE (dS + dE)
#define dSW (dS + dW)

/*MoveArray*/
extern s64  knightM[];
extern s64  bishopM[];
extern s64  rookM[];
extern s64  kingM[];
extern s64 *queenM[];
extern s64  wPawnM[];
extern s64  bPawnM[];

constexpr s64 sliderP{1};
constexpr s64 jumperP{2};
constexpr s64 compoundP{3};
constexpr s64 endMoves{9};
/*MoveArray end*/

enum materialValue : u8
{
   pawnB = 12

};

enum pieceGeneric : u8
{
   noPiece = 0B00000000,
   pawn = 0B00000001,
   knight = 0B00000010,
   bishop = 0B00000011,
   rook = 0B00000100,
   queen = 0B00001000,
   king = 0B00100000,
   fenRowBreak = 0B11111110,
   invalidPiece = 0B11111111
};
enum color : u8
{
   black = 0B00000000,
   white = 0B10000000
};
enum piec : u8 /*piecesWhite*/
{
   nP,
   wP = white | pawn,
   wN = white | knight,
   wB = white | bishop,
   wR = white | rook,
   wQ = white | queen,
   wK = white | king,

   bP = black | pawn,
   bN = black | knight,
   bB = black | bishop,
   bR = black | rook,
   bQ = black | queen,
   bK = black | king
};

extern u64                   wPawnL[];
extern u64                   wRookL[];
extern u64                   wQueenL[];
extern u64                   wBishopL[];
extern u64                   wKnightL[];
extern u64                   wKingL[];
extern u64                   bPawnL[];
extern u64                   bRookL[];
extern u64                   bQueenL[];
extern u64                   bBishopL[];
extern u64                   bKnightL[];
extern u64                   bKingL[];

#pragma endregion

#pragma region functionDefinitions
/* DEFINITIONS */
/*board*/
extern void boardsInit();
extern void boardDisplay(string boarD);
extern void boardDisplay(vector<u64> boarD);

extern void dire();
extern void boardPFill(bool display = true);
extern void boardFill();

/*move and piece*/
extern void inline moveGena(int pos, u64 piece = noPiece);
extern void inline queenMGen(int pos, int color);
extern void inline pawnMGen(int pos, int color);
extern void genMove(s64 *pieceM, int pos, int color);
extern void genMove(s64 **pieceM, int pos, int color);
extern void fillPieceList();
/* DEFINITIONS */
#pragma endregion
/*--------BOARD DATA END--------------*/

/*
craap

extern void inline wPawnMGen(int pos);
extern void inline bPawnMGen(int pos);


//extern array<s64, 120> pieces;

extern array<s64, 8> knightM;
extern array<s64, 4> bishopM;
extern array<s64, 4> rookM;
extern array<s64, 8> kingM;
extern array<s64, 3> wPawnM;
extern array<s64, 3> bPawnM;

constexpr array<s64, 8> knightM{
    (dN + dN + dE), (dN + dN + dW),  //
    (dS + dS + dE), (dS + dS + dW),  //
    (dE + dE + dN), (dE + dE + dS),  //
    (dW + dW + dN), (dW + dW + dS)   //
};
constexpr array<s64, 4> bishopM{dNE, dNW, dSE, dSW};
constexpr array<s64, 4> rookM{dN, dS, dE, dW};
constexpr array<s64, 8> kingM{dN, dS, dE, dW, dNE, dNW, dSE, dSW};
constexpr array<s64, 3> wPawnM{dN, dNE, dNW};
constexpr array<s64, 3> bPawnM{dS, dSE, dSW};


// extern template void staticMoveGen(const array<s64, SZ> &piece, u8 pos,
// u8 color=white);
extern void inline knightMGen(int pos);
extern void inline kingMGen(int pos);
extern void inline rookMGen(int pos);
extern void inline bishopMGen(int pos);
*/
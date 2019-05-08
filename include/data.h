#pragma once
#include <array>
#include <cassert>
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;
// max board size is 256 (or update in move to square to from square)

#define dynamicChess 0

using u64 = unsigned long long int;
using s64 = signed long long int;


constexpr char invalidSquare = '+';
constexpr char emptySquare = '-';
constexpr char moveDebug = '.';
constexpr char captureDebug = '*';
constexpr int  black = 0;
constexpr int  white = 1;
constexpr int errorFlag_D{123};

/*           Packed Move DATA
Warning: The number that Gets shifted in should be u64 */
extern u64 pkdMove;                        /*defined in pieces.cpp*/
#define frSq(m) ((m) & (0x3ff))            /*frmSquare [10] bits(1023)*/
#define toSq(m) (((m) >> 10) & (0x3ff))    /*toSquare  [10] +10=20*/
#define capP(m) (((m) >> 20) & (0xff))     /*captured Piece [8]+20=28(255)*/
#define prmD(m) (((m) >> 28) & (0xff))     /*promoted piece [8]+28=36*/
#define mVal(m) (((m) >> 40) & (0x7fffff)) /*moveValue [23]+36+4(flags)=63*/
constexpr u64 epFg{0x1000000000};          /*enPassant flag 37th bit*/
constexpr u64 psFg{0x2000000000};          /*PawnStart flag 38th bit*/
constexpr u64 csFg{0x4000000000};          /*Castle    flag 39th bit*/
constexpr u64 cpFg{0x8000000000};          /*Capture   flag 40th bit*/
constexpr u64 lastBit{0x8000000000000000}; /*The Last Bit   64th bit*/
/* END PACKED MOVE DATA*/



constexpr s64 sliderP{1};
constexpr s64 jumperP{2};
constexpr s64 compoundP{3};
constexpr s64 endMoves{9};

#define dN (pBCol)
#define dS (-dN)
#define dE (1)
#define dW (-1)
#define dNE (dN + dE)
#define dNW (dN + dW)
#define dSE (dS + dE)
#define dSW (dS + dW)

enum pieceGeneric
{
   noPiece,
   pawn,
   rook,
   knight,
   bishop,
   queen,
   king
};
enum piW /*piecesWhite*/
{
   nP,
   wp,
   wr,
   wn,
   wb,
   wq,
   wk,
   bp,
   br,
   bn,
   bb,
   bq,
   bk
};

extern s64  knightM[];
extern s64  bishopM[];
extern s64  rookM[];
extern s64  kingM[];
extern s64 *queenM[];
extern s64  wPawnM[];
extern s64  bPawnM[];

/* DEFINITIONS */

/*board*/
void boardsInit();
void boardDisplay(string boarD);
void dire();
void boardPFill(bool display = true);
void boardFill();

/*move and piece*/
extern void inline moveGena(int pos, char piece = noPiece);

extern void inline queenMGen(int pos, int color);
extern void inline pawnMGen(int pos, bool color);

void genMove(s64 *pieceM, int pos, int color);
void genMove(s64 **pieceM, int pos, int color);

/* DEFINITIONS */

/*--------------PIECES DATA-------------*/

/* value castle promoted-piece eP  captured toSq fromSq*/

/*----------------PIECES DATA END--------*/
/* --------------BOARD DATA------------------*/
#if dynamicChess == 1
extern short int maxJ; /*knight can jump 2square out of board*/
/*Boards Data*/
extern short int bRow; /*board Size Row*/
extern short int bCol; /*board Size Col*/
extern short int bSz;  /*board Size*/

extern short int         pBRow;        /*padded Board Row Count*/
extern short int         pBCol;        /*padded Board Col Count*/
extern short int         pBSz;         /*padded Board Size*/
extern vector<char>      pBoard;       // boardPadded
extern vector<char>      board;        // board
extern vector<short int> boardIndexP;  // index of board data in pBoard

#elif dynamicChess == 0
constexpr short int maxJ = 2;
constexpr short int bRow{8};
constexpr short int bCol{8};
constexpr short int bSz = bRow * bCol;
constexpr short int pBRow = (bRow + maxJ * 2);
constexpr short int pBCol = (bCol + (maxJ - 1) * 2);
constexpr short int pBSz = pBRow * pBCol;
/*The Boards */
extern array<char, pBSz>       pBoard;       // boardPadded
extern array<char, bSz>        board;        // board
extern array<short int, bSz>   boardIndexP;  // index of board data in pBoard
extern array<char, pBSz>       pBoardC;      // boardPaddedCopy
static constexpr array<int, 4> lol{1, 2, 3, 4};
/*TheBoards End*/
#endif
extern int side;
extern int xside;
extern int castle;
extern int ep;
extern int fifty;
extern int hash;
extern int ply;
extern int hply;
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


// extern template void staticMoveGen(const array<s64, SZ> &piece, char pos,
// char color=white);
extern void inline knightMGen(int pos);
extern void inline kingMGen(int pos);
extern void inline rookMGen(int pos);
extern void inline bishopMGen(int pos);
*/
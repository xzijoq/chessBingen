#pragma once
#include <array>
#include <cassert>
#include <cstring>
#include <iostream>
#include <vector>

#define dynamicChess 0
constexpr char invalidSquare = '+';
constexpr char emptySquare = '-';
constexpr char moveDebug = '.';
constexpr char captureDebug = '*';
constexpr int  black = 0;
constexpr int  white = 1;

constexpr int errorFlag_D{123};
using namespace std;
using u64 = unsigned long long int;
using s64 = signed long long int;
/* DEFINITIONS */
void boardsInit();
void boardDisplay(string boarD);
void dire();
void boardPFill(bool display = true);
/* DEFINITIONS */
/*--------------PIECES DATA-------------*/

#define dN (pBCol)
#define dS (-dN)
#define dE (1)
#define dW (-1)
#define dNE (dN + dE)
#define dNW (dN + dW)
#define dSE (dS + dE)
#define dSW (dS + dW)

/*castle promoted-piece eP  captured toSq fromSq*/
extern u64 move;

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

extern array<s64, 120> pieces;

extern array<s64, 8> knightM;
extern array<s64, 4> bishopM;
extern array<s64, 4> rookM;
extern array<s64, 8> kingM;
extern array<s64, 3> wPawnM;
extern array<s64, 3> bPawnM;

/*
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
*/
extern void inline moveGen(int pos, char piece = noPiece);

extern void inline knightMGen(int pos);
extern void inline kingMGen(int pos);
extern void inline rookMGen(int pos);
extern void inline bishopMGen(int pos);
extern void inline queenMGen(int pos,int color);
extern void inline pawnMGen(int pos, bool color);
extern void inline wPawnMGen(int pos);
extern void inline bPawnMGen(int pos);

//extern template void staticMoveGen(const array<s64, SZ> &piece, char pos, char color=white);

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
extern array<char, pBSz>     pBoard;       // boardPadded
extern array<char, bSz>      board;        // board
extern array<short int, bSz> boardIndexP;  // index of board data in pBoard
extern array<char, pBSz>     pBoardC;      // boardPaddedCopy
static constexpr array<int, 4> lol{1,2,3,4};
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
template <std::size_t SZ>
void staticMoveGen(const array<s64, SZ> &piece, int pos, char color)
{
   for (auto j{0}; j < piece.size(); j++)
   {
      moveT = pos + piece[j];
      if (pBoard[moveT] == invalidSquare)
      {
         continue;
      }
      if (pBoard[moveT] != emptySquare && pBoard[moveT] != moveDebug)
      {
         pBoard[moveT] = captureDebug;
         ;
      }
      else
      {
         pBoard[moveT] = moveDebug;
      }
   }
}
template <size_t SZ>
void slidingMoveGen(array<s64, SZ> piece, int pos, char color)
{
   for (auto j{0}; j < piece.size(); j++)
   {
      for (s64 i{1}; i < 256; i++)
      {
         moveT = pos + (piece[j] * i);

         if (pBoard[moveT] == invalidSquare)
         {
            break;
         }
         if (pBoard[moveT] != emptySquare)
         {
            if (pBoard[moveT] == moveDebug)
            {
               continue;
            }
            pBoard[moveT] = captureDebug;
            break;
         }
         else
         {
            pBoard[moveT] = moveDebug;
         }
      }
   }
}
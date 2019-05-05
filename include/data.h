#pragma once
#include <array>
#include <cassert>
#include <cstring>
#include <iostream>
#include <vector>

#define dynamicChess 1
constexpr int errorFlag_D {123};
using namespace std;
using u64 = unsigned long long int;
/* DEFINITIONS */
void boardsInit();
void boardDisplay(string boarD, bool index = false);
void dire();
void boardPFill(bool display = true);
/* DEFINITIONS */
/*--------------PIECES DATA-------------*/
enum pW; /*piecesWhite*/
enum pB; /*piecesBlack*/
extern array<u64, 120> pieces;
/*----------------PIECES DATA END--------*/
/* --------------BOARD DATA------------------*/
#if dynamicChess == 1
extern short int maxJ; /*knight can jump 2square out of board*/
/*Boards Data*/
extern short int bRow; /*board Size Row*/
extern short int bCol; /*board Size Col*/
extern short int bSz;  /*board Size*/

extern short int         bPRow;        /*padded Board Row Count*/
extern short int         bPCol;        /*padded Board Col Count*/
extern short int         bPSz;         /*padded Board Size*/
extern vector<char>      boardP;       // boardPadded
extern vector<char>      board;        // board
extern vector<short int> boardIndexP;  // index of board data in boardP

#elif dynamicChess == 0
constexpr short int maxJ = 2;
constexpr short int bRow{8};
constexpr short int bCol{8};
constexpr short int bSz = bRow * bCol;
constexpr short int bPRow = (bRow + maxJ * 2);
constexpr short int bPCol = (bCol + (maxJ - 1) * 2);
constexpr short int bPSz = bPRow * bPCol;
/*The Boards */
extern array<char, bPSz>     boardP;       // boardPadded
extern array<char, bSz>      board;        // board
extern array<short int, bSz> boardIndexP;  // index of board data in boardP
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

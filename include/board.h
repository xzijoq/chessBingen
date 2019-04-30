#pragma once
#include <vector>

using namespace std;


/*The Boards*/
extern vector<short int> boardP;       // boardPadded
extern vector<short int> board;        // board
extern vector<short int> boardIndexP;  // index of board data in boardP
/*TheBoards End*/  
/*Boards Data*/
extern short int bRow; /*board Size Row*/
extern short int bCol; /*board Size Col*/
extern short int bSz;  /*board Size*/

extern short int bPRow; /*padded Board Row Count*/
extern short int bPCol; /*padded Board Col Count*/
extern short int bPSz;  /*padded Board Size*/
/*Boards Data End*/
extern int       side;
extern int       xside;
extern int       castle;
extern int       ep;
extern int       fifty;
extern int       hash;
extern int       ply;
extern int       hply;



extern short int maxJ; /*knight can jump 2square out of board*/






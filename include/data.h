#include <iostream>
#include <array>
#include <cstring>
#include <cassert>
using namespace std;
void boardsInit();
void boardDisplay();

void boardPDisplay();


void boardPFill(bool display = true);

typedef unsigned long long int u64;

#define boardSizeFen 280 

//extern char boardFen[boardSize];
extern array<char,boardSizeFen> boardFen;



extern int  corePartBoardFen;
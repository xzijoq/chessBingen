#pragma once
#include<vector>
#include <cassert>
#include <cstring>
#include <iostream>
using namespace std;
void boardsInit();
void boardDisplay(vector<short int> boarD, short int offset,bool index=false);



void boardPFill(bool display = true);

typedef unsigned long long int u64;


extern vector<char> boardFen;

extern int corePartBoardFen;
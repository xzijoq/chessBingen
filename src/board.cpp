#include <board.h>
#include <data.h>
#include <assert.h>

using namespace std;

short int maxJ = 2;
short int bRow = 8;
short int bCol = 8;
short int bSz = bRow * bCol;
short int bPRow = (bRow + maxJ * 2);
short int bPCol = (bCol + (maxJ - 1) * 2);
short int bPSz = bPRow * bPCol;



// array<short int, bSz>  board;
vector<short int> boardP(bPSz);
vector<short int> board(bSz);
vector<short int> boardIndexP(bSz);

void boardsInit()
{
   cout << boardP.size();
   for (auto i{0}; i < boardP.size(); i++) { boardP[i] = -1; }
   for (auto i{0}; i < board.size(); i++) { board[i] = i; }
}

void boardDisplay(vector<short int> boarD, short int offset, bool index)
{
   cout << "\nBoard: \n ";
   if (index == true)
   {
      for (auto i{0}; i < boarD.size(); i++)
      {
         if (i < 10)
         {
            cout << "   " << i;
         }
         else if ((i < 100 && i >= 10))
         {
            cout << "  " << i;
         }
         else
         {
            cout << " " << i;
         }
         if (((i + 1) % offset) == 0)
         {
            cout << "\n";
         }
      }
      cout << endl;
   }
   for (auto i{0}; i < boarD.size(); i++)
   {
      if (boarD[i] < 10)
      {
         if (boarD[i] >= 0)
         {
            cout << "   " << boarD[i];
         }
         else if (boarD[i] < 0 && boarD[i] > -10)
         {
            cout << "  " << boarD[i];
         }
      }
      else if (boarD[i] < 100 && boarD[i] >= 10)
      {
         cout << "  " << boarD[i];
      }
      else
      {
         cout << " " << boarD[i];
      }
      if (((i + 1) % offset) == 0)
      {
         cout << "\n ";
         // cout << "-------------------------------\n";
      }
   }
}

void boardPFill(bool display)
{
   assert(maxJ >= 0);
   int j{maxJ - 1};
   int k{1};
   int boardData{0};
   //   cout << "\n k and bPCol" << k << " " << bPCol;
   for (int i = 0; i < boardP.size(); i++)
   {
      // top and bottom padding
      int topPad = (bPCol * maxJ);
      int botPad = ((int)boardP.size() - topPad);
      //     cout << "\n" << topPad << "\n";
      if (i >= topPad && i < botPad)
      {
         k++;
         if (j > 0 || k > ((maxJ) + bCol))
         {
            boardP[i] = -1;
         }
         else
         {
            boardP[i] = board[boardData];
            boardIndexP[boardData] = i;
            boardData++;
         }
         j--;
         if ((i + 1) % bPCol == 0)
         {
            j = maxJ - 1;
            k = 1;
         }
      }
   }
}

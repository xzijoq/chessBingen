#include <board.h>
#include <data.h>
using namespace std;

array<short int, bSz>  board;
array<short int, bSzP> boardP;

void boardsInit()
{
   for (auto i{0}; i < boardP.size(); i++) { boardP[i] = -1; }
   for (auto i{0}; i < board.size(); i++) { board[i] = 2; }
}

void boardPDisplay()
{
   cout << "\nBoardPadded: \n";

   for (auto i{0}; i < boardP.size(); i++)
   {
      cout << " " << i;
      if (((i + 1) % padC) == 0)
      {
         cout << "\n";
      }
   }
   for (auto i{0}; i < boardP.size(); i++)
   {
      cout << " " << boardP[i];
      if (((i + 1) % padC) == 0)
      {
         cout << "\n";
      }
   }
}
void boardDisplay()
{
   cout << "\nBoard: \n";

   for (auto i{0}; i < board.size(); i++)
   {
      cout << " " << i;
      if (((i + 1) % bSC) == 0)
      {
         cout << "\n";
      }
   }
   for (auto i{0}; i < board.size(); i++)
   {
      cout << " " << board[i];
      if (((i + 1) % bSC) == 0)
      {
         cout << "\n";
      }
   }
}

void boardPFill(bool display)
{
   int j = maxJ-1;
   int k=(maxJ-1);
//   cout << "\n k and padc" << k << " " << padC;
   for (int i = 0; i < boardP.size(); i++)
   {

      // top and bottom padding
      int topPad = ((bSC + (maxJ)) * maxJ);
      int botPad = (boardP.size() - topPad);
   //     cout << "\n" << topPad << "\n";
      if (i >= topPad && i<botPad)
      {
         k++;
         if (j > 0 || k>((maxJ)+bSC))
         {
 
            cout << "k " << k << endl;
            boardP[i] = -1;
            j--;


		 }
         else
         {
            boardP[i] = 3;

         }
         if ((i + 1) % padC == 0)  // && i>topPad )
         {
            j = maxJ-1;
            k = (maxJ - 1);
          //   boardP[i] = 7;
         }

      }

   }
}

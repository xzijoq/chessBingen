#include <assert.h>

#include <data.h>

using namespace std;

void boardsInit()
{
   // std::cout << boardP.size();
   for (auto i{0}; i < boardP.size(); i++) { boardP[i] = '!'; }
   for (auto i{0}; i < board.size(); i++) { board[i] = 'a'; }
}

void boardDisplay(string boarS, bool index)
{
   int offset{0}, flag{0};

   size_t bS{0}, bDR{0};

   bS = board.size();
   offset = bCol;
   bDR = bS / offset;

   if (boarS == "board") { flag = 1; }
   else if (boarS == "boardP")
   {
      bS = boardP.size();
      offset = bPCol;
      bDR = bS / offset;
      flag = 2;
   }
   else if (boarS == "boardIndexP")
   {
      flag = 3;
   }
   else
   {
      flag = errorFlag_D;
   }
   auto j{bDR - 1};

   std::cout << "\nBoard: \n";
   // cout << "\n TT \n";

   /*DisplayLoop*/
   for (auto i{0}; i < bDR; i++)
   {
      if (j < 10) { cout << " "; }
      cout << " " << j;

      for (auto k{0}; k < offset; k++)
      {
         // cout << rank;
         auto pos = j * offset + k;
         if (flag == 1) { std::cout << "  " << board[pos]; }
         if (flag == 2) { std::cout << "  " << boardP[pos]; }
         if (flag == 3) { std::cout << "  " << boardIndexP[pos]; }
         if (flag == errorFlag_D) { cerr << "ERROR: WrongBoard"; }
      }
      cout << endl;
      j--;
   }
   cout << "   ";
   for (auto i{0}; i < offset; i++) { cout << "  " << (char)(i + 'a'); }
   cout << endl;

   if (index == true)
   {
      cout << "\n IndexBoard:\n";
      for (auto i{0}; i < bSz; i++)
      {
         if (i < 10) { cout << "   " << i; }
         else if ((i < 100 && i >= 10))
         {
            cout << "  " << i;
         }
         else
         {
            cout << " " << i;
         }
         if (((i + 1) % offset) == 0) { cout << "\n"; }
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
         if (j > 0 || k > ((maxJ) + bCol)) { boardP[i] = '!'; }
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

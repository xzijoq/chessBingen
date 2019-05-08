#include <assert.h>
#include <data.h>

using namespace std;

void boardsInit()
{
   // std::cout << pBoard.size();
   for (auto i{0}; i < pBoard.size(); i++) { pBoard[i] = invalidSquare; }
   for (auto i{0}; i < board.size(); i++) { board[i] = 'a'; }
}

void boardDisplay(string boarS)
{
   int    offset{0}, flag{errorFlag_D}, rank{bSz / bCol};
   char   file{'a'};
   size_t bS{0}, bDR{0};

   bS = board.size();
   offset = bCol;
   bDR = bS / offset;

   if (boarS == "board") { flag = 1; }
   if (boarS == "pBoard")
   {
      bS = pBoard.size();
      offset = pBCol;
      bDR = bS / offset;
      flag = 2;
   }
   if (boarS == "boardIndexP") { flag = 3; }

   auto j{bDR - 1};

   std::cout << "\nBoard: \n";
   // cout << "\n TT \n";

   /*DisplayLoop*/
   for (auto i{0}; i < bDR; i++)
   {
      if (flag == 2)
      {
         if ((i >= maxJ) && (rank > 0))
         {
            if ((rank < 10) && (rank >= 0)) { cout << " "; }
            cout << " " << rank;
            rank--;
         }
         else
         {
            cout << "   ";
         }
      }
      else
      {
         if ((rank < 10) && (rank >= 0)) { cout << " "; }
         cout << " " << rank;
         rank--;
      }
      for (auto k{0}; k < offset; k++)
      {
         // cout << rank;
         auto pos = j * offset + k;
         if (flag == 1) { std::cout << "  " << board[pos]; }
         if (flag == 2) { std::cout << "  " << pBoard[pos] ; }/*cout<<pos (for index)*/
         if (flag == 3) { std::cout << "  " << boardIndexP[pos]; }
         if (flag == errorFlag_D) { cerr << "ERROR: WrongBoard"; }
      }
      cout << endl;
      j--;
   }
   cout << "\n   ";
   if (flag == 2)
   {
      for (auto i{0}; i < maxJ - 1; i++) { cout << "   "; }
   }
   for (auto i{0}; i < bCol; i++) { cout << "  " << file++; }
   cout << endl;
}

void boardPFill(bool display)
{
   assert(maxJ >= 0);
   int j{maxJ - 1};
   int k{1};
   int boardData{0};
   //   cout << "\n k and pBCol" << k << " " << pBCol;
   for (int i = 0; i < pBoard.size(); i++)
   {
      // top and bottom padding
      int topPad = (pBCol * maxJ);
      int botPad = ((int)pBoard.size() - topPad);
      //     cout << "\n" << topPad << "\n";
      if (i >= topPad && i < botPad)
      {
         k++;
         if (j > 0 || k > ((maxJ) + bCol)) { pBoard[i] = invalidSquare; }
         else
         {
            pBoard[i] = board[boardData];
            boardIndexP[boardData] = i;
            boardData++;
         }
         j--;
         if ((i + 1) % pBCol == 0)
         {
            j = maxJ - 1;
            k = 1;
         }
      }
   }
}

void boardFill()
{
   int j{0};
   for (auto i : boardIndexP)
   {
      // cout << i << " ";
      board[j] = pBoard[i];
      j++;
   }
}
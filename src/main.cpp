
#include <board.h>
#include <data.h>

using namespace std;

void chessFen(string fen, bool display = false);
int  main()
{
   //  cout << "\n" << sizeof(boardP) << "\n";
   boardsInit();
   boardDisplay(boardP, bPCol);
   boardDisplay(board, bCol);

   boardPFill();
   cout << "\n NewBoard \n";
   boardDisplay(board, bCol);
   boardDisplay(boardP, bPCol);
   boardDisplay(boardIndexP, bCol);

   string t1 =
       "position fen rnbqkbnr/pppppppp/"
       "8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 "
       "1";
   string t2 =
       "position fen rnbqkbnrR/ppppppppR/"
       "8R/8R/4P3R/8R/PPPP1PPPR/RNBQKBNRR b KQkq e3 0 "
       "1";
   string ww = "8/K7/8/8/8/8/3k4/8 w  - 0 1";

  // chessFen(ww, true);

   // cout << "yoMama";

   /*
   for (int i{0}; i <= corePartBoardFen; i++)
   {
      cout << boardFen[i];
      if (boardFen[i] == '@')
      {
         cout << "\n";
      }
   }*/
   getchar();
}



#include <data.h>
#include <cinttypes>

using namespace std;

void chessFen(string fen, bool display = false);
int  main()
{
  
   string t1 =
       "position fen rnbqkbnr/pppppppp/"
       "8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 "
       "1";
   string t2 =
       "position fen rnbqkbnrR/ppppppppR/"
       "8R/8R/4P3R/8R/PPPP1PPPR/RNBQKBNRR b KQkq e3 0 "
       "1";
   string star = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
   string ww = "8/K7/8/8/8/8/3k4/8/7P w - 0 1";
   string wh = "4c15/19a/19k w - e2 1";
   boardsInit();
  // boardDisplay(board, bCol);
  // boardDisplay(boardP, bPCol);
   chessFen(wh, true);
   string aa = "12";



  
   //  cout << "\n" << sizeof(boardP) << "\n";
   boardDisplay("board");
    boardDisplay("boardP");
   //boardDisplay("boardIndexP");


   //boardPFill();
   cout << "\n NewBoard \n";
   // dire();
   //boardDisplay(board, bCol);
   //boardDisplay(boardP, bPCol);
   // boardDisplay(boardIndexP, bCol);

   // cout << "yoMama";

   

   getchar();
}

/*
MaxBoardSize 128 limited by the 128 bit interger
MaxJumperSize 4, in a 12 x12 requires a padding of
*/
#include <data.h>
#include <bitset>
#include <cinttypes>
//array<char, pBSz> pBoardC;

using namespace std;
enum wtf
{
   fg,
   gg,
   qe,
   hg
};

void chessFen(string fen, bool display = false);
int  main()
{
   boardsInit();
   string emptyBo = "12/12/8r3/12/8n3/12/12/12/12/12/12/12 w K e2 1";
   string ranF = "b1kb4/2B2Bp1/1P4P1/P1K2N2/8/1N1r1ppp/1RPp2n1/qr6 w - - 0 1";
   string ranF1 = "8/Rp2pp2/3np1Pb/2K1Q3/1P1P2P1/P1BPpr1P/5qn1/3k4 w - - 0 1";
   string fen3 = "8/8/8/3k4/8/8/8/8";
   //  chessFen(ranF);
   // boardDisplay("pBoard");
   // boardDisplay("board");
 //  cout << lol[1];
  // pBoardC = pBoard;

   for (auto i{0}; i < pBSz; i++)
   {
      // if (pBoard[i] != invalidSquare) { moveGen(i); }
      // if (pBoardC[i] == 'p' || pBoardC[i] == 'P') { moveGen(i); }
      //     if (pBoard[i] == 'r' || pBoard[i] == 'R') { moveGen(i); }
   }

   // boardDisplay("pBoard");

   getchar();
}
/*

   /*
        u64 wow{0};
   wow = dN<<9;  //| (abs(dS)<<8) | (1<<19);
        cout << bitset<64>(wow) << endl;
       


        cout << bitset<64>(wow>>9);


   int cow= (~(wow >> 9))+1;
        cout << " "<<cow;
                

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
   string wh = "4c15/19a/19k w  e2 1";
      // boardDisplay(board, bCol);
   // boardDisplay(pBoard, pBCol);
   chessFen(wh, true);
   string aa = "12";

   //  cout << "\n" << sizeof(pBoard) << "\n";
   boardDisplay("board");
   boardDisplay("pBoard");
   // boardDisplay("boardIndexP");

   // boardPFill();
   cout << "\n NewBoard \n";
   // dire();
   // boardDisplay(board, bCol);
   // boardDisplay(pBoard, pBCol);
   // boardDisplay(boardIndexP, bCol);

   // cout << "yoMama";
   */

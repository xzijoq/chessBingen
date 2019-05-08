/*
MaxBoardSize 128 limited by the 128 bit interger
MaxJumperSize 4, in a 12 x12 requires a padding of
*/
#include <data.h>
#include <bitset>
#include <cinttypes>


void chessFen(string fen, bool display = false);
int  main()
{
   boardsInit();

   string star = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
   chessFen(star);
   // genMove()


   getchar();
}
/*
DEBUG tests
     cout << pkdMove << endl;
   // These should be u64 or imba bugs will show up
   u64 fr{0x3ff}, to{0x3ff}, cap = 0xff, prom = 0xff, mVal{0x7fffff};
   // setting any one to zero should set exactly the no of size bits to zero
   pkdMove = (fr) | (to << 10) | (cap << 20) | (prom << 28) | (mVal << 40);

   // to test the value of flag & it with the fuking bit
   pkdMove |= epFg;
   pkdMove |= psFg;
   pkdMove |= csFg;
   pkdMove |= cpFg;
   pkdMove |= lastBit;

   cout << " " << frSq(pkdMove) << " " << toSq(pkdMove) << " " << capP(pkdMove)
        << " " << prmD(pkdMove) << " "
        << " " << mVal(pkdMove) << endl
        << "flag: " << (pkdMove & cpFg) << endl;

   cout << endl << bitset<64>(pkdMove);


*/

/*
Bogus:
   // boardDisplay("pBoard");
   // boardDisplay("board");
 //  cout << lol[1];
  // pBoardC = pBoard;

   for (auto i{0}; i < pBSz; i++)
   {
      // if (pBoard[i] != invalidSquare) { genMove(i); }
      // if (pBoardC[i] == 'p' || pBoardC[i] == 'P') { genMove(i); }
         //  if (pBoard[i] == 'r' || pBoard[i] == 'R') { genMove(queenM,i,2); }
      moveGena(i);
   }

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

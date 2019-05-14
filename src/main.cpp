/*
MaxBoardSize 128 limited by the 128 bit interger
MaxJumperSize 4, in a 12 x12 requires a padding of
*/
#include <data.h>
#include <bitset>
#include <chrono>
#include <cstdlib>

using namespace std::chrono;

moveList mvList;

void chessFen(string fen, bool display = false);

int main()
{
   D(cout << atIndex.size() << endl;)
   string star =
       "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq h8 123 256";
   string pawnFuck = "1ppp1p1p/2P3P1/6p1/1p2pP2/2P5/PPPPPP2/1P2P3/8 w k e6 0 1";
   string pF1 = "1ppp1p1p/2P3P1/6p1/1p2pP2/2P5/PPPPPPP1/1P2P1PP/8 w - e6 0 1";
   string MajorFuck = "5r2/1Br1N1RR/6r1/2nB1nB1/1q2N3/8/2rb2b1/4N2R w - - 0 1";
   string ff = "3Pp3/8/8/8/3r4/4R3/8/8 w - - 0 1";

   // cout << endl <<" as: "<< getPIndex('e', 6);

   boardsInit();

    string star1 = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
   string fuck = "19a10/30/22a7 w - - 0 0";
   chessFen(star);
   cout << ep;
   boardDisplay("pBoard");

   for (auto i{0}; i < 120; i++)
   {
      cout << (int)(atIndex[i])<<" ";
	  if ((i + 1) % pBCol == 0) { cout << endl;
	  }
      ;
   }

   cout << endl << ep << endl;
   for (int i{0}; i < pBSz; i++)
   {
      if (pBoard[i] == wP)
      {
         moveGena(i);
         ;
      };
   }
   for (int i{0}; i < mvList.mvCount; i++)
   {
      if ((mvList.pkdMv[i] & cpFg))
      { pBoard[toSq(mvList.pkdMv[i])] = captureDebug; }
      else
      {
         pBoard[toSq(mvList.pkdMv[i])] = moveDebug;
      }
   }
   for (int i{0}; i < mvList.mvCount; i++)
   {
      // cout << capP(mvList.pkdMv[i])<<" ";
      ;
      ;
   }

   boardDisplay("pBoard");
   cout << "wow";
}
/*
DEBUG tests
 





  for (auto i : board) { cout << displayMap[i] << " "; }
   cout << pkdMove << endl;
   // These should be u64 or imba bugs will show up
   u64 fr{0x3ff}, to{0x3ff}, prom{0x3f}, movP{0xff}, cap{0xff}, mVal{0x3ffff};
   // setting any one to zero should set exactly the no of size bits to zero
   pkdMove = (fr) | (to << 10) | (prom << 20) | (movP << 30) | (cap << 38) |
             (mVal << 46);

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
       with mkMove
      cout << endl << bitset<64>(pkdMove) << endl;
   pkdMove = mkMove(12, 13, 14, 15, 16,0,18);
   cout << endl << bitset<64>(pkdMove) << endl;
   cout << frSq(pkdMove) << " " << toSq(pkdMove) << " " << movP(pkdMove) << " "
        << capP(pkdMove) << " " << prmP(pkdMove) << " " << mVal(pkdMove) << ""
        << endl;


   pshMv(7);
   pshMv(12);
   pshMv(19);
   for (auto i{0};i<mvList.mvCount;i++)
   {
   cout << mvList.pkdMv[i] << endl;
   cout << mvList.mvCount << endl;
   }


      cout << endl
        << activeSide << " "
        << " " << castle << " " << ep <<" "<< halfMc << " "
        << " " << fullMc<< endl;
   cout << bitset<32>(castle);
*/

/*
Bogus:
   // boardDisplay("pBoard");
   // boardDisplay("board");
 //  cout << lol[1];
  // pBoardC = pBoard;

   for (auto i{0}; i < pBSz; i++)
   {
      // if (pBoard[i] != invalidPiece) { genMove(i); }
      // if (pBoardC[i] == 'p' || pBoardC[i] == 'P') { genMove(i); }
         //  if (pBoard[i] == 'r' || pBoard[i] == 'R') { genMove(queenM,i,2); }
      moveGena(i);
   }
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
//
//


#include <bitset>
#include "data.h"

u64 pkdMove{0};
s64 mvTo{0};
u64 tMv{0};

u64 wPawnL[50];
u64 wRookL[50];
u64 wQueenL[50];
u64 wBishopL[50];
u64 wKnightL[50];
u64 wKingL[50];
u64 bPawnL[50];
u64 bRookL[50];
u64 bQueenL[50];
u64 bBishopL[50];
u64 bKnightL[50];
u64 bKingL[50];
u64 noPieceL[2];
u64 invalidPieceList[2];

const map<u64, u64 *> ToLi{

    {wP, wPawnL},
    {bP, bPawnL},
    {wN, wKnightL},
    {bN, bKnightL},
    {wB, wBishopL},
    {bB, bBishopL},
    {wR, wRookL},
    {bR, bRookL},
    {wQ, wQueenL},
    {bQ, bQueenL},
    {wK, wKingL},
    {bK, bKingL},
    {invalidPiece, noPieceL},
    {noPiece, invalidPieceList}

};

array<u64, 20> a;

void fillPieceList()
{
   ToLi.at(pBoard[12])[0] = 12;
   // cout<<
  // for (int o{0}; o < pBSz; o++) { ToLi.at(pBoard[o])[0] = 0; }
   for (int i{0}; i < pBSz; i++)
   {
      if (pBoard[i] != invalidPiece && pBoard[i] != noPiece)
      {

         ToLi.at(pBoard[i])[0]++;
         u64 countR = ToLi.at(pBoard[i])[0];
		 ToLi.at(pBoard[i])[countR] = i;
         atIndex[i] = countR;
         cout << countR << " ";
      }

      //<< pBoard[i] << " ";
      // ToLi.at(pBoard[i])[ToLi.at(pBoard[i])[0]] = i;
      // atIndex[i] = ToLi.at(pBoard[i])[0];
      /*
          switch (pBoard[i])
      {
         case bP:
         {
            bPawnL[0]++;
            bPawnL[bPawnL[0]] = i;   // append at end
            atIndex[i] = bPawnL[0];  // append the IndexBoard
            break;
         }
      }
          */
   }
}

void fillPieceLista()
{
   for (int i{0}; i < pBSz; i++)
   {
      switch (pBoard[i])
      {
         case bP:
         {
            bPawnL[0]++;
            bPawnL[bPawnL[0]] = i;   // append at end
            atIndex[i] = bPawnL[0];  // append the IndexBoard
            break;
         }
         case wP:
         {
            wPawnL[0]++;
            wPawnL[wPawnL[0]] = i;
            atIndex[i] = wPawnL[0];
            break;
         }
         case bR:
         {
            bRookL[0]++;
            bRookL[bRookL[0]] = i;
            atIndex[i] = bRookL[0];
            break;
         }
         case wR:
         {
            wRookL[0]++;
            wRookL[wRookL[0]] = i;
            atIndex[i] = wRookL[0];
            break;
         }
         case bB:
         {
            bBishopL[0]++;
            bBishopL[bBishopL[0]] = i;
            atIndex[i] = bBishopL[0];
            break;
         }
         case wB:
         {
            wBishopL[0]++;
            wBishopL[wBishopL[0]] = i;
            atIndex[i] = wBishopL[0];
            break;
         }
         case bN:
         {
            bKnightL[0]++;
            bKnightL[bKnightL[0]] = i;
            atIndex[i] = bKnightL[0];
            break;
         }
         case wN:
         {
            wKnightL[0]++;
            wKnightL[wKnightL[0]] = i;
            atIndex[i] = wKnightL[0];
            break;
         }
         case bQ:
         {
            bQueenL[0]++;
            bQueenL[bQueenL[0]] = i;
            atIndex[i] = bQueenL[0];
            break;
         }
         case wQ:
         {
            wQueenL[0]++;
            wQueenL[wQueenL[0]] = i;
            atIndex[i] = wQueenL[0];
            break;
         }
         case bK:
         {
            bKingL[0]++;
            bKingL[bKingL[0]] = i;
            atIndex[i] = bKingL[0];
            break;
         }
         case wK:
         {
            wKingL[0]++;
            wKingL[wKingL[0]] = i;
            atIndex[i] = wKingL[0];
            break;
         }
         case noPiece:
         {  // cout << "\nWARNING: GenEmptySqMv\n";
            break;
         }
         case invalidPiece:
         {
            //  cerr << "\nERROR: GenINVALIDSqMv\n";
            break;
         }

         default:
         {
            // cout << "\nBy Default Fuck Your Self";
         }
      }
   }
}

void addQuiteMv() {}
void inline moveGena(int frm, u64 piece)
{ /*if no piece is specified it'll search through the board to find it*/

   if (piece == noPiece) { piece = pBoard[frm]; }

   switch (piece)
   {
      case bP:
      {
         pawnMGen(frm, black);
         break;
      }
      case wP:
      {
         pawnMGen(frm, white);
         break;
      }
      case bR:
      {
         genMove(rookM, frm, black);
         break;
      }
      case wR:
      {
         genMove(rookM, frm, white);
         break;
      }
      case bB:
      {
         genMove(bishopM, frm, black);
         break;
      }
      case wB:
      {
         genMove(bishopM, frm, white);
         break;
      }
      case bN:
      {
         genMove(knightM, frm, black);
         break;
      }
      case wN:
      {
         genMove(knightM, frm, white);
         break;
      }
      case bQ:
      {
         genMove(queenM, frm, black);
         break;
      }
      case wQ:
      {
         genMove(queenM, frm, white);
         break;
      }
      case bK:
      {
         genMove(kingM, frm, black);
         break;
      }
      case wK:
      {
         genMove(kingM, frm, white);
         break;
      }
      case noPiece:
      {  // cout << "\nWARNING: GenEmptySqMv\n";
         break;
      }
      case invalidPiece:
      {
         cerr << "\nERROR: GenINVALIDSqMv\n";
         break;
      }

      default:
      {
         // cout << "\nBy Default Fuck Your Self";
      }
   }
}

void genMove(s64 *pieceM, int frm, int color)
{
   if (color != white && color != black) { cerr << "\nERROR:ColorMovegen\n"; }
   int xcolor{99};
   (color == white) ? xcolor = black : xcolor = white;

   if (pieceM[0] == jumperP)
   {
      for (auto j{1}; pieceM[j] != 0; j++)
      {
         mvTo = frm + pieceM[j];
         if (pBoard[mvTo] == invalidPiece) { continue; }
         if ((pBoard[mvTo] != noPiece && pBoard[mvTo] != moveDebug))
         {
            if ((pBoard[mvTo] & color) == xcolor)
            {
               // pBoard[mvTo] = captureDebug;

               pshMv(Mv(frm, mvTo, cpFg, nP, pBoard[frm], pBoard[mvTo], 50000));
            }
         }
         else
         {
            pshMv(Mv(frm, mvTo, 0, nP, pBoard[frm], pBoard[mvTo], 0));

            // pBoard[mvTo] = moveDebug;
         }
      }
   }
   else if (pieceM[0] == sliderP)
   {
      for (auto j{1}; pieceM[j] != 0; j++)
      {
         for (s64 i{1}; i < 256; i++)
         {
            mvTo = frm + (pieceM[j] * i);

            if (pBoard[mvTo] == invalidPiece) { break; }
            if ((pBoard[mvTo] != noPiece && pBoard[mvTo] != moveDebug))
            {
               if ((pBoard[mvTo] & white) == xcolor)
               {
                  // pBoard[mvTo] = captureDebug;
                  pshMv(Mv(frm, mvTo, cpFg, nP, pBoard[frm], pBoard[mvTo],
                           50000));
               }
               break;
            }
            else
            {
               // pBoard[mvTo] = moveDebug;
               pshMv(Mv(frm, mvTo, 0, nP, pBoard[frm], pBoard[mvTo], 0));
            }
         }
      }
   }
   else
   {
      cerr << "ERROR:UNDEFINED PIECE TYPE genMove";
   }
}

// for compound pieces
void genMove(s64 **pieceM, int frm, int color)
{
   if ((s64)(pieceM[0]) == compoundP)
   {
      for (auto j{1}; pieceM[j] != nullptr; j++)
      {
         genMove(pieceM[j], frm, color);
         ;
      }
   }
   else
   {
      cerr << "ERROR:QueenMoveGen";
   }
}

void inline pawnMGen(int frm, int color)
{ /*clear ep at eatch moveGen*/
   auto cRank = getRank(frm);

   s64 mC{0}, pawn;
   int xcolor{99};

   bool canPromote{false}, startPos{false};
   if (cRank > maxJ + bRow) { cerr << "ERROR: WHere exactly is your Pawn"; }

   if (color == white)
   {
      xcolor = black;

      pawn = wP;
      if (cRank == bRow - 1) { canPromote = true; }
      if (cRank == 2) { startPos = true; }
   }
   else if (color == black)
   {
      xcolor = white;
      pawn = bP;
      if (cRank == 2) { canPromote = true; }
      if (cRank == bRow - 1) { startPos = true; }
   }
   else
   {
      D(cerr << "ERROR:PawnsAREpplOFcolor";)
   }
   for (auto j{0}; wPawnM[j] != 0; j++)
   {
      if (color == white) { mC = wPawnM[j]; }
      if (color == black) { mC = bPawnM[j]; }
      mvTo = frm + mC;
      /*passiveMove*/
      if (j == 0)
      {
         if (pBoard[mvTo] == invalidPiece)
         {
            cerr << "ERROR:Pawn" << mvTo;
            continue;
         }
         if (pBoard[mvTo] != noPiece && pBoard[mvTo] != moveDebug)
         {
            continue;
            ;
         }
         else /*moveTo Square Is Empty*/
         {
            if (canPromote == 1)
            {
               pshMv(Mv(frm, mvTo, 0, queen | color, pBoard[frm], 0, 0));
               pshMv(Mv(frm, mvTo, 0, rook | color, pBoard[frm], 0, 0));
               pshMv(Mv(frm, mvTo, 0, knight | color, pBoard[frm], 0, 0));
               pshMv(Mv(frm, mvTo, 0, bishop | color, pBoard[frm], 0, 0));

               // pBoard[mvTo] = moveDebug;
            }
            else  // not  a promotion move
            {
               if (startPos == true)
               {
                  if (pBoard[mvTo + mC] == noPiece)
                  {
                     // pBoard[mvTo + mC] = moveDebug;
                     pshMv(Mv(frm, mvTo + mC, psFg | epFg, nP, pBoard[frm], 0,
                              0));

                     // ep = mvTo;
                     // gen double move
                     // set enPasant
                  }
                  else  // the double move square is not empty
                  {
                     pshMv(Mv(frm, mvTo, noFg, nP, pBoard[frm], 0, 0));

                     // pBoard[mvTo] = moveDebug;
                  }
               }
               else  // Not a start Position
               {
                  pshMv(Mv(frm, mvTo, noFg, nP, pBoard[frm], 0, 0));
               }
            }
         }
      }
      /* CaptureMove*/
      if (j > 0)
      {
         if (pBoard[mvTo] == invalidPiece) { continue; }

         // cout  << " "<<ep<<" ";
         if (ep == mvTo)
         {
            pshMv(Mv(frm, mvTo, cpFg | epFg, nP, pBoard[frm], pBoard[mvTo - mC],
                     5000));
            // genEp move
            pBoard[mvTo + mC] = captureDebug;
         }
         if ((pBoard[mvTo] != noPiece && pBoard[mvTo] != moveDebug) &&
             ((pBoard[mvTo] & white) == xcolor))
         {
            if (canPromote == 1)
            {
               pshMv(Mv(frm, mvTo, cpFg, queen | color, pBoard[frm],
                        pBoard[mvTo], 5000));
               pshMv(Mv(frm, mvTo, cpFg, rook | color, pBoard[frm],
                        pBoard[mvTo], 5000));
               pshMv(Mv(frm, mvTo, cpFg, knight | color, pBoard[frm],
                        pBoard[mvTo], 5000));
               pshMv(Mv(frm, mvTo, cpFg, bishop | color, pBoard[frm],
                        pBoard[mvTo], 5000));

               pBoard[mvTo] = captureDebug;
               // pBoard[mvTo] = '.';
            }
            else /*not a promotion capture*/
            {
               pshMv(Mv(frm, mvTo, cpFg, nP, pBoard[frm], pBoard[mvTo], 5000));
               // pBoard[mvTo] = captureDebug;
            }
         }
      }
   }
}
void makeMove(u64 pMove)
{
   u64 frmSq = frSq(pMove);
   u64 toSq = toSq(pMove);
   u64 movingPiece;
   u64 capturedPiece;

   switch (movingPiece)
   {
      case wP:
      {
         // generate capture
         if (pMove & cpFg)
         {
            ;
            ;
         }

         ;
      }
   }
}
void genCapture(u64 piece) {}

void makeMoveWp() {}

/*


                                /*
               if (startPos == true)
               {
                             //pawnStartFlag?
                  pshMv(
                      Mv(frm, mvTo, (cpFg | psFg), nP, pBoard[frm],
   pBoard[mvTo], 5000));
                             // pBoard[mvTo] = captureDebug;
                           }
               else //Not a starting capture
               {
                 
                  pshMv(Mv(frm, mvTo, cpFg, nP, pBoard[frm],
                           pBoard[mvTo], 5000));
                  // pBoard[mvTo] = captureDebug;
               }
                           */
// pshMv(Mv(frm, mvTo, cpFg, nP, pBoard[frm], pBoard[mvTo], 5000));

/*
void inline wPawnMGen(int frm)
{
   int cRank = (frm / pBCol) - maxJ + 1, canPromote{0};
   if (cRank > maxJ + bRow) { cerr << "ERROR: WHere exactly is your PawnW"; }
   int mvTo{'{'};
   if (cRank == bRow - 1) { canPromote = 1; }
   for (auto j{0}; j < wPawnM.size(); j++)
   {
      mvTo = frm + wPawnM[j];

      if (j == 0)
      {
         if (pBoard[mvTo] == invalidPiece)
         {
            cerr << "ERROR: WHere exactly is your PawnII";
            continue;
         }
         if (pBoard[mvTo] != noPiece && pBoard[mvTo] != moveDebug)
         { continue; }
         else
         {
            if (canPromote == 1) { pBoard[mvTo] = '{'; }
            else
            {
               pBoard[mvTo] = moveDebug;
            }
         }
      }
      if (j > 0)
      {
         if (pBoard[mvTo] == invalidPiece) { continue; }
         if (pBoard[mvTo] != noPiece && pBoard[mvTo] != moveDebug)
         {
            if (canPromote == 1) { pBoard[mvTo] = '}'; }
            else
            {
               pBoard[mvTo] = captureDebug;
            }
         }
      }
   }
}
void inline bPawnMGen(int frm)
{
   int cRank = (frm / pBCol) - maxJ + 1, canPromote{0};
   //cout<<" cRank: " << cRank<<" frm/COl: "<<(int)(frm/pBCol)<<"EE";
   if (cRank > maxJ + bRow)
   {
      cerr << "ERROR: WHere exactly is your Pawn " << cRank << " " << frm <<
" "
           << pBCol;
      pBoard[frm] = '?';
   }
   int mvTo{'{'};
   if (cRank == 2) { canPromote = 1; }
   for (auto j{0}; j < wPawnM.size(); j++)
   {
      mvTo = frm + bPawnM[j];

      if (j == 0)
      {
         if (pBoard[mvTo] == invalidPiece)
         {
            cerr << "ERROR: WHere exactly is your PawnII";
            continue;
         }
         if (pBoard[mvTo] != noPiece && pBoard[mvTo] != moveDebug)
         { continue; }
         else
         {
            if (canPromote == 1) { pBoard[mvTo] = '{'; }
            else
            {
               pBoard[mvTo] = moveDebug;
            }
         }
      }
      if (j > 0)
      {
         if (pBoard[mvTo] == invalidPiece) { continue; }
         if (pBoard[mvTo] != noPiece && pBoard[mvTo] != moveDebug)
         {
            if (canPromote == 1) { pBoard[mvTo] = '}'; }
            else
            {
               pBoard[mvTo] = captureDebug;
            }
         }
      }
   }
}
*/
/*
void inline knightMGen(int frm)
{
   //int mvTo{'{'};
   for (auto j{0}; j < knightM.size(); j++)
   {
      mvTo = frm + knightM[j];
      if (pBoard[mvTo] == invalidPiece) { continue; }
      if (pBoard[mvTo] != noPiece && pBoard[mvTo] != moveDebug)
      { pBoard[mvTo] = captureDebug; }
      else
      {
         pBoard[mvTo] = moveDebug;
      }
   }
}
void inline kingMGen(int frm)
{
  // int mvTo{'{'};
   for (auto j{0}; j < kingM.size(); j++)
   {
      mvTo = frm + kingM[j];
      if (pBoard[mvTo] == invalidPiece) { continue; }
      if (pBoard[mvTo] != noPiece && pBoard[mvTo] != moveDebug)
      { pBoard[mvTo] = captureDebug; }
      else
      {
         pBoard[mvTo] = moveDebug;
      }
   }
}
void inline rookMGen(int frm)
{
   //int mvTo{0};
   for (auto j{0}; j < rookM.size(); j++)
   {
      for (auto i{1}; i < 256; i++)
      {
         mvTo = frm + (rookM[j] * i);

         if (pBoard[mvTo] == invalidPiece) { break; }
         if (pBoard[mvTo] != noPiece)
         {
            if (pBoard[mvTo] == moveDebug) { continue; }
            pBoard[mvTo] = captureDebug;
             break;
         }
         else
         {
            pBoard[mvTo] = moveDebug;
         }
      }
   }
}
void inline bishopMGen(int frm)
{
  // int mvTo{0};
   for (auto j{0}; j < bishopM.size(); j++)
   {
      for (auto i{1}; i < 256; i++)
      {
         mvTo = frm + (bishopM[j] * i);
         if (pBoard[mvTo] == invalidPiece) { break; }
         if (pBoard[mvTo] != noPiece)
         {
            if (pBoard[mvTo] == moveDebug) { continue; }
            pBoard[mvTo] = captureDebug;
             break;
         }
         else
         {
            pBoard[mvTo] = moveDebug;
         }
      }
   }
}
*/

void dire()
{
   std::cout << " dN: " << dN << " dS: " << dS << " dE: " << dE << " dW " << dW
             << " dNE: " << dNE << " dNW: " << dNW << " dSE: " << dSE
             << " dSW: " << dSW << endl;
   //<< " " << dS << " " << ;

   // cout << fc;
}

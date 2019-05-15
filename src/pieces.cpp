
/*

We can define the max numbers of piecs as only pawns promote, mostly
to queen so 2 array starting with pawn then queen, and no major
readjustment is required, and the engine will only promote to queen
so in the very rare case when pawn promote to anything other than
queen we can readjust the array 1 down from the last piece,
the number of pieces at the start define the index

pawnCount , queen count, knight count ...
to scan for knights we start scanning from pawnCount+queenCount
up to pC+qC+kC

*/

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

array<int, 23> yoqwe;

unordered_map<u64, array<int, 23> > ji{

    {wP, yoqwe}};

const unordered_map<u64, u64 *> listOf{

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

// template <typename T>
// constexpr void old_function(/* args */);

// template <typename T>
// constexpr auto alias_to_old = old_function<T>;

array<u64, 20> a;

void fillPieceList()
{
   listOf.at(pieceAt[12])[0] = 12;
   // cout<<
   for (int o{0}; o < pBSz; o++) { listOf.at(pieceAt[o])[0] = 0; }
   for (int i{0}; i < pBSz; i++)
   {
      if (pieceAt[i] != invalidPiece && pieceAt[i] != noPiece)
      {
         listOf.at(pieceAt[i])[0]++;
         u64 countR = listOf.at(pieceAt[i])[0];
         listOf.at(pieceAt[i])[countR] = i;
         indexAt[i] = countR;
         // cout << countR << " ";
      }


   }
}
void fillPieceLista()
{
   for (int i{0}; i < pBSz; i++)
   {
      switch (pieceAt[i])
      {
         case bP:
         {
            bPawnL[0]++;
            bPawnL[bPawnL[0]] = i;   // append at end
            indexAt[i] = bPawnL[0];  // append the IndexBoard
            break;
         }
         case wP:
         {
            wPawnL[0]++;
            wPawnL[wPawnL[0]] = i;
            indexAt[i] = wPawnL[0];
            break;
         }
         case bR:
         {
            bRookL[0]++;
            bRookL[bRookL[0]] = i;
            indexAt[i] = bRookL[0];
            break;
         }
         case wR:
         {
            wRookL[0]++;
            wRookL[wRookL[0]] = i;
            indexAt[i] = wRookL[0];
            break;
         }
         case bB:
         {
            bBishopL[0]++;
            bBishopL[bBishopL[0]] = i;
            indexAt[i] = bBishopL[0];
            break;
         }
         case wB:
         {
            wBishopL[0]++;
            wBishopL[wBishopL[0]] = i;
            indexAt[i] = wBishopL[0];
            break;
         }
         case bN:
         {
            bKnightL[0]++;
            bKnightL[bKnightL[0]] = i;
            indexAt[i] = bKnightL[0];
            break;
         }
         case wN:
         {
            wKnightL[0]++;
            wKnightL[wKnightL[0]] = i;
            indexAt[i] = wKnightL[0];
            break;
         }
         case bQ:
         {
            bQueenL[0]++;
            bQueenL[bQueenL[0]] = i;
            indexAt[i] = bQueenL[0];
            break;
         }
         case wQ:
         {
            wQueenL[0]++;
            wQueenL[wQueenL[0]] = i;
            indexAt[i] = wQueenL[0];
            break;
         }
         case bK:
         {
            bKingL[0]++;
            bKingL[bKingL[0]] = i;
            indexAt[i] = bKingL[0];
            break;
         }
         case wK:
         {
            wKingL[0]++;
            wKingL[wKingL[0]] = i;
            indexAt[i] = wKingL[0];
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

   if (piece == noPiece) { piece = pieceAt[frm]; }

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
         if (pieceAt[mvTo] == invalidPiece) { continue; }
         if ((pieceAt[mvTo] != noPiece && pieceAt[mvTo] != moveDebug))
         {
            if ((pieceAt[mvTo] & color) == xcolor)
            {
               // pieceAt[mvTo] = captureDebug;

               pshMv(
                   Mv(frm, mvTo, cpFg, nP, pieceAt[frm], pieceAt[mvTo], 50000));
            }
         }
         else
         {
            pshMv(Mv(frm, mvTo, 0, nP, pieceAt[frm], pieceAt[mvTo], 0));

            // pieceAt[mvTo] = moveDebug;
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

            if (pieceAt[mvTo] == invalidPiece) { break; }
            if ((pieceAt[mvTo] != noPiece && pieceAt[mvTo] != moveDebug))
            {
               if ((pieceAt[mvTo] & white) == xcolor)
               {
                  // pieceAt[mvTo] = captureDebug;
                  pshMv(Mv(frm, mvTo, cpFg, nP, pieceAt[frm], pieceAt[mvTo],
                           50000));
               }
               break;
            }
            else
            {
               // pieceAt[mvTo] = moveDebug;
               pshMv(Mv(frm, mvTo, 0, nP, pieceAt[frm], pieceAt[mvTo], 0));
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
         if (pieceAt[mvTo] == invalidPiece)
         {
            cerr << "ERROR:Pawn" << mvTo;
            continue;
         }
         if (pieceAt[mvTo] != noPiece && pieceAt[mvTo] != moveDebug)
         {
            continue;
            ;
         }
         else /*moveTo Square Is Empty*/
         {
            if (canPromote == 1)
            {
               pshMv(Mv(frm, mvTo, 0, queen | color, pieceAt[frm], 0, 0));
               pshMv(Mv(frm, mvTo, 0, rook | color, pieceAt[frm], 0, 0));
               pshMv(Mv(frm, mvTo, 0, knight | color, pieceAt[frm], 0, 0));
               pshMv(Mv(frm, mvTo, 0, bishop | color, pieceAt[frm], 0, 0));

               // pieceAt[mvTo] = moveDebug;
            }
            else  // not  a promotion move
            {
               if (startPos == true)
               {
                  if (pieceAt[mvTo + mC] == noPiece)
                  {
                     // pieceAt[mvTo + mC] = moveDebug;
                     pshMv(Mv(frm, mvTo + mC, psFg | epFg, nP, pieceAt[frm], 0,
                              0));

                     // ep = mvTo;
                     // gen double move
                     // set enPasant
                  }
                  else  // the double move square is not empty
                  {
                     pshMv(Mv(frm, mvTo, noFg, nP, pieceAt[frm], 0, 0));

                     // pieceAt[mvTo] = moveDebug;
                  }
               }
               else  // Not a start Position
               {
                  pshMv(Mv(frm, mvTo, noFg, nP, pieceAt[frm], 0, 0));
               }
            }
         }
      }
      /* CaptureMove*/
      if (j > 0)
      {
         if (pieceAt[mvTo] == invalidPiece) { continue; }

         // cout  << " "<<ep<<" ";
         if (ep == mvTo)
         {
            pshMv(Mv(frm, mvTo, cpFg | epFg, nP, pieceAt[frm],
                     pieceAt[mvTo - mC], 5000));
            // genEp move
            pieceAt[mvTo + mC] = captureDebug;
         }
         if ((pieceAt[mvTo] != noPiece && pieceAt[mvTo] != moveDebug) &&
             ((pieceAt[mvTo] & white) == xcolor))
         {
            if (canPromote == 1)
            {
               pshMv(Mv(frm, mvTo, cpFg, queen | color, pieceAt[frm],
                        pieceAt[mvTo], 5000));
               pshMv(Mv(frm, mvTo, cpFg, rook | color, pieceAt[frm],
                        pieceAt[mvTo], 5000));
               pshMv(Mv(frm, mvTo, cpFg, knight | color, pieceAt[frm],
                        pieceAt[mvTo], 5000));
               pshMv(Mv(frm, mvTo, cpFg, bishop | color, pieceAt[frm],
                        pieceAt[mvTo], 5000));

               pieceAt[mvTo] = captureDebug;
               // pieceAt[mvTo] = '.';
            }
            else /*not a promotion capture*/
            {
               pshMv(
                   Mv(frm, mvTo, cpFg, nP, pieceAt[frm], pieceAt[mvTo], 5000));
               // pieceAt[mvTo] = captureDebug;
            }
         }
      }
   }
}
void makeMove(u64 pMove)
{// still need to check for checks and pins
	//what happens to move Value
   u64 frmSq = frSq(pMove);
   u64 toSq = toSq(pMove);


   if (pMove & csFg)
   {
      // generate castelingMove
   }
   if (pMove & cpFg)
   {
      auto capSq = toSq;
      if (pMove & epFg)
      {
         //capSq dependsOn color of pawn 
         
      }
      // capturePiece
      u64 lastPieceSq = listOf.at(pieceAt[capSq])[listOf.at(pieceAt[capSq])[0]];      

	
      listOf.at(pieceAt[capSq])[indexAt[capSq]] =
          lastPieceSq;                       // lastPieceInPlaceOfCapture
      indexAt[lastPieceSq] = indexAt[capSq];  // New index of the last piece
      listOf.at(pieceAt[capSq])[0]--;         // count --
      if (listOf.at(pieceAt[capSq])[0] < 0) { cout << "NegetivePieceCount"; }
      // capturedPiece
   }
   cout << endl << "PieceList: ";
  

   // pieceMovement

   listOf.at(pieceAt[frmSq])[indexAt[frmSq]] = toSq;
   indexAt[toSq] = indexAt[frmSq];  // toSq now contains the index of
   indexAt[frmSq] = invalidIndex;
   pieceAt[toSq] = pieceAt[frmSq];
   pieceAt[frmSq] = noPiece;
   // endPieceMovement
}
void unMakeMove(u64 pMove)
{  // still need to check for checks and pins
   // what happens to move Value
   u64 toSq = frSq(pMove);
   u64 frmSq = toSq(pMove);
   u64 capP = capP(pMove);


   if (pMove & csFg)
   {
      // generate castelingMove
   }
   // pieceMovement

   listOf.at(pieceAt[frmSq])[indexAt[frmSq]] = toSq;
   indexAt[toSq] = indexAt[frmSq];  // toSq now contains the index of
   indexAt[frmSq] = invalidIndex;
   pieceAt[toSq] = pieceAt[frmSq];
   pieceAt[frmSq] = capP;
   // endPieceMovement
   if (pMove & cpFg)
   {
      auto capSq = toSq;
      if (pMove & epFg)
      {
         // capSq dependsOn color of pawn
      }
      // capturePiece
      listOf.at(capP)[0]++;  // count ++
      listOf.at(capP)[listOf.at(capP)[0]]=frmSq;
      indexAt[frmSq] = listOf.at(capP)[0];      
      if (listOf.at(pieceAt[capSq])[0] < 0) { cout << "NegetivePieceCount"; }
      // capturedPiece
   }
}
void genaCapture(u64 piece) {}

void makeMoveWp() {}

void dire()
{
   std::cout << " dN: " << dN << " dS: " << dS << " dE: " << dE << " dW " << dW
             << " dNE: " << dNE << " dNW: " << dNW << " dSE: " << dSE
             << " dSW: " << dSW << endl;
   //<< " " << dS << " " << ;

   // cout << fc;
}

/*DEBUG   MakeMove

   //
   index=indexOfpieceat[to]
   sq=bK_list[bKcount];
   bk_List[index]=sq
   bKcount--;
   bPiece--;
   //
#define wow(x) (char)(getFile(x) + 'a' - 1) << getRank(x)
   cout << endl << "PieceList: ";
   for (int i{1}; i < listOf.at(pieceAt[toSq])[0]+1; i++)
   { cout << wow(listOf.at(pieceAt[toSq])[i]) << " "; }
   cout << "endPlist" << endl;

   cout << " frmSq: " << wow(frmSq);
   cout << " toSq: " << (char)(getFile(toSq) + 'a' - 1) << getRank(toSq);
   cout << endl
        << " lastSq: " << (char)(getFile(lastPieceSq) + 'a' - 1)
        << getRank(lastPieceSq);

   cout << endl;
   cout << " ioTq " << ioTq;
   cout << " ioLPQ " << indexAt[lastPieceSq];
   //#define countOf(x) listOf.at(x)[0]

         //PutATEnd
         cout << endl << "PieceList: ";
      for (int i{1}; i < listOf.at(pieceAt[toSq])[0] + 1; i++)
      { cout << wow(listOf.at(pieceAt[toSq])[i]) << " "; }
      cout << "endPlist" << endl;
      */

/*


                                /*
               if (startPos == true)
               {
                             //pawnStartFlag?
                  pshMv(
                      Mv(frm, mvTo, (cpFg | psFg), nP, pieceAt[frm],
   pieceAt[mvTo], 5000));
                             // pieceAt[mvTo] = captureDebug;
                           }
               else //Not a starting capture
               {
                 
                  pshMv(Mv(frm, mvTo, cpFg, nP, pieceAt[frm],
                           pieceAt[mvTo], 5000));
                  // pieceAt[mvTo] = captureDebug;
               }
                           */
// pshMv(Mv(frm, mvTo, cpFg, nP, pieceAt[frm], pieceAt[mvTo], 5000));

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
         if (pieceAt[mvTo] == invalidPiece)
         {
            cerr << "ERROR: WHere exactly is your PawnII";
            continue;
         }
         if (pieceAt[mvTo] != noPiece && pieceAt[mvTo] != moveDebug)
         { continue; }
         else
         {
            if (canPromote == 1) { pieceAt[mvTo] = '{'; }
            else
            {
               pieceAt[mvTo] = moveDebug;
            }
         }
      }
      if (j > 0)
      {
         if (pieceAt[mvTo] == invalidPiece) { continue; }
         if (pieceAt[mvTo] != noPiece && pieceAt[mvTo] != moveDebug)
         {
            if (canPromote == 1) { pieceAt[mvTo] = '}'; }
            else
            {
               pieceAt[mvTo] = captureDebug;
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
      pieceAt[frm] = '?';
   }
   int mvTo{'{'};
   if (cRank == 2) { canPromote = 1; }
   for (auto j{0}; j < wPawnM.size(); j++)
   {
      mvTo = frm + bPawnM[j];

      if (j == 0)
      {
         if (pieceAt[mvTo] == invalidPiece)
         {
            cerr << "ERROR: WHere exactly is your PawnII";
            continue;
         }
         if (pieceAt[mvTo] != noPiece && pieceAt[mvTo] != moveDebug)
         { continue; }
         else
         {
            if (canPromote == 1) { pieceAt[mvTo] = '{'; }
            else
            {
               pieceAt[mvTo] = moveDebug;
            }
         }
      }
      if (j > 0)
      {
         if (pieceAt[mvTo] == invalidPiece) { continue; }
         if (pieceAt[mvTo] != noPiece && pieceAt[mvTo] != moveDebug)
         {
            if (canPromote == 1) { pieceAt[mvTo] = '}'; }
            else
            {
               pieceAt[mvTo] = captureDebug;
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
      if (pieceAt[mvTo] == invalidPiece) { continue; }
      if (pieceAt[mvTo] != noPiece && pieceAt[mvTo] != moveDebug)
      { pieceAt[mvTo] = captureDebug; }
      else
      {
         pieceAt[mvTo] = moveDebug;
      }
   }
}
void inline kingMGen(int frm)
{
  // int mvTo{'{'};
   for (auto j{0}; j < kingM.size(); j++)
   {
      mvTo = frm + kingM[j];
      if (pieceAt[mvTo] == invalidPiece) { continue; }
      if (pieceAt[mvTo] != noPiece && pieceAt[mvTo] != moveDebug)
      { pieceAt[mvTo] = captureDebug; }
      else
      {
         pieceAt[mvTo] = moveDebug;
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

         if (pieceAt[mvTo] == invalidPiece) { break; }
         if (pieceAt[mvTo] != noPiece)
         {
            if (pieceAt[mvTo] == moveDebug) { continue; }
            pieceAt[mvTo] = captureDebug;
             break;
         }
         else
         {
            pieceAt[mvTo] = moveDebug;
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
         if (pieceAt[mvTo] == invalidPiece) { break; }
         if (pieceAt[mvTo] != noPiece)
         {
            if (pieceAt[mvTo] == moveDebug) { continue; }
            pieceAt[mvTo] = captureDebug;
             break;
         }
         else
         {
            pieceAt[mvTo] = moveDebug;
         }
      }
   }
}
*/

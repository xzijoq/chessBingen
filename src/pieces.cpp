#include "data.h"


u64 pkdMove{0};
class piece
{
   // bool
};

array<u64, 120> knightMove{};
s64             moveT{0};
void genMove(s64 *pieceM, int pos, int color)
{
   if (color != white && color != black) { cerr << "\nERROR:ColorMovegen\n"; }
   int xcolor{99};
   (color == white) ? xcolor = black : xcolor = white;

   if (pieceM[0] == jumperP)
   {
      for (auto j{1}; pieceM[j] != 0; j++)
      {
         moveT = pos + pieceM[j];
         if (pBoard[moveT] == invalidSquare) { continue; }
         if (pBoard[moveT] != emptySquare && pBoard[moveT] != moveDebug)
         {
            // pBoard[moveT] = captureDebug;
            ;
         }
         else
         {
            pBoard[moveT] = moveDebug;
         }
      }
   }
   else if (pieceM[0] == sliderP)
   {
      for (auto j{1}; pieceM[j] != 0; j++)
      {
         for (s64 i{1}; i < 256; i++)
         {
            moveT = pos + (pieceM[j] * i);

            if (pBoard[moveT] == invalidSquare) { break; }
            if (pBoard[moveT] != emptySquare && pBoard[moveT] != moveDebug)
            {
            
               // pBoard[moveT] = captureDebug;
               break;
            }
            else
            {
               pBoard[moveT] = moveDebug;
            }
         }
      }
   }
   else
   {
      cerr << "ERROR:UNDEFINED PIECE TYPE genMove";
   }
}

//for compound pieces
void genMove(s64 **pieceM, int pos, int color)
{
   if ((s64)(pieceM[0]) == compoundP)
   {
      for (auto j{1}; pieceM[j] != nullptr; j++)
      {
         genMove(pieceM[j], pos, color);
         ;
      }
   }
   else
   {
      cerr << "ERROR:QueenMoveGen";
   }
}

void inline moveGena(int pos, char piece)
{ /*if no piece is specified it'll search through the board to find it*/
   // if (pos == 72) { cout << "wow"; }
   if (pos == 72) { cout << pBoard[pos] << endl; }
   if (piece == noPiece) { piece = pBoard[pos]; }
   if (piece == 'p') { pawnMGen(pos, black); }
   if (piece == 'P') { pawnMGen(pos, white); }
   if (piece == 'r') { genMove(rookM, pos, black); }
   if (piece == 'R') { genMove(rookM, pos, white); }
   if (piece == 'b') { genMove(bishopM, pos, black); }
   if (piece == 'B') { genMove(bishopM, pos, white); }
   if (piece == 'n') { genMove(knightM, pos, black); }
   if (piece == 'N') { genMove(knightM, pos, white); }
   if (piece == 'q') { genMove(queenM, pos, black); }
   if (piece == 'Q') { genMove(queenM, pos, white); }
   if (piece == 'k') { genMove(kingM, pos, black); }
   if (piece == 'K') { genMove(kingM, pos, white); }
   if (piece == emptySquare) {}    // cout << "\nWARNING: GenEmptySqMv\n"; }
   if (piece == invalidSquare) {}  // cerr << "\nERROR: GenINVALIDSqMv\n"; }
}

void inline pawnMGen(int pos, bool color)
{
   auto cRank = (pos / pBCol) - maxJ + 1;

   s64 mC{0};

   bool canPromote{false}, startPos{false};
   if (cRank > maxJ + bRow) { cerr << "ERROR: WHere exactly is your Pawn"; }

   if (color == white)
   {
      if (cRank == bRow - 1) { canPromote = true; }
      if (cRank == 2) { startPos = true; }
   }
   else
   {
      if (cRank == 2) { canPromote = true; }
      if (cRank == bRow - 1) { startPos = true; }
   }
   for (auto j{0}; wPawnM[j] != 0; j++)
   {
      if (color == white) { mC = wPawnM[j]; }
      if (color == black) { mC = bPawnM[j]; }
      moveT = pos + mC;

      if (j == 0)
      {
         if (pBoard[moveT] == invalidSquare)
         {
            cerr << "ERROR:Pawn" << moveT;
            continue;
         }
         if (pBoard[moveT] != emptySquare && pBoard[moveT] != moveDebug)
         { continue; }
         else
         {
            if (canPromote == 1) { pBoard[moveT] = '.'; }
            else
            {
               if (startPos == true)
               {
                  if (pBoard[moveT + mC] == emptySquare)
                  {
                     pBoard[moveT+mC] = moveDebug;
                     // gen double move
                     // set enPasant
                  }
               }
               pBoard[moveT] = moveDebug;
            }
         }
      }
      if (j > 0)
      {
         if (pBoard[moveT] == invalidSquare) { continue; }
         if ((pBoard[moveT] != emptySquare && pBoard[moveT] != moveDebug) ||
             pBoard[moveT] == 'e')
         {
            if (canPromote == 1) { pBoard[moveT] = '.'; }
            else
            {
               // pBoard[moveT] = captureDebug;
            }
         }
      }
   }
}


/*
void inline wPawnMGen(int pos)
{
   int cRank = (pos / pBCol) - maxJ + 1, canPromote{0};
   if (cRank > maxJ + bRow) { cerr << "ERROR: WHere exactly is your PawnW"; }
   int moveT{'{'};
   if (cRank == bRow - 1) { canPromote = 1; }
   for (auto j{0}; j < wPawnM.size(); j++)
   {
      moveT = pos + wPawnM[j];

      if (j == 0)
      {
         if (pBoard[moveT] == invalidSquare)
         {
            cerr << "ERROR: WHere exactly is your PawnII";
            continue;
         }
         if (pBoard[moveT] != emptySquare && pBoard[moveT] != moveDebug)
         { continue; }
         else
         {
            if (canPromote == 1) { pBoard[moveT] = '{'; }
            else
            {
               pBoard[moveT] = moveDebug;
            }
         }
      }
      if (j > 0)
      {
         if (pBoard[moveT] == invalidSquare) { continue; }
         if (pBoard[moveT] != emptySquare && pBoard[moveT] != moveDebug)
         {
            if (canPromote == 1) { pBoard[moveT] = '}'; }
            else
            {
               pBoard[moveT] = captureDebug;
            }
         }
      }
   }
}
void inline bPawnMGen(int pos)
{
   int cRank = (pos / pBCol) - maxJ + 1, canPromote{0};
   //cout<<" cRank: " << cRank<<" Pos/COl: "<<(int)(pos/pBCol)<<"EE";
   if (cRank > maxJ + bRow)
   {
      cerr << "ERROR: WHere exactly is your Pawn " << cRank << " " << pos << " "
           << pBCol;
      pBoard[pos] = '?';
   }
   int moveT{'{'};
   if (cRank == 2) { canPromote = 1; }
   for (auto j{0}; j < wPawnM.size(); j++)
   {
      moveT = pos + bPawnM[j];

      if (j == 0)
      {
         if (pBoard[moveT] == invalidSquare)
         {
            cerr << "ERROR: WHere exactly is your PawnII";
            continue;
         }
         if (pBoard[moveT] != emptySquare && pBoard[moveT] != moveDebug)
         { continue; }
         else
         {
            if (canPromote == 1) { pBoard[moveT] = '{'; }
            else
            {
               pBoard[moveT] = moveDebug;
            }
         }
      }
      if (j > 0)
      {
         if (pBoard[moveT] == invalidSquare) { continue; }
         if (pBoard[moveT] != emptySquare && pBoard[moveT] != moveDebug)
         {
            if (canPromote == 1) { pBoard[moveT] = '}'; }
            else
            {
               pBoard[moveT] = captureDebug;
            }
         }
      }
   }
}
*/
/*
void inline knightMGen(int pos)
{
   //int moveT{'{'};
   for (auto j{0}; j < knightM.size(); j++)
   {
      moveT = pos + knightM[j];
      if (pBoard[moveT] == invalidSquare) { continue; }
      if (pBoard[moveT] != emptySquare && pBoard[moveT] != moveDebug)
      { pBoard[moveT] = captureDebug; }
      else
      {
         pBoard[moveT] = moveDebug;
      }
   }
}
void inline kingMGen(int pos)
{
  // int moveT{'{'};
   for (auto j{0}; j < kingM.size(); j++)
   {
      moveT = pos + kingM[j];
      if (pBoard[moveT] == invalidSquare) { continue; }
      if (pBoard[moveT] != emptySquare && pBoard[moveT] != moveDebug)
      { pBoard[moveT] = captureDebug; }
      else
      {
         pBoard[moveT] = moveDebug;
      }
   }
}
void inline rookMGen(int pos)
{
   //int moveT{0};
   for (auto j{0}; j < rookM.size(); j++)
   {
      for (auto i{1}; i < 256; i++)
      {
         moveT = pos + (rookM[j] * i);

         if (pBoard[moveT] == invalidSquare) { break; }
         if (pBoard[moveT] != emptySquare)
         {
            if (pBoard[moveT] == moveDebug) { continue; }
            pBoard[moveT] = captureDebug;
             break;
         }
         else
         {
            pBoard[moveT] = moveDebug;
         }
      }
   }
}
void inline bishopMGen(int pos)
{
  // int moveT{0};
   for (auto j{0}; j < bishopM.size(); j++)
   {
      for (auto i{1}; i < 256; i++)
      {
         moveT = pos + (bishopM[j] * i);
         if (pBoard[moveT] == invalidSquare) { break; }
         if (pBoard[moveT] != emptySquare)
         {
            if (pBoard[moveT] == moveDebug) { continue; }
            pBoard[moveT] = captureDebug;
             break;
         }
         else
         {
            pBoard[moveT] = moveDebug;
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

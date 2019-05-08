#include "data.h"

s64 moveT{0};
class piece
{
   // bool
};

array<u64, 120> knightMove{};



void inline moveGen(int pos, char piece)
{ /*if no piece is specified it'll search through the board to find it*/
   // if (pos == 72) { cout << "wow"; }
   if (pos == 72) { cout << pBoard[pos] << endl; }
   if (piece == noPiece) { piece = pBoard[pos]; }
   if (piece == 'p') { pawnMGen(pos, black); }
   if (piece == 'P') { pawnMGen(pos, white); }
   if (piece == 'r') { slidingMoveGen(rookM, pos, black); }
   if (piece == 'R') { slidingMoveGen(rookM, pos, white); }
  // if (piece == 'b' || piece == 'B') { bishopMGen(pos); }
   //if (piece == 'n' || piece == 'N') { knightMGen(pos); }
   //if (piece == 'q' || piece == 'Q') { queenMGen(pos); }
   //if (piece == 'k' || piece == 'K') { kingMGen(pos); }
   if (piece == emptySquare) {}  // cout << "\nWARNING: GenEmptySqMv\n"; }
   if (piece == invalidSquare) { cerr << "\nERROR: GenINVALIDSqMv\n"; }
}

void inline pawnMGen(int pos, bool color)
{
   int cRank = (pos / pBCol) - maxJ + 1;

   bool canPromote{false},startPos{true};
   if (cRank > maxJ + bRow) { cerr << "ERROR: WHere exactly is your Pawn"; }
  // s64 moveT{'{'};

   if (color == white)
   {
      if (cRank == bRow - 1) { canPromote = 1; }
   }
   else
   {
      // _Ty a;
      if (cRank == 2) { canPromote = 1; }
   }
   for (auto j{0}; j < wPawnM.size(); j++)
   {
      if (color == white) { moveT = pos + wPawnM[j]; }
      if (color == black) { moveT = pos + bPawnM[j]; }

      if (j == 0)
      {
         if (pBoard[moveT] == invalidSquare)
         {
            cerr << "ERROR: WHere exactly is your Pawn" << moveT;
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
void inline queenMGen(int pos,int color)
{
   slidingMoveGen(rookM, pos, white);
   slidingMoveGen(bishopM, pos, white);
	
   
   // rookMGen(pos);
   //bishopMGen(pos);
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

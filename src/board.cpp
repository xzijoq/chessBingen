#include <assert.h>
#include <data.h>

#include "board.h"
#include "pieces.h"
#include <string>

using namespace std;


void boardsInit()
{
   // std::cout << pieceAt.size();
   for (auto i{0}; i < pieceAt.size(); i++) { pieceAt[i] = invalidPiece; }
   for (auto i{0}; i < board.size(); i++) { board[i] = invalidPiece; }
}

void boardPFill(bool display)
{
   assert(maxJ >= 0);
   u64 boardData{0};
   /*change this  'j' to AUTO or u64 to get an overflow bug
      auto Cant be trusted*/
   s64 leftPad = s64(maxJ - 1);
   s64 rightPad{1};
   u64 topPad = (pBCol * maxJ);
   u64 botPad = ((u64)pieceAt.size() - topPad);
   //   cout << "\n k and pBCol" << k << " " << pBCol;
   for (u64 i = 0; i < pieceAt.size(); i++)
   {
      // top and bottom padding

      //  cout << "\n" << topPad << " "<<botPad<<"\n";
      if (i >= topPad && i < botPad)
      {
         rightPad++;
         if (leftPad > 0 || rightPad > ((maxJ) + bCol))
         { pieceAt[i] = invalidPiece; }
         else
         {
            // cout << "i: " << i << endl;
            pieceAt[i] = board[boardData];
            // cout <<" "<<displayMap[ board[boardData]];
            boardIndexP[boardData] = i;
            boardData++;
         }
         leftPad--;
         if ((i + 1) % pBCol == 0)
         {
            leftPad = maxJ - 1;
            rightPad = 1;
         }
      }
   }
   fillPieceList();
}

void boardFill()
{
   int j{0};
   for (auto i : boardIndexP)
   {
      // cout << i << " ";
      board[j] = pieceAt[i];
      j++;
   }
}

void boardDisplay(const vector<u64> &boarD, bool intBoard)
{
 //  dPce[0] = noPiece;
   u64    offset{0}, rank{bSz / bCol};
   u8     file{'a'};
   size_t bS{0}, bDRow{0};
   bS = boarD.size();
   (bS == pBSz) ? offset = pBCol : offset = bCol;
   bDRow = bS / offset;
   auto j{bDRow - 1};
   std::cout << "\nBoardVec: \n";
   /*DisplayLoop*/
   for (auto i{0}; i < bDRow; i++)
   {
      if (bS == pBSz)
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
         auto pos = j * offset + k;
         (intBoard) ? cout << "  " << boarD[pos]
                    : cout << "  " << displayMap.at(boarD[pos]);

         //  (boarD[pos] < 32) ? cout << "  " << dPce[boarD[pos]]
         //                   : cout << "  " << boarD[pos];
      }
      cout << endl;
      j--;
   }
   cout << "\n   ";
   if (bS == pBSz)
   {
      for (auto i{0}; i < maxJ - 1; i++) { cout << "   "; }
   }
   for (auto i{0}; i < bCol; i++) { cout << "  " << file++; }
   cout << endl;
}
string getName(u64 sq)
{
   char   file = (char)(getFile(sq) + 'a' - 1);
   char   rank = getRank(sq) + '0';
   string wow;
   wow.push_back(file);
   wow.push_back(rank);

   return wow;
}




void boardDisplay(string boarS)
{
   // dPce[0] = noPiece;
   auto offset{0}, flag{errorFlag_D};

   auto   rank{bSz / bCol};
   u8     file{'a'};
   size_t bS{0}, bDR{0};

   bS = board.size();
   offset = bCol;
   bDR = bS / offset;

   if (boarS == "board") { flag = 1; }
   if (boarS == "pieceAt")
   {
      bS = pieceAt.size();
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
         auto pos = j * offset + k;

         if (flag == 1) { cout << "  " << displayMap.at(board[pos]); }
         if (flag == 2) { cout << "  " << displayMap.at(pieceAt[pos]); }
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

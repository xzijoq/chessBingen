#include <data.h>
#include <bitset>
#include <chrono>
#include <regex>  //to inititally validate fen

/*
MAX Board size supported by this fen reader 2048 2MB! (or update in fen)

S/O means selectively optional
1. reads fen and validate format :Done
        1.1 pass1 validation is very generous to accomodate varients
                1.2 pass2 tests for much of fide chess (emphasis on much)
2. if known reads fen and tell the board size and lists pieces on board :Done
3. if known identify the variation // no known variations yet
4. draw the board :Done
5. check if its a valid position :Done for n/n board
        5.1 TODO check valid pos for rules, basically there are two
            and only 2 opposite color kings (for now), and if either is in
            check its not the opponents move

TODO better Display and debuf (substitiue cout with blank function simething
llike taht)
*/

using namespace std;
using namespace std::chrono;
static enum fenParts {
   core,
   activePlayerFen,
   Castling,
   enPassant,
   halfMoveClock,
   fullMoveNumber,
   WOW
};

/*2MB?!!!*/
#define boardSizeFen 1024
/*Prefer to keep it u8 rather than u64*/
static vector<u64> boardFen(boardSizeFen);

static int          corePartBoardFen = 0, row{0}, col{0};
static int          fenEpCounter{0}, hmc{0}, fmc{0}, kingCount{0};
static array<u8, 3> epSFen{'a', 0, 1};
static unsigned int castleFen{0};
static int          halfMcFen{-1};
static int          fullMcFen{-1};
static int          activeSideFen{3};
unsigned char       fenSpace = invalidPiece;

void        chessFen(string fen, bool display);
static int  validateFenRegex(string fen);
static void stripFluffFen(string &fen);
static void fillData(int row, int col);
static void filldata();

/*

 for details on there regex see comments at bottom
passOne broad check, check only format
 passTwo checks foe max 8 rows and 8 columns, chekcs for fide chess pieces only
 requires core fen though

 passThree Requires full fen exept the start engine thingie
 as specified in https://en.wikipedia.org/wiki/Forsyth%E2%80%93Edwards_Notation
 rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1
  is it from engine optional
  #define mkStr_D(x) #x
 #define concat_D(x, y) x##y
*/

#pragma region regexStuff

static const string posAFen = "(^)(position[[:s:]])?(fen[[:s:]])?";
static const string coreFenS1 = "(([a-zA-Z0-9])+/)+";
static const string coreFenS2 = "(([rnbqkbnrpRNBQKBNRP1-8]){1,8}/){7}";
static const string coreFenS3 = "(([rnbqkbnrpRNBQKBNRP1-8]){1,8}/){7}";

static const string coreFenEnd1 = "(([a-zA-Z0-9])+){1}";  // rest is optional
static const string coreFenEnd2 = "(([rnbqkbnrpRNBQKBNRP1-8]){1,8}){1}";  // S/O
static const string coreFenEnd3 = "(([rnbqkbnrpRNBQKBNRP1-8]){1,8}){1}";

// nothing is optional in pass3 (hence the less bracket which ~ends at end)
static const string sideToMove1 = "([[:s:]][a-zA-Z1-9]{1}";
static const string sideToMove2 = "([[:s:]][b|w|B|W]{1}";
static const string sideToMove3 = "[[:s:]][b|w]{1}";

// castle rights can be empty in regex it is checked in string later
static const string castleRights1 = "[[:s:]]([K|-]?[Q|-]?[k|-]?[q|-]?|-)";
static const string castleRights2 = "[[:s:]]([K|-]?[Q|-]?[k|-]?[q|-]?|-)";
static const string castleRights3 = "[[:s:]]([K|-]?[Q|-]?[k|-]?[q|-]?|-)";

// TODO restrict more ([1-9]{1}[1-9]{0,1}) --for larger boards
static const string enPasant1 = "([[:s:]](([a-z]{1}[1-9]{1})|(-)))?";
static const string enPasant2 = "[[:s:]](([a-z]{1}[1-9]{1})|(-))";
static const string enPasant3 = "[[:s:]](([a-z]{1}[1-9]{1})|(-))";

// max half moves are 99999 (is check for greater move number needed?)
static const string halfMoves1 = "([[:s:]][0-9][0-9]?[0-9]?[0-9]?[0-9]?)?";
static const string halfMoves2 = "([[:s:]][0-9][0-9]?[0-9]?[0-9]?[0-9]?)?";
static const string halfMoves3 = "[[:s:]][0-9][0-9]?[0-9]?[0-9]?[0-9]?";

// max fullmoves are 9999
static const string fullMoves1 = "([[:s:]][0-9][0-9]?[0-9]?[0-9]?)?)?";
static const string fullMoves2 = "([[:s:]][0-9][0-9]?[0-9]?[0-9]?)?)?";
static const string fullMoves3 = "[[:s:]][0-9][0-9]?[0-9]?[0-9]?";

static const string passOneS = posAFen + coreFenS1 + coreFenEnd1 + sideToMove1 +
                               castleRights1 + enPasant1 + halfMoves1 +
                               fullMoves1;

static const string passTwoS = posAFen + coreFenS2 + coreFenEnd2 + sideToMove2 +
                               castleRights2 + enPasant2 + halfMoves2 +
                               fullMoves2;

static const string passThreeS = posAFen + coreFenS3 + coreFenEnd3 +
                                 sideToMove3 + castleRights3 + enPasant3 +
                                 halfMoves3 + fullMoves3;

#pragma endregion

int validateFenRegex(string fen)
{
   int flag{errorFlag_D};

   regex passOne(passOneS);
   regex passTwo(passTwoS);
   regex passThree(passThreeS);
   if (regex_match(fen, passOne)) { flag = 1; }
   if (regex_match(fen, passTwo)) { flag = 2; }
   if (regex_match(fen, passThree)) { flag = 3; }
   return flag;
}
void stripFluffFen(string &fen)
{
   // removeing the fluff
   size_t posPos = fen.find("position ");  // length is 9 including space
   if (posPos != string::npos && posPos == 0) { fen.erase(0, 9); }
   size_t fenPos = fen.find("fen ");
   if (fenPos != string::npos && (fenPos == 0)) { fen.erase(0, 4); }
   // removed the fluff
}

void fillData(int row, int col)
{
#if dynamicChess == 1
   // cout << "row: " << row << " cpl: " << col << endl;
   bRow = row;
   bCol = col;
   bSz = bRow * bCol;
   pBRow = (bRow + maxJ * 2);
   pBCol = (bCol + (maxJ - 1) * 2);
   pBSz = pBRow * pBCol;
   board.resize(bSz);
   pBoard.resize(pBSz);
   boardIndexP.resize(bSz);

   //  cout << "row: " << row << " col: " << col << endl;
#endif

#if dynamicChess == 0
   // assert(row == bRow && col == bCol);
   if ((row != bRow) && (col != bCol))
   { cerr << "ERROR:  InvalidBoardSize InvalidFen"; }
   // cout << "row: " << row << " col: " << col << endl;
#endif
   filldata();
}

void filldata()
{
   boardsInit();
   int  j{0};
   int  offset = col + 1;  //+1 for @ or +
   int  bDR = corePartBoardFen / offset;
   auto l{bDR - 1};
   /*Fen Starts From last rank*/
   for (auto i{0}; i < bDR; i++)
   {
      for (auto k{0}; k < offset; k++)
      {
         auto pos = l * offset + k;
         // cout << pos;
         //   cout << "   " << boardFen[pos];

         if (boardFen[pos] != fenRowBreak && boardFen[pos] != fenSpace)
         {
            if (j < bRow * bCol)
            {
               board[j] = boardFen[pos];
               j++;
            }
         }
      }
      l--;
      // cout << endl;
   }

   if (kingCount != 3) { cerr << "FenError:KingCount"; }
   boardPFill();
   activeSide = activeSideFen;
   castle = castleFen;
  // cout << endl << (char)(epSFen[0]) << " r " << (int)epSFen[1];
  // cout << endl << ep << endl;
   ep = getPIndex(epSFen[0], epSFen[1]);
  // cout << "\n ep " << ep;
   halfMc = halfMcFen;
   fullMc = fullMcFen;
}

void chessFen(string fen, bool display)
{
   // timing
   auto start = high_resolution_clock::now();

   /*for generating full board array from condenced fen*/
   int fenLocation{0}, rel{0};
   /*for counting the row and column of core fen and marking its end*/
   int count1{0}, d2{0};

   int regValidate = validateFenRegex(fen);
   if (regValidate == errorFlag_D)
   {
      cerr << "ThatAin'tNoValidFen, Please Kill yourself" << endl
           << "RegX validation failed";
      return;
   }
   else
   {
      // cout << "\nRegeX validation pass" << regValidate << " Sucess" << endl;
   }

   stripFluffFen(fen);

   // can be more elegent
   for (auto ch{0}; ch < fen.size(); ch++)
   {
      if (fenLocation == core)
      {
         if (fen[ch] != '/' && fen[ch] != ' ')
         {
            if (isdigit(fen[ch])) /*could use stoi*/
            {
               d2 = stoi(&fen[ch]);

               ch += (((d2 <= 1) ? 1 : log10(d2) + 1) - 1);

               for (int i{0}; i < d2; i++)
               {
                  boardFen[rel] = noPiece;
                  //                 cout << boardFen[rel];
                  rel++;
                  corePartBoardFen++;
                  count1++;
                  if (row == 0) { col++; }
               }
               rel--;  // WowMan
            }
            else
            {
               switch (fen[ch])
               {
                  case 'P':
                  {
                     boardFen[rel] = wP;
                     break;
                  }
                  case 'N':
                  {
                     boardFen[rel] = wN;
                     break;
                  }
                  case 'B':
                  {
                     boardFen[rel] = wB;
                     break;
                  }
                  case 'R':
                  {
                     boardFen[rel] = wR;
                     break;
                  }
                  case 'Q':
                  {
                     boardFen[rel] = wQ;
                     break;
                  }
                  case 'K':
                  {
                     boardFen[rel] = wK;
                     kingCount |= (0x1);
                     break;
                  }

                  case 'p':
                  {
                     boardFen[rel] = bP;
                     break;
                  }
                  case 'n':
                  {
                     boardFen[rel] = bN;
                     break;
                  }
                  case 'b':
                  {
                     boardFen[rel] = bB;
                     break;
                  }
                  case 'r':
                  {
                     boardFen[rel] = bR;
                     break;
                  }
                  case 'q':
                  {
                     boardFen[rel] = bQ;
                     break;
                  }
                  case 'k':
                  {
                     boardFen[rel] = bK;
                     kingCount |= (0x1) << 1;
                     break;
                  }
                  default: { boardFen[rel] = fen[ch];
                  }
               }

               // cout << boardFen[rel];
               corePartBoardFen++;
               count1++;
               /* counting no of coulumns in first row*/
               if (row == 0) { col++; }
            }
         }
         else
         {
            boardFen[rel] = fenRowBreak;
            corePartBoardFen++;
            row++;
            if (row > 0)
            {
               if (col != count1) { cerr << "\nERROR:Col!=Col\n"; }
            }
            count1 = 0;
         }
      }
      if (fen[ch] == ' ')
      {
         boardFen[rel] = fenSpace;
         fenLocation++;
         //         cout << "\n";
      }

      if (fenLocation == activePlayerFen)
      {
         if (fen[ch] != ' ')
         {
            boardFen[rel] = fen[ch];
            if (fen[ch] == 'w' || fen[ch] == 'W') { activeSideFen = white; }
            else
            {
               activeSideFen = black;
            }
         }
      }
      if (fenLocation == Castling)
      {
         if (fen[ch] != ' ')
         {
            boardFen[rel] = fen[ch];
            switch (fen[ch])
            {
               case 'K':
               {
                  castleFen |= 0x1;
                  break;
               }
               case 'Q':
               {
                  castleFen |= (0x1) << 1;
                  break;
               }
               case 'k':
               {
                  castleFen |= (0x1) << 2;

                  break;
               }
               case 'q':
               {
                  castleFen |= (0x1) << 3;

                  break;
               }
               default: {
               }
            }
         }
         else if (fen[ch + 1] == ' ')
         {
            cerr << "\nERROR: INVALID FEN -CastelingSquare is Empty \n";
            rel++;
            boardFen[rel] = '-';
            fenLocation--;
         }
      }
      if (fenLocation == enPassant && fen[ch] != ' ')
      {
         if ((fen[ch] != '-') && (fenEpCounter == 0))
         {
            fenEpCounter++;
      

            epSFen[0] = fen[ch];
           // cout << endl << epSFen[0] << endl;
            epSFen[1] = stoi(&fen[ch + 1]);
         }
         else if ((fen[ch] == '-'))
         {
         }
         boardFen[rel] = fen[ch];
      }
      if (fenLocation == halfMoveClock && fen[ch] != ' ')
      {
         boardFen[rel] = fen[ch];
         if (hmc == 0)
         {
            halfMcFen = stoi(&fen[ch]);
            hmc++;
         }
      }
      if (fenLocation == fullMoveNumber && fen[ch] != ' ')
      {
         boardFen[rel] = fen[ch];
         if (fmc == 0)
         {
            fullMcFen = stoi(&fen[ch]);
            fmc++;
         }
      }
      if (fenLocation > 5)
      {
         cerr << "ERROR: You'veGotBeKiddingme";
         boardFen[rel] = 'E';
      }

      rel++;
   }

   auto stop = high_resolution_clock::now();
   auto duration = duration_cast<microseconds>(stop - start);
   if (display == true)
   {
      cout << "\nCore part of fen : \n";
      for (int i{0}; i < corePartBoardFen; i++)
      {
         cout << boardFen[i];
         if (boardFen[i] == '@') { cout << "\n"; }
      }
      cout << endl << "Time taken: " << duration.count() << " microSec\n";
   }

   fillData(row, col);
};

// clang-format off
/* REGEX DATA
replace
\[\[:s:]] with \s and /with \/ --toSite
and 
\\s with [[:s:]] --backFromSite
for, back and forth
https://www.regexpal.com/
get sample fen to test from google

just cout the strings to console and copy endit

sample:
passOneOld
(^)(position\s)?(fen\s)?(([a-zA-Z1-9])+\/)+(([a-zA-Z1-9])+){1}(\s[a-zA-Z1-9]{1}\s([K|-]?[Q|-]?[k|-]?[q|-]?|-)\s(([a-z]{1}[1-9]{1})|(-))\s[0-9][0-9]?[0-9]?[0-9]?[0-9]?(\s[0-9][0-9]?[0-9]?[0-9]?)?)? 

passTwoOld
(^)(position\s)?(fen\s)?(([rnbqkbnrpRNBQKBNRP1-8]){1,8}/){7}(([rnbqkbnrpRNBQKBNRP1-8]){1,8}){1}(\s[b|w|B|W]{1}\s([K|-]?[Q|-]?[k|-]?[q|-]?|-)\s(([a-z]{1}[1-9]{1})|(-))(\s[0-9][0-9]?[0-9]?[0-9]?[0-9]?)?(\s[0-9][0-9]?[0-9]?[0-9]?)?)?                    
    
*/


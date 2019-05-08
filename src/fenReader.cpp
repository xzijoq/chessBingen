#include <data.h>
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
enum fenParts
{
   core,
   activePlayer,
   Castling,
   enPassant,
   halfMoveClock,
   fullMoveNumber,
   WOW
};
// char boardFen[280];
// array<char, boardSizeFen> boardFen;  // goes to ~81 for fideChess

/*2MB?!!!*/
#define boardSizeFen 1024
vector<char> boardFen(boardSizeFen);

int corePartBoardFen = 0, row{0}, col{0};


int  validateFenRegex(string fen);
void stripFluffFen(string &fen);
void fillData(int row, int col);
void filldata();
void chessFen(string fen, bool display);
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

// TODO restrict more
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
   int  offset = col +1;//+1 for @ or +
   int  bDR = corePartBoardFen / offset;
   auto l{bDR - 1};
   for (auto i{0}; i < bDR; i++)
   {
      for (auto k{0}; k < offset; k++)
      {
         auto pos = l * offset + k;
      //   cout << "   " << boardFen[pos];
         if (boardFen[pos] != '@' && boardFen[pos] != '+')
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

   for (auto i{0}; i < corePartBoardFen; i++)
   {
      // cout << boardFen[i];
   }

   boardPFill();
}

void chessFen(string fen, bool display)
{
   // timing
   auto start = high_resolution_clock::now();

   /*for generating full board array from condenced fen*/
   int fenLocation{0}, rel{0};
   /*for counting the row and column of core fen and marking its end*/
   int count1{0};
   /*for multiple digits in large boards*/
   int d0{0}, d1{0}, d2{0};
   //, row{0}, col{0};

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

   // regex check fen

   stripFluffFen(fen);

   // cout << "\n";
   // can be more elegent
   for (auto ch{0}; ch < fen.size(); ch++)
   {
      if (fenLocation == core)
      {
         if (fen[ch] != '/' && fen[ch] != ' ')
         {
            if (isdigit(fen[ch]))
            {
               // cout << " " << fen[ch];
               if (isdigit(fen[ch + 1]) && isdigit(fen[ch + 2]))
               {
                  // cout << " " << fen[ch+1];
                  d0 = (fen[ch] - '0') * 100;
                  d1 = (fen[ch + 1] - '0') * 10;
                  d2 = d0 + d1 + (fen[ch + 2] - '0');
                  ch += 2;
               }
               else if (isdigit(fen[ch + 1]))
               {
                  // cout << " " << fen[ch+1];
                  d1 = (fen[ch] - '0') * 10;
                  d2 = d1 + (fen[ch + 1] - '0');
                  ch++;
               }
               else
               {
                  d2 = fen[ch] - '0';
               }
               for (int i{0}; i < d2; i++)
               {
                  boardFen[rel] = '-';
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
               boardFen[rel] = fen[ch];
               // cout << boardFen[rel];
               corePartBoardFen++;
               count1++;
               /* counting no of coulumns in first row*/
               if (row == 0) { col++; }
            }
         }
         else
         {
            boardFen[rel] = '@';
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
         boardFen[rel] = '+';
         fenLocation++;
         //         cout << "\n";
      }

      if (fenLocation == activePlayer)
      {
         if (fen[ch] != ' ') { boardFen[rel] = fen[ch]; }
      }
      if (fenLocation == Castling)
      {
         if (fen[ch] != ' ') { boardFen[rel] = fen[ch]; }
         else if (fen[ch + 1] == ' ')
         {
            cerr << "\nERROR: INVALID FEN -CastelingSquare is Empty \n";
            rel++;
            boardFen[rel] = '-';
            fenLocation--;
         }
      }
      if (fenLocation == enPassant && fen[ch] != ' ')
      { boardFen[rel] = fen[ch]; }
      if (fenLocation == halfMoveClock && fen[ch] != ' ')
      { boardFen[rel] = fen[ch]; }
      if (fenLocation == fullMoveNumber && fen[ch] != ' ')
      { boardFen[rel] = fen[ch]; }
      if (fenLocation > 5)
      {
         cerr << "ERROR: You'veGotBeKiddingme";
         boardFen[rel] = 'E';
      }

      rel++;
   }

   // cout << endl << rel << endl;
   // cout << "\nNumberOfRow: " << row;
   // cout << "\nNumberOfColumn: " << col;

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


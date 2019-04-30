
#include <data.h>

#include <chrono>
#include <regex>  //to inititally validate fen
#include <vector>

/*
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
// char boardFen[280];
array<char, boardSizeFen> boardFen;  // goes to ~81 for fideChess
int                    corePartBoardFen = 0;

// for details on there regex see comments at bottom
/*passOne broad check, check only format

 passTwo checks foe max 8 rows and 8 columns, chekcs for fide chess pieces only
 requires core fen though

 passThree Requires full fen exept the start engine thingie
 as specified in https://en.wikipedia.org/wiki/Forsyth%E2%80%93Edwards_Notation
 rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1
*/
// is it from engine optional

#define mkStr_D(x) #x
#define concat_D(x, y) x##y
#define errorFlag_D 123

static const string posAFen = "(^)(position[[:s:]])?(fen[[:s:]])?";
static const string coreFenS1 = "(([a-zA-Z1-9])+/)+";
static const string coreFenS2 = "(([rnbqkbnrpRNBQKBNRP1-8]){1,8}/){7}";
static const string coreFenS3 = "(([rnbqkbnrpRNBQKBNRP1-8]){1,8}/){7}";

static const string coreFenEnd1 = "(([a-zA-Z1-9])+){1}";  // rest is optional
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

int validateFenRegex(string fen)
{
   int flag{errorFlag_D};

   regex passOne(passOneS);
   regex passTwo(passTwoS);
   regex passThree(passThreeS);
   if (regex_match(fen, passOne))
   {
      flag = 1;
   }
   if (regex_match(fen, passTwo))
   {
      flag = 2;
   }
   if (regex_match(fen, passThree))
   {
      flag = 3;
   }
   return flag;
}
void stripFluffFen(string &fen)
{
   // removeing the fluff
   size_t posPos = fen.find("position ");  // length is 9 including space
   if (posPos != string::npos && posPos == 0)
   {
      fen.erase(0, 9);
   }
   size_t fenPos = fen.find("fen ");
   if (fenPos != string::npos && (fenPos == 0))
   {
      fen.erase(0, 4);
   }
   // removed the fluff
}

void chessFen(string fen, bool display)
{
   // timing
   auto start = high_resolution_clock::now();

   /*If plan to branch non trivially from this function rememeber to reset cout
   or diable the first line
   if display is false disableing cout, is restored at the end*/
   if (display == false)
   {
      std::cout.setstate(std::ios_base::failbit);
   }

   /*for generating full board array from condenced fen*/
   int flag{0}, rel{0};
   /*for counting the row and column of core fen and marking its end*/
   int count1{0}, row{0}, col{0};

   int regValidate = validateFenRegex(fen);
   if (regValidate == 123)
   {
      cerr << "ThatAin'tNoValidFen, Please Kill yourself" << endl
           << "RegX validation failed";
      if (display == false)
      {
         std::cout.clear();
         return;
      }
   }
   else
   {
      cout << "\nRegeX validation pass" << regValidate << " Sucess" << endl;
   }

   // regex check fen

   stripFluffFen(fen);

   cout << "\n";
   // can be more elegent
   for (auto ch{0}; ch < fen.size(); ch++)
   {
      if (fen[ch] == ' ')
      {
         boardFen[rel] = '+';
         flag++;
         cout << "\n";
      }
      if (flag == 0)
      {
         if (fen[ch] != '/')
         {
            if (isdigit(fen[ch]))
            {
               for (int i{0}; i < atoi(&fen[ch]); i++)
               {
                  boardFen[rel] = '-';
                  cout << boardFen[rel];
                  rel++;
                  corePartBoardFen++;
                  count1++;
                  if (row == 0)
                  {
                     col++;
                  }
               }
               rel--;  // WowMan
            }
            else
            {
               boardFen[rel] = fen[ch];
               cout << boardFen[rel];
               corePartBoardFen++;
               count1++;
               if (row == 0)
               {
                  col++;
               }
            }
         }
         else
         {  // if(fen[ch]=='\'
            boardFen[rel] = '@';
            cout << endl;
            corePartBoardFen++;
            row++;
            if (row > 0)
            {
               if (col != count1)
               {
                  cout << "\ntHistypeoFmAdnesSiSnotSupPorted\n"
                       << "Multiple Size Row\n";
               }
            }
            count1 = 0;
         }
      }
      if (flag == 1)
      {
         if (fen[ch] != ' ')
         {
            cout << "side to move is: " << fen[ch];
            boardFen[rel] = fen[ch];
         }
         else
         {
            if (col != count1)
            {
               cout << "\ntHistypeoFmAdnesSiSnotSupPorted\n"
                    << "Multiple Size Row\n";
            }
         }
      }
      if (flag == 2)
      {
         if (fen[ch] != ' ')
         {  // TODO: enter for -
            cout << "castleAllowed: " << fen[ch] << " ";
            boardFen[rel] = fen[ch];
         }
         else if (fen[ch + 1] == ' ')
         {
            cout << "CastelingSquare is Empty, resetting flag";
            rel++;
            boardFen[rel] = '-';
            flag--;
         }
      }
      if (flag == 3 && fen[ch] != ' ')
      {
         cout << "EnPasantSquare is: " << fen[ch] << endl;
         boardFen[rel] = fen[ch];
      }
      if (flag == 4 && fen[ch] != ' ')
      {
         cout << "HalfMoveCounter: " << fen[ch] << endl;
         boardFen[rel] = fen[ch];
      }
      if (flag == 5 && fen[ch] != ' ')
      {
         cout << "FullMoveCounter: " << fen[ch] << endl;
         boardFen[rel] = fen[ch];
      }
      if (flag > 5)
      {
         cout << "You've GotTobeKiddingMe " << fen[ch] << endl;
         boardFen[rel] = fen[ch];
      }
      rel++;
   }

   cout << endl << rel << endl;
   cout << "\nNumberOfRow: " << row;
   cout << "\nNumberOfColumn: " << col;
   std::cout.clear();

   auto stop = high_resolution_clock::now();
   auto duration = duration_cast<microseconds>(stop - start);
   cout << endl << "Time taken: " << duration.count() << " microSec\n";
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


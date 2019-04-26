#include <assert.h>
#include <cstring>
#include <iostream>
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
*/

using namespace std;
char boardFen[ 280 ];  // goes to ~81 for fideChess

// for details on there regex see comments at bottom
/*passOne broad check, check only format*/
static const string passOne =
    "(^)(position[[:s:]])?(fen[[:s:]])?"       // is it from engine optional
    "(([a-zA-Z1-9])+/)+"                       // core fen
    "(([a-zA-Z1-9])+){1}"                      // core fen *rest is optional
    "([[:s:]][a-zA-Z1-9]{1}"                   // side to move
    "[[:s:]]([K|-]?[Q|-]?[k|-]?[q|-]?|-)"      // casteling rights(m Empty)
    "([[:s:]](([a-z]{1}[1-9]{1})|(-)))?"       // en pasant S/O
    "([[:s:]][0-9][0-9]?[0-9]?[0-9]?[0-9]?)?"  // half moves max 99999
    "([[:s:]][0-9][0-9]?[0-9]?[0-9]?)?)?";     // num of full moves max 9999

/*passTwo checks foe max 8 rows and 8 columns, chekcs for fide chess pieces only
  requires core fen though */
static const string passTwo =
    "(^)(position[[:s:]])?(fen[[:s:]])?"    // is it from engine optional
    "(([rnbqkbnrpRNBQKBNRP1-8]){1,8}/){7}"  // core fen
    "(([rnbqkbnrpRNBQKBNRP1-8]){1,8}){1}"   // core fen *rest is optional
    "([[:s:]]"                              // space
    "[b|w|B|W]{1}"                          // side to move
    "[[:s:]]"                               // space
    "([K|-]?[Q|-]?[k|-]?[q|-]?|-)"     // casteling rights(can be empty BUG?)
    "[[:s:]]"                          // space
    "(([a-z]{1}[1-9]{1})|(-))"         // en pasant TODO: restrict
    "([[:s:]]"                         // space
    "[0-9][0-9]?[0-9]?[0-9]?[0-9]?)?"  // half moves max 99999 S/O
    "([[:s:]]"                         // space
    "[0-9][0-9]?[0-9]?[0-9]?)?)?";     //  full moves max 9999 S/O

/*passThree Requires full fen exept the start engine thingie
as specified in https://en.wikipedia.org/wiki/Forsyth%E2%80%93Edwards_Notation
rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1
*/
static const string passThree =
    "(^)(position[[:s:]])?(fen[[:s:]])?"    // is it from engine optional
    "(([rnbqkbnrpRNBQKBNRP1-8]){1,8}/){7}"  // core fen
    "(([rnbqkbnrpRNBQKBNRP1-8]){1,8}){1}"   // core fen *requires the rest
    "[[:s:]]"                               // space
    "[b|w]{1}"                              // side to move
    "[[:s:]]"                               // space
    "([K|-]?[Q|-]?[k|-]?[q|-]?|-)"   // casteling rights (can be empty BUG?)
    "[[:s:]]"                        // space
    "(([a-z]{1}[1-9]{1})|(-))"       // en pasant TODO: restrict
    "[[:s:]]"                        // space
    "[0-9][0-9]?[0-9]?[0-9]?[0-9]?"  // number ofhalf moves max 99999
    "[[:s:]]"                        // space
    "[0-9][0-9]?[0-9]?[0-9]?";       // num of full moves max 9999

void chessFen( string fen ) {
  /*for generating full board array from condenced fen*/
  int flag{0}, rel{0};
  /*for counting the row and column of core fen and marking its end*/
  int   count1{0}, row{0}, col{0}, lag{0};
  regex isNum( "[0-9]" );
  regex passOne( passOne );
  regex passTwo( passTwo );
  regex passThree( passThree );
  ( regex_match( fen, passOne ) ) ? cout << "-passOneSucess-"
                                  : cout << "-failPassOne-";
  ( regex_match( fen, passTwo ) ) ? cout << "-passTwoSucess-"
                                  : cout << "-failPassTwo-";
  ( regex_match( fen, passThree ) ) ? cout << "-passThreeSucess-"
                                    : cout << "-failPassThree-";

  // removeing the fluff
  size_t posPos = fen.find( "position " );  // length is 9 including space
  if ( posPos != string::npos && posPos == 0 ) { fen.erase( 0, 9 ); }
  size_t fenPos = fen.find( "fen " );
  if ( fenPos != string::npos && ( fenPos == 0 ) ) { fen.erase( 0, 4 ); }
  // removed the fluff

  cout << "\n";
  // can be more elegent
  for ( auto ch{0}; ch < fen.size(); ch++ ) {
    if ( fen[ ch ] == ' ' ) {
      boardFen[ rel ] = '+';
      flag++;
      cout << "\n";
    }
    if ( fen[ ch ] != '/' && flag == 0 ) {
      if ( isdigit( fen[ ch ] ) ) {
        for ( int i{0}; i < atoi( &fen[ ch ] ); i++ ) {
          boardFen[ rel ] = '-';
          cout << boardFen[ rel ];
          rel++;
        }
        rel--;  // WowMan
      } else {
        boardFen[ rel ] = fen[ ch ];
        cout << boardFen[ rel ];
      }
    } else if ( flag == 0 ) {
      boardFen[ rel ] = '@';
      cout << endl;
    }

    if ( flag == 1 && fen[ ch ] != ' ' ) {
      cout << "side to move is: " << fen[ ch ];
      boardFen[ rel ] = fen[ ch ];
    }
    if ( flag == 2 ) {
      if ( fen[ ch ] == ' ' ) {
        if ( fen[ ch + 1 ] == ' ' ) {
          cout << "CastelingSquare is Empty, resetting flag";
          rel++;
          boardFen[ rel ] = '-';
          flag--;
        }
      }
      if ( fen[ ch ] != ' ' ) {  // TODO: enter for -
        cout << "castleAllowed: " << fen[ ch ] << " ";
        boardFen[ rel ] = fen[ ch ];
      }
    }
    if ( flag == 3 && fen[ ch ] != ' ' ) {
      cout << "EnPasantSquare is: " << fen[ ch ] << endl;
      boardFen[ rel ] = fen[ ch ];
    }
    if ( flag == 4 && fen[ ch ] != ' ' ) {
      cout << "HalfMoveCounter: " << fen[ ch ] << endl;
      boardFen[ rel ] = fen[ ch ];
    }
    if ( flag == 5 && fen[ ch ] != ' ' ) {
      cout << "FullMoveCounter: " << fen[ ch ] << endl;
      boardFen[ rel ] = fen[ ch ];
    }
    if ( flag > 5 ) {
      cout << "You've GotTobeKiddingMe " << fen[ ch ] << endl;
      boardFen[ rel ] = fen[ ch ];
    }
    rel++;
  }

  cout << rel << endl;
  lag = 0;

  for ( auto i{0}; i < rel + 1; i++ )  // todo append A at end
  {
    if ( boardFen[ i ] != '@' && lag == 0 && boardFen[ i ] != '+' ) {
      count1++;
    }
    cout << boardFen[ i ] << " ";
    if ( ( ( boardFen[ i ] == '@' ) || ( boardFen[ i ] == '+' ) ) &&
         lag == 0 ) {
      cout << endl;
      row++;
      //   cout << "col: " << col << "count " << count<<endl;
      if ( ( col ) != ( count1 ) ) {
        cout << "\nThis TYpe OF MadNESS iS nOt Supported\n";
        cout << "variable row board\n";
      }
      count1 = 0;
      if ( boardFen[ i ] == '+' ) { lag++; }
    }
    if ( row == 0 ) { col++; }
  }
  cout << "\nNumberOfRow: " << row;
  cout << "\nNumberOfColumn: " << col;
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

passOne
(^)(position\s)?(fen\s)?(([a-zA-Z1-9])+\/)+(([a-zA-Z1-9])+){1}(\s[a-zA-Z1-9]{1}\s([K|-]?[Q|-]?[k|-]?[q|-]?|-)\s(([a-z]{1}[1-9]{1})|(-))\s[0-9][0-9]?[0-9]?[0-9]?[0-9]?(\s[0-9][0-9]?[0-9]?[0-9]?)?)? 

passTwo
(^)(position\s)?(fen\s)?(([rnbqkbnrpRNBQKBNRP1-8]){1,8}/){7}(([rnbqkbnrpRNBQKBNRP1-8]){1,8}){1}(\s[b|w|B|W]{1}\s([K|-]?[Q|-]?[k|-]?[q|-]?|-)\s(([a-z]{1}[1-9]{1})|(-))(\s[0-9][0-9]?[0-9]?[0-9]?[0-9]?)?(\s[0-9][0-9]?[0-9]?[0-9]?)?)?                    
    
*/


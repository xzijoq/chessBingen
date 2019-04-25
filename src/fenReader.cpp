#include <cstring>
#include <iostream>
#include <regex>  //to inititally validate fen

/*
S/O means selectively optional
1. reads fen and validate it
        1.1 pass1 validation is very generous to accomodate varients
                1.2 pass2 tests for much of fide chess (emphasis on much)
2. if known reads fen and tell the board size and lists pieces on board
3. if known identify the variation
4. draw the board
5. check if its a valid position
*/

using namespace std;

void chessFen( const string *fen )
{
  /*broad check, check only format*/
  regex passOne(
      "(^)(position[[:s:]])?(fen[[:s:]])?"       // is it from engine optional
      "(([a-zA-Z1-9])+/)+"                       // core fen
      "(([a-zA-Z1-9])+){1}"                      // core fen *rest is optional
      "([[:s:]][a-zA-Z1-9]{1}"                   // side to move
      "[[:s:]]([K|-]?[Q|-]?[k|-]?[q|-]?|-)"      // casteling rights(m Empty)
      "([[:s:]](([a-z]{1}[1-9]{1})|(-)))?"       // en pasant S/O
      "([[:s:]][0-9][0-9]?[0-9]?[0-9]?[0-9]?)?"  // half moves max 99999
      "([[:s:]][0-9][0-9]?[0-9]?[0-9]?)?)?"      // num of full moves max 9999
  );
  /*checks foe max 8 rows and 8 columns, chekcs for fide chess pieces only
   * requires core fen though */
  regex passTwo(
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
      "[0-9][0-9]?[0-9]?[0-9]?)?)?"      //  full moves max 9999 S/O
  );
  /*Requires full fen exept the start engine thingie
  as specified in https://en.wikipedia.org/wiki/Forsyth%E2%80%93Edwards_Notation
  rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1
  */
  regex passThree(
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
      "[0-9][0-9]?[0-9]?[0-9]?"        // num of full moves max 9999
  );

  ( regex_match( *fen, passOne ) ) ? cout << "-passOneSucess-"
                                   : cout << "-failPassOne-";
  ( regex_match( *fen, passTwo ) ) ? cout << "-passTwoSucess-"
                                   : cout << "-failPassTwo-";
  ( regex_match( *fen, passThree ) ) ? cout << "-passThreeSucess-"
                                     : cout << "-failPassThree-";
};

// clang-format off

 
/* regx replace
\[\[:s:]] with \s and /with \/ --toSite
and 
\\s with [[:s:]] --backFromSite
for, back and forth
https://www.regexpal.com/
*/

/*
passOne
(^)(position\s)?(fen\s)?(([a-zA-Z1-9])+\/)+(([a-zA-Z1-9])+){1}(\s[a-zA-Z1-9]{1}\s([K|-]?[Q|-]?[k|-]?[q|-]?|-)\s(([a-z]{1}[1-9]{1})|(-))\s[0-9][0-9]?[0-9]?[0-9]?[0-9]?(\s[0-9][0-9]?[0-9]?[0-9]?)?)? 

passTwo
(^)(position\s)?(fen\s)?(([rnbqkbnrpRNBQKBNRP1-8]){1,8}/){7}(([rnbqkbnrpRNBQKBNRP1-8]){1,8}){1}(\s[b|w|B|W]{1}\s([K|-]?[Q|-]?[k|-]?[q|-]?|-)\s(([a-z]{1}[1-9]{1})|(-))(\s[0-9][0-9]?[0-9]?[0-9]?[0-9]?)?(\s[0-9][0-9]?[0-9]?[0-9]?)?)?                    
    
*/


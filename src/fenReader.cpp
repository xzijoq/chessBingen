#include <cstring>
#include <iostream>
#include <regex> //to validate fen

/*
1. reads fen and validate it
        1.1 pass1 validation is on format that is contains (no, of rows(adds the
            number of alphabetic charecters to any number found, and validates
            consistency over the columns))/....(repeat till number
                        of columns)(space reasd fgen and tell the variation also
validates number of columns is equal to the number of row( warns if untrue)
2. if known reads fen and tell the board size and lists pieces on board
3. if known identify the variation
4. draw the board
*/

using namespace std;

string fen;

string testfen =
    "position fen rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
// "position fen rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1
string testRegx = "123asd aA/";
string ff = "part1, part2,part3";
string ff1 = "gg";

int main() {

  string fPos = "position";
  string fFen = "fen";
  size_t fenPos = testfen.find("fen");
  // care must be taken for forward backslash https://www.regexpal.com/ checked
  // from there replace [[:s:]] with /s for site and back
  regex flora("(^)(position[[:s:]])?(fen[[:s:]])?(([a-zA-Z1-9]){1,8}\/){7}(([a-"
              "zA-Z1-9]){1,8}){1}([[:s:]][w|b]{1}[[:s:]][K|-][Q|-][k|-][q|-][[:"
              "s:]](([a-z]{1}[1-9]{1})|(-))[[:s:]][0-9][0-9]?[0-9]?[0-9]?[0-9]?"
              "[[:s:]][0-9][0-9]?[0-9]?[0-9]?)?");

  (regex_match(testfen, flora)) ? cout << " a mathc" : cout << "noMatch\n";
  // cout << posPos;
  if (fenPos != string::npos) {
  }
  // if()
  getchar();
}
/*
regex ss("((^|, )(part1|part2|part3))+$");
regex ii("^(pp|gg)$");
(regex_match(ff1, ii)) ? cout << " a mathc1" : cout << "noMatch1\n";

regex vFen("[[:digit:]]{3}(.*)\\s(aA/)");*/

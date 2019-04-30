
#include <array>
using namespace std;
constexpr short int maxJ = 2; /*knight can jump 2square*/
constexpr short int bSR = 8;       /*boardSizeRow*/
constexpr short int bSC = 8;    /*boardsizeCol*/
constexpr short int bSz = bSR * bSC;
constexpr short int padR = (bSR + maxJ * 2);
constexpr short int padC = (bSC + (maxJ - 1) * 2);
constexpr short int bSzP = padR * padC;




extern array<short int, bSz> board;

extern array<short int, bSzP> boardP;  // boardPadded

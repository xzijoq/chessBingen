#include <cstring>
#include <iostream>
#include <regex>

using namespace std;

void chessFen( const string *fen );
int  main()
{
  string t1 = "rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1";
  string ww = "8/K7/8/8/8/8/3k4/8 w - - 0 1";
  chessFen( &ww );


}

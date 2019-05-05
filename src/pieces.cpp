

#include "data.h"

#define dN (bPCol)
#define dS (-dN)
#define dE (1)
#define dW (-1)
#define dNE (dN + dE)
#define dNW (dN + dW)
#define dSE (dS + dE)
#define dSW (dS + dW)

array<u64, 120> knightMove{};


void dire()
{
   std::cout << " dN: " << dN << " dS: " << dS << " dE: " << dE << " dW " << dW
             << " dNE: " << dNE << " dNW: " << dNW << " dSE: " << dSE
             << " dSW: " << dSW << endl;
   //<< " " << dS << " " << ;

   // cout << fc;
}

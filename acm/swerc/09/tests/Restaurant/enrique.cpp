#include <iostream>
#include <cassert>
using namespace std;

/* 
Solution to "Working at the restaurant"
SWERC 2009, Madrid
Enrique Martín
*/


typedef enum state { INITIAL , TWO_PILES } state;
const int BIG = 10000;
const unsigned int pileIn = 0, pileOut = 1;

int main()
{
   unsigned int stacks[2];
   string s, take = "TAKE", drop = "DROP";
   state state = INITIAL;
   int n, m, numcase = 0;
   

   cin >> n;
   cin.ignore(BIG,'\n'); //Skip the line
   while ( n > 0 )
   { 
      if ( numcase != 0 )
         cout << endl;
       numcase++;
      
      stacks[0] = stacks[1] = 0;
      state = INITIAL;
   
   
      for( int i  = 0; i < n; ++i )
      {
         cin >> s >> m; 
         if ( s == take )
         {
            if ( state == INITIAL )
            {
               assert( stacks[pileIn] >= (unsigned int)m );
               assert( stacks[pileOut] == 0 ) ;
               int platesIn = stacks[pileIn]; // By definition platesIn >= m
               // Move all the plates from pileIn to pileOut
               stacks[pileIn] = 0;
               stacks[pileOut] += platesIn;
               cout << "MOVE " << (pileIn+1) << "->" << (pileOut+1) << " "  << platesIn << endl;
               // Take m plates from pileOut
               stacks[pileOut] -= m;
               cout << "TAKE " << (pileOut+1) << " " << m << endl;
               if ( stacks[pileOut] > 0 )
               {
                 state = TWO_PILES;
               }
            }
            else if ( state == TWO_PILES )
            {
               assert( (stacks[pileIn] + stacks[pileOut]) >= (unsigned int)m );
               int platesOut = stacks[pileOut];
               int fromOut = min(platesOut, m );
               int rest = m - fromOut;
               int platesIn = stacks[pileIn];
               // We take 'fromOut' plates from pileOut
               stacks[pileOut] -= fromOut;
               cout << "TAKE " << (pileOut+1) << " " << fromOut << endl;
               if ( rest > 0 )
               {
                  // Move all the plates from pileIn to pileOut
                  stacks[pileIn] = 0;
                  stacks[pileOut] += platesIn;
                  cout << "MOVE " << (pileIn+1) << "->" << (pileOut+1) << " "  << platesIn << endl;
                  // Take 'rest' plates from pileOut
                  stacks[pileOut] -= rest;
                  cout << "TAKE " << (pileOut+1) << " " << rest << endl;
               }
               if ( stacks[pileOut] == 0 )
               {
                  state = INITIAL;
               }
            }
         }
         else if ( s == drop )
         {
            stacks[pileIn] += m;
            cout << "DROP " << (pileIn+1) << " " << m << endl;
         }
      }
      cin >> n;
      cin.ignore(BIG,'\n'); //Skip the rest of the line   
   }
   
   return 0;
}

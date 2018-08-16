// O(length^3 * letters^2) DP solution to 'Assembly line'.
// Enrique Martin Martin

#include <iostream>
#include <cstdio>
#include <set>
using namespace std;

const int MAXL = 200;             //Maximum chain length
const int MAXA = 'z'-'a' + 1;     //Maximum number of letters: 'z'-'a'
const int INF  = 1000000000;  

char letter[MAXA];            //Positions of letters
int multCost[MAXA][MAXA];     //Cost of the multiplication of 2 letters at positions i,j
int multRes[MAXA][MAXA];      //Result of the multiplication of 2 letters at positions i,j
int cost[MAXL][MAXL][MAXA];   //Minimum cost of multiplying in a substring cost[i][j] obtaining a particular letter
string s;

// Returns the position of the letter c
inline int getPosition( char c )
{
   for( int i = 0; i < MAXA; ++i )
      if( letter[i] == c )
         return i;
         
   return -1; //This will not happen because c is supposed to appear in letter[]
}


void minimumCost( const string &s, int len, int numLetters )
{   
   fill( &cost[0][0][0], &cost[len-1][len-1][numLetters], INF );
    
   /*Base case, substrings of length 1*/
   for( int i = 0; i < len; ++i )
   {
      //cout << s << "-" << i << endl;
      int pos = getPosition( s[i] );
      cost[i][i][pos] = 0;
   }
   
   /*Substrings of length > 1*/ 
   for( int diag = 1; diag < len; diag++ )  
   {
      for( int i = 0; i+diag < len; i++ )
      {
         /*Substring [i,i+diag]*/
         for( int k = i; k < i+diag; k++ )
         {
            for( int l1 = 0; l1 < numLetters; l1++ )
            {
              for( int l2 = 0; l2 < numLetters; l2++ )
              {             
                if( cost[i][i+diag][ multRes[l1][l2] ] > (cost[i][k][l1] + cost[k+1][i+diag][l2] + multCost[l1][l2] ) )
                {
                  cost[i][i+diag][ multRes[l1][l2] ] = cost[i][k][l1] + cost[k+1][i+diag][l2] + multCost[l1][l2];
                }                
              }
            }
         }
      }
   }
}

int main()
{
   int k, costMul, n, m, len;
   char res;
   
   m = 0;
   for(;;)
   {
      cin >> k;
      if( k == 0 ) 
        break;
        
      if( m > 0 )
         cout << endl;
      m++;
      
      
      cin.ignore( 8092, '\n' );
      for( int i = 0; i < k; i++ )
         cin >> letter[i];
      
      for( int i = 0; i < k; i++ )
         for( int j = 0; j < k; j++ )
         {
           scanf ("%i-%c", &costMul, &res);
           multCost[i][j] = costMul;
           multRes[i][j] = getPosition(res);
         }
      
      cin >> n;
      cin.ignore( 8092, '\n' );
      for( int i = 0; i < n; i++ )
      {
         s.clear();
         cin >> s;
         len = s.length();
         cin.ignore( 8092, '\n' );
         
         minimumCost( s, len, k);
         int mincost = INF;
         for( int j = 0; j < MAXA; j++ )
         {
            mincost = ( cost[0][len-1][j] < mincost) ? cost[0][len-1][j] : mincost;
         }
         
         for( int j = 0; j < k; j++ )
         {
            if ( cost[0][len-1][j] == mincost )
            {
              cout << mincost << "-" << letter[j] << endl;
              break;
            }
         }
      }   
   }
   return 0;
}

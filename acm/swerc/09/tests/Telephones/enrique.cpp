#include <iostream>
#include <vector>
using namespace std;


/* 
Solution to "Happy telephones"
SWERC 2009, Madrid
Enrique Martín

Trivial solution O(MN)
*/


inline int overlap( pair<int,int> call, pair<int,int> interval )
{
  int a = max(call.first, interval.first);
  int b = min(call.second, interval.second);
  int ret = ((b-a) >= 1) ? 1 : 0;
  
  return ret;
}

int main()
{
   int n, m, a, b, s, l;
   vector< pair<int,int> > calls;
   
   cin >> n >> m;
   while( n != 0 && m != 0 )
   {
      calls.clear();
      for( int i = 0; i < n; ++i )
      {
         cin >> a >> b >> s >> l;
         calls.push_back( make_pair(s, s+l) );
      }
      
      for( int i = 0; i < m; ++i )
      {
         cin >> s >> l;
         pair<int,int> interval = make_pair(s,s+l);
         vector< pair<int,int> >::iterator it;
         int intcount = 0;
         
         for( it = calls.begin(); it != calls.end(); it++ )
            intcount += overlap( interval, *it );
            
         cout << intcount << endl;
      }
      cin >> n >> m;
   }
   return 0;
}

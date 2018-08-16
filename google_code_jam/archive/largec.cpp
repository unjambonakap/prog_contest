#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <set>
#include <map>
#include <queue>
#include <deque>
#include <list>
#include <utility>
#include <cassert>
using namespace std;

#define GI ({int t;scanf("%d",&t);t;})
#define REP(i,N) for(int i = 0;i < (N); ++i )
#define EACH(it,mp) for( __typeof(mp.begin()) it(mp.begin()); it != mp.end(); ++it )
#define REPV(i,ar) for(int i = 0; i < (ar).sz; ++i )
#define FOR(i,a,b) for(int i = (a); i <= (b); ++i )
#define INF (int(1e-9))
#define sz size()
#define pb push_back
#define mkp make_pair

typedef pair<int,int> PII;
typedef long long int LL;
typedef vector<int> VI;

int main(){
	int T = GI;
	FOR(tt,1,T){
		int K = GI;
		int N = GI;
		printf("Case #%d: ",tt);
		REP(i,N){
			int ind = GI - 1;
			LL pos = 0;
			int move = 0, len = K;
			while( true ) {
				pos += move; pos %= len;
				if( pos == ind ) break;
				if( pos < ind ) ind--;
				len--;
				move++;
				assert( ind < len );
			}
			printf(" %d",move+1);
		}
		puts("");
	}
	return 0;
	return 0;
}




#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <stack>
#include <algorithm>
#include <numeric>
#include <utility>
#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cassert>
//#include <ext/hash_map>


using namespace std;
using namespace __gnu_cxx;

#define PI asin(1)*2.
#define EPS 10e-8


#define REP(i,n) for(i = 0; i < (n); i++)
#define REPC(i,n,c) for(i = 0; (i < (n)) && (c); i++)

#define REPV(i, n) for (i = (n) - 1; i >= 0; i--)
#define REPVC(i, n, c) for (i = (n) - 1; (i >= 0) && (c); i--)
#define FOR(i, a, b) for(i = (a); i <= (b); i++)
#define FORC(i, a, b, c) for(i = (a); (i <= (b)) && (c); i++)
#define FORV(i, a, b) for(i = (a); i >= (b); i--)
#define FORVC(i, a, b, c) for(i = (a); (i >= (b)) && (c); i--)
#define FE(i,t) for (typeof(t.begin())i=t.begin();i!=t.end();i++)
#define FEV(i,t) for (typeof(t.rbegin())i=t.rbegin();i!=t.rend();i++)

#define MAX(a,b) (((a) < (b)) ? (b) : (a))
#define MIN(a,b) (((a) < (b)) ? (a) : (b))
#define pb push_back
#define ST first
#define ND second
#define SZ(a) ((a).size())
#define two(x) (1 << (x))
#define twoll(x) (1LL << (x))
#define ALL(a) (a).begin(), (a).end()
#define CLR(a) (a).clear()
#define SWAP(a,b,c) (c=a, a=b, b=c)

#define SQR(x) (pow((x),2))
#define DIST(x,y) (SQR(x)+SQR(y))
#define MDIST(x,y,a,b) (abs((a)-(x))+abs((b)-(y)))

#define CMP(x,y) ((fabs((x)-(y)) < EPS) ? 0 : ((x) < (y)) ? -1 : 1)

#define ST first
#define ND second

#define ll long long

inline int count_bit(int n){return (n == 0)?0:(n&1)+count_bit(n>>1);}

typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<string> vs;
typedef queue<int> qi;


#define MAX_N 500


class WT{
	public:
		WT(){}
		//WT(int _x, int _y, int _c, int _r){x=_x, y=_y, c=_c, r=_r;}
		int x, y, c, r;

};
vi edge[MAX_N];
WT wl[MAX_N];
int n;

int solve(){
	int i, j, k, c, nc;
	vi::iterator it;


	c=-1;
	REP(i, two(n)){

		nc=0;
		REP(k, n)
			if (i&two(k)){
				nc+=wl[k].c;
				for(it=edge[k].begin(); it!=edge[k].end(); it++)	
					if (!(i&two(*it)))break;
				if (it != edge[k].end())break;
			}
			

		
		if (k != n)continue;
		c=MAX(c, nc);
	}
	return c;





}


int main(){
	int i, j, k, T;
	scanf("%d", &T);
	REP(i, T){
		scanf("%d", &n);
		REP(j, n)
			scanf("%d %d %d %d", &wl[j].x, &wl[j].y, &wl[j].r, &wl[j].c);


		REP(j, n){
			CLR(edge[j]);

			REP(k, n)
				if (DIST(wl[k].x-wl[j].x, wl[k].y-wl[j].y) <= SQR(wl[j].r))
					edge[j].pb(k);
		}
			
		printf("Case #%d: %d\n", i+1, solve());



	}


	return EXIT_SUCCESS;
}


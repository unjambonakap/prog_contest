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
#include <climits>
//#include <ext/hash_map>


using namespace std;
using namespace __gnu_cxx;



#define REP(i,n) for(i = 0; i < (n); i++)
#define REPC(i,n,c) for(i = 0; (i < (n)) && (c); i++)

#define REPV(i, n) for (i = (n) - 1; i >= 0; i--)
#define REPVC(i, n, c) for (i = (n) - 1; (i >= 0) && (c); i--)
#define FOR(i, a, b) for(i = (a); i <= (b); i++)
#define FORC(i, a, b, c) for(i = (a); (i <= (b)) && (c); i++)
#define FORV(i, a, b) for(i = (a); i >= (b); i--)
#define FORVC(i, a, b, c) for(i = (a); (i >= (b)) && (c); i--)

#define FE(i,t) for (typeof((t).begin())i=(t).begin();i!=(t).end();i++)
#define FEV(i,t) for (typeof((t).rbegin())i=(t).rbegin();i!=(t).rend();i++)

#define MAX(a,b) (((a) < (b)) ? (b) : (a))
#define MIN(a,b) (((a) < (b)) ? (a) : (b))
#define SZ(a) (int((a).size()))
#define two(x) (1 << (x))
#define twoll(x) (1LL << (x))
#define ALL(a) (a).begin(), (a).end()
#define CLR(a) (a).clear()
#define SWAP(a,b,c) (c=a, a=b, b=c)

#define SQR(x) (pow((x),2))
#define DIST(x,y) (SQR(x)+SQR(y))
#define MDIST(x,y,a,b) (abs((a)-(x))+abs((b)-(y)))

#define CMP(x,y) ((fabs((x)-(y)) < EPS) ? 0 : ((x) < (y)) ? -1 : 1)

#define pb push_back
#define PF push_front
#define ST first
#define ND second
#define MP(x,y) make_pair(x, y)

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<string> vs;
typedef queue<int> qi;

inline int count_bit(int n){return (n == 0)?0:1+count_bit(n&(n-1));}
inline ll sqr(int x){return ll(x)*ll(x);}
inline double dist(ll x, ll y, ll a, ll b){return sqrt(double(sqr(x-a)+sqr(y-b)));}
inline bool bit_set(int a, int b){return (a&two(b));}

const double INF=1e20;

const int MAX_X=110;
int m[MAX_X][MAX_X], nm[MAX_X][MAX_X];

int main(){
	int _t, _T;
	int i, j, k;
	int r;
	int xa, xb, ya, yb;
	int mx, my;

	scanf("%d", &_T);
	REP(_t, _T){
		

		scanf("%d", &r);
		memset(m, 0, sizeof(m));

		mx=my=0;
		REP(i, r){
			scanf("%d %d %d %d", &xa, &ya, &xb, &yb);
			xa--, ya--, xb--, yb--;
			FOR(j, xa, xb)
				FOR(k, ya, yb)
					m[j][k]=1;
			mx=max(mx, xb), my=max(my, yb);
		}
		mx++, my++;

		//REP(j, my){
		//	REP(i, mx)
		//			printf("%d", m[i][j]);
		//		printf("\n");
		//	}
		//printf("\n");
		int c=0;
		while(r>0){

			memset(nm, 0, sizeof(nm));
			bool seen=false;
			REP(i, mx)
				REP(j, my){
					nm[i][j]=m[i][j];
					
					if (m[i][j]){
						if ((j==0 || m[i][j-1]==0) && (i==0 || m[i-1][j]==0))
							nm[i][j]=0;
						else seen=true;
					}else{
						if (j>0 && m[i][j-1] && i>0 && m[i-1][j])
							nm[i][j]=1, seen=true;
					}


				}
			//REP(j, my){
			//	REP(i, mx)
			//		printf("%d", nm[i][j]);
			//	printf("\n");
			//}
					
			memcpy(m, nm, sizeof(m));
			++c;
			if (!seen)break;
		}


		printf("Case #%d: %d\n", _t+1, c);
	}



	return EXIT_SUCCESS;
}


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
const int MAX_N=520;

int n, m;
int msq[MAX_N][MAX_N];

struct state{
	int x, y;
	int sqz;
	bool operator<(const state& a)const{
		if (sqz!=a.sqz)return sqz>a.sqz;
		if (y!=a.y)return y<a.y;
		return x<a.x;
	}
	


};

int main(){
	int t, T;
	int i, j, k;
	string s;
	map<char, int> tb;
	REP(i, 10)
		tb[(char)i+'0']=i;
	tb['A']=10;
	tb['B']=11;
	tb['C']=12;
	tb['D']=13;
	tb['E']=14;
	tb['F']=15;

	scanf("%d", &T);
	REP(t, T){
		scanf("%d %d\n", &m, &n);
		vector<vi> ma(m, vi(n, 0));
		REP(i, m){
			cin>>s;
			REP(j, n/4)
				REPV(k, 4)
					ma[i][j*4+3-k]=bool(tb[s[j]]&two(k));
		}

		memset(msq, 0, sizeof(msq));
		set<state> sa;
		vector<int> count(min(n, m)+1, 0);

		REP(i, n)
			msq[0][i]=1;
		REP(i, m)
			msq[i][0]=1;
	
		FOR(j, 1, m-1)
			FOR(i, 1, n-1){
				if (ma[j][i-1]!=ma[j][i] && ma[j-1][i]!=ma[j][i] && ma[j-1][i-1]==ma[j][i])
					msq[j][i]=1+min(min(msq[j-1][i], msq[j][i-1]), msq[j-1][i-1]);
				else
					msq[j][i]=1;
			}

			
		REP(j, m)
			REP(i, n)
			sa.insert((state){i, j, msq[j][i]});
		//FE(it, sa)
		//	if (it->sqz>1)printf("square %d %d %d\n", it->x, it->y, it->sqz);
		state ta;
		int d;
		int nz=0;
		while(SZ(sa)>0){
			ta=*sa.begin();
			if (count[ta.sqz]++==0)++nz;
			FOR(i, ta.x-ta.sqz+1, ta.x+ta.sqz-1)
				FOR(j, ta.y-ta.sqz+1, ta.y+ta.sqz-1){
					if (i>=n || j>=m)continue;
					if (sa.find((state){i, j, msq[j][i]})==sa.end())continue;
					sa.erase((state){i, j, msq[j][i]});
					if (i<=ta.x && j<=ta.y)continue;

					d=max(i-ta.x, j-ta.y);
					assert(d>=1);
					msq[j][i]=min(d, msq[j][i]);
					sa.insert((state){i, j, msq[j][i]});
				}


		}

		
				

		printf("Case #%d: %d\n", t+1, nz);
		REPV(i, SZ(count))
			if (count[i]>0)
				printf("%d %d\n", i, count[i]);


		



	}

	return EXIT_SUCCESS;
}


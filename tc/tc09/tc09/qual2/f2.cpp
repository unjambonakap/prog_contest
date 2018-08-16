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


class PageNumbers{
	public:
		int tb[11][11];

		vector<int> getCounts(int N){
			int i, j, k, p, sp;
			int n=N;
			vi tn;
			REP(i, 10)
				tb[0][i]=0;


			sp=1;
			while(n!=0){
				tn.pb(n%10);
				p=SZ(tn);
				n/=10;
				REP(j, 10)
					tb[p][j]+=10*tb[p-1][j]+sp;
				sp*=10;
			}

			vi s(10, 0);
			p=1;
			int sa=0;
			REP(i, SZ(tn)){

				k=tn[i];
				REP(j, 10)
					s[j]+=tb[i][j]*k;
				FOR(j, 1, k-1)
					s[j]+=p;
				s[k]+=sa+1;
				if (i>0 && tn[i-1]==0)s[0]-=p/10;
				//REP(j, 10)
				//	printf("%d ", s[j]);
				//	printf(" << for %d => %d %d\n\n", i, k, tb[i][0]*k);
				sa+=p*k;
				p*=10;
			}
			return s;
		}

};

int main(){
	int i, n, s, j;
	vi t;

		t=PageNumbers().getCounts(999);
		REP(j, 10)
			printf("%d ", t[j]);
		printf("\n");
	return 0;
	cin>>n;
	REP(i, n){
		cin>>s;
		t=PageNumbers().getCounts(s);
		printf("%d => ", s);
		REP(j, 10)
			printf("%d ", t[j]);
		printf("\n");

	}



	return 0;

}






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
//using namespace __gnu_cxx;



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
#define pb push_back
#define ST first
#define ND second
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

#define ST first
#define ND second

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
const int MAX_N=500;

int n, c;
int town[MAX_N];

vector<vi> m;

bool cmpL(const vi& a, const vi& b){
	int i;
	REP(i, n){
		if (a[i]>b[i])return true;
		else if (a[i]<b[i])return false;
	}
	return false;
}


void reduce(int col, int l){
	int i, j;

	if (col == n || l == c)return;

	if (m[l][col]==0) return reduce(col+1, l);


	FOR(i, l+1, c-1){
		if (m[i][col]==0)break;
		FOR(j, col, n)
			m[i][j]=(m[i][j]+m[l][j])%2;
	}

	sort(ALL(m), cmpL);
	reduce(col+1, l+1);


}

void reduce2(int l){
	int i, j, k;
	if (l == -1)return;
	REPV(i, n){
		if (m[l][i]!=0){
			REP(j, l)
				if (m[j][i]!=0){
					REP(k, n+1)
						m[j][k]=(m[j][k]+m[l][k])%2;
				}

			break;
		}
	}
	reduce2(l-1);

}

void solve(){

	int i, j, k;
	memset(town, 0, sizeof(town));

	sort(ALL(m), cmpL);
	//FE(it, m){
	//	FE(ita, *it)
	//		printf("%d", *ita);
	//	printf("\n");
	//}

	reduce(0, 0);
	reduce2(c-1);
	//printf("\n");
	//FE(it, m){
	//	FE(ita, *it)
	//		printf("%d", *ita);
	//	printf("\n");
	//}

	REP(i, c){
		k=-1;
		REP(j, n){
			if (m[i][j]){
				if (k!=-1)break;
				k=j;
			}

		}if (j!=n || k==-1)continue;

		town[k]=m[i][n]+1;
	}
	


}

int main(){
	int t, X;
	int i, j, k;
	int a, b;
	char l;


	scanf("%d", &X);
	REP(t, X){



		scanf("%d %d", &n, &c);

		m=vector<vi>(c, vi(n+1, 0));
		REP(i, c){
			scanf("%d %c", &k, &l);
			k--;
			switch(l){
				case 'T':j=0;break;
				case 'L':j=1;break;
				case 'S':j=2;break;
				case 'D':j=3;break;
			}

			if (j>=2){
				scanf("%d %d", &a, &b);
				a--, b--;
				m[i][k]++, m[i][a]++, m[i][b]++, m[i][n]=3-j;
			}else{
				scanf("%d", &a);
				a--;
				m[i][k]++,m[i][a]++, m[i][n]=j;
			}
			m[i][k]%=2, m[i][a]%=2;
		}

		solve();
		printf("Case #%d:", t+1);

		REP(i, n){
			if (town[i] == 0)printf(" -");
			else if (town[i] == 1)printf(" L");
			else printf(" T");
		}


		printf("\n");


	}
	return EXIT_SUCCESS;
}


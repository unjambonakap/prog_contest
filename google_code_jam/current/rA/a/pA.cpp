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
#define MP make_pair

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

const int MAX_N=52;
int tb[MAX_N][MAX_N];
int ntb[MAX_N][MAX_N];
vector<vi> va;
int n, k;

int vl=8;
int vx[]={0, -1, -1, -1, 0, 1, 1, 1};
int vy[]={1, 1, 0, -1, -1, -1, 0, 1};

int main(){
	int X, t;
	int i, j, h;
	char c;

	scanf("%d", &X);

	REP(t, X){

		scanf("%d %d\n", &n, &k);
//		printf("%d %d\n", n, k);
		va=vector<vi>(n);
		REP(i, n){
			REP(j, n){
				scanf("%c", &c);
				if (c=='.')tb[i][j]=0;
				else if (c=='B')tb[i][j]=1;
				else if (c=='R')tb[i][j]=2;
				if (c!='.')va[i].pb(j);
			}
			scanf("\n");
			memset(ntb[i], 0, sizeof(int)*n);
		}


		REP(i, n)
			REPV(j, SZ(va[i]))
				ntb[i][n-SZ(va[i])+j]=tb[i][va[i][j]];
	//	if (t!=2)continue;
			

		

		
	//	REP(i, n){
	//		REP(j, n)
	//			printf("%d", tb[i][j]);
	//		printf("\n");
	//	}
	//		printf("========\n");
	//	REP(i, n){
	//		REP(j, n)
	//			printf("%d", ntb[i][j]);
	//		printf("\n");
	//	}
		bool a, b;
		a=b=false;
		int l;
		int tx, ty;
		REP(i, n){
			REP(j, n){
				if (ntb[i][j]==0 || (ntb[i][j]==1 && b) || (ntb[i][j]==2 && a))continue;
				REP(h, vl){
					l=0;
					tx=i+vx[h], ty=j+vy[h];
					while(l++<k){
						if (tx<0 || tx>=n || ty<0 || ty>=n)break;
						if (ntb[tx][ty]!=ntb[i][j])break;
						tx+=vx[h], ty+=vy[h];
					}
					if (l==k){
						if (ntb[i][j]==1)b=true;
						else a=true;
						break;
					}
				}

			}

		}

		printf("Case #%d: ", t+1);
		if (a && b)
			printf("Both");
		else if (a)
			printf("Red");
		else if (b)
			printf("Blue");
		else
			printf("Neither");
		printf("\n");





	}


	return EXIT_SUCCESS;
}



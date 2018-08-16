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


vi Hungarian(int **w,int n){
  int lx[n],ly[n],skojx[n],skojy[n];
  int markx[n],marky[n],slack[n],par[n],q[n];
  int i, j, k;
  REP(i,n){ skojx[i]=skojy[i]=-1; ly[i]=0; lx[i]=*max_element(w[i], w[i]+n); }
  REP(k,n){
	  int v=-1,qb=0,qe=0;
	  REP(i,n){ marky[i]=markx[i]=0; slack[i]=-1; if (skojx[i]==-1) q[qe++]=i;}
	  while (v==-1){
		  while (qb<qe){
			  int i=q[qb++]; markx[i]=1;
			  REP(j,n)
				  if (!marky[j] && (slack[j]==-1 || slack[j]>lx[i]+ly[j]-w[i][j])){
					  if ((slack[j] = lx[ par[j]=i ]+ly[j]-w[i][j]) == 0){
						  marky[j]=1;
						  if (skojy[j]!=-1) q[qe++]=skojy[j]; else {v=j; goto koniec;}
					  }
				  }
		  }
		  int x=-1; REP(i,n) if (!marky[i] && (x==-1 || slack[i] < x)) x=slack[i];
		  REP(i,n){
			  if (markx[i]) lx[i]-=x; 
			  if (marky[i]) ly[i]+=x; else
				  if ((slack[i] -= x) == 0){
					  marky[i]=1; if (skojy[i] != -1) q[qe++]=skojy[i]; else v=i;
				  }
		  }
	  }
koniec:
	  while (v!=-1){int y=skojx[par[v]]; skojx[par[v]]=v; skojy[v]=par[v]; v=y;}
  }
  return vi(skojx,skojx+n);
}



int main(){
	int i, j, n, c;

	scanf("%d", &n);
	int **m=(int**)malloc(sizeof(int*)*n);;

	REP(i, n){
		m[i]=(int*)malloc(sizeof(int)*n);
		REP(j, n){
			scanf("%d", &m[i][j]);
			m[i][j]=-m[i][j];

		}
	}


	vi s=Hungarian(m, n);
	c=0;
	REP(i, n)
		c+=m[i][s[i]];

	printf("%d\n", c);





	return EXIT_SUCCESS;
}


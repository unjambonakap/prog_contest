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

const int MAX_V=1000010;
int store[MAX_V];
ll sq[MAX_V];

bool solve(int a, int b){//a > b
	assert(a>=b);
	if (a==0||b==0 || a==b)return false;
	if (a>=2*b)return true;
	if (store[a]>=0)return b<=store[a];
	return !solve(b, a-b);
}

ll proc(int a, int b){
	int i;

	if (a<b)swap(a, b);
	
	ll s=sq[b];
	FOR(i, b+1, a) 
		s+=min(b, store[i]);
	return s;

}
int main(){
	int X, t;
	int i, j;
	int aa, ab, ba, bb;

	memset(store, -1, sizeof(store));
	int low, high, mid;
	store[1]=0;
	FOR(i, 2, MAX_V){
		low=1, high=i;
		while(low<high){
			mid=ceil((low+high)/2.);
			if (solve(i, mid))
				low=mid;
			else
				high=mid-1;
		}
		store[i]=low;
		assert(solve(i, low));
		assert(!solve(i, low+1));

	}
//	printf("%d\n", win(MP(1, 0), MP(0, 1), 2, 1, 2));
//	exit(0);
	scanf("%d", &X);
	sq[0]=0;
	FOR(i, 1, MAX_V)
		sq[i]=sq[i-1]+2*store[i];

	

	REP(t, X){
		scanf("%d %d %d %d\n", &aa, &ab, &ba, &bb);
		aa--, ba--;
		printf("Case #%d: %Ld\n", t+1, proc(aa, ba)+proc(ab, bb)-proc(aa, bb)-proc(ab, ba));

	}


	return EXIT_SUCCESS;
}



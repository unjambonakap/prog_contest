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
const int MAX_L=7010;

vi s;

struct State{
	int p, n, a, b, c;
	bool operator<(const State& s)const{
		if (p!=s.p)return p<s.p;
		if (n!=s.n)return n<s.n;
		if (a!=s.a)return a<s.a;
		if (b!=s.b)return b<s.b;
		return c<s.c;
	}
};

map<State, int> dp;


int solve(int p, int n, int a, int b, int c){
	if (p==SZ(s))return n;
	map<State, int>::iterator it;
	if ((it=dp.find((State){p, n, a, b, c}))!=dp.end())return it->ND;
	it=dp.insert(MP(((State){p, n, a, b, c}), 0)).ST;
	int &r=it->ND;
	//stack xxxx => c => b => a <<< top

	int tl[3], i;
	memset(tl, 0, sizeof(tl));
	

	if (n==0)
		r=solve(p+1, 1, s[p], 0, 0)+1;
	else if (n==1){
		if (a==s[p]) r=solve(p+1, 1, a, 0, 0);
		else r=solve(p+1, 2, s[p], a, 0)+1;
	} else if (n==2){
		if (a==s[p]) r=solve(p+1, 2, a, b, 0);
		else if (b==s[p])r=solve(p+1, 1, b, 0, 0)+1;
		else r=solve(p+1, 3, s[p], a, b)+1;
	} else{
		int ttl[3]={a, b, c};
		assert(ttl[0]==a && ttl[1]==b && ttl[2]==c);

		REP(i, 3)
			tl[i]=ttl[(i+2*n)%3];
		assert(s[p-1]==tl[0]);


		if (tl[0]==s[p]) r=solve(p+1, n, a, b, c);
		else if (tl[1]==s[p]){
			if (n==3)ttl[2]=0, ttl[0]=b, ttl[1]=c;
			r=solve(p+1, n-1, ttl[0], ttl[1], ttl[2])+1;
		} else{
			if (n==3)ttl[1]=ttl[2]=0, ttl[0]=c;
			else if (n==4)ttl[2]=0, ttl[0]=b, ttl[1]=c;
			r=solve(p+1, n+1, a, b, c)+1;
			r=min(r, solve(p+1, n-2, ttl[0], ttl[1], ttl[2])+2);
		}
	}
	//printf("%d %d %d %d %d >> %d\n", p, n, a, b, c, r);
	return r;
}
	
	

int main(){
	int t, tn, i;
	string sa;

	scanf("%d\n", &tn);
	FOR(t, 1, tn){
		CLR(dp);
		CLR(s);
		cin>>sa;
		REP(i, sa.length())
			if (sa[i]>='A')
				s.pb(sa[i]-'A'+1);
		printf("Case #%d: %d\n", t, solve(0, 0, 0, 0, 0)+SZ(s));
	}


	return EXIT_SUCCESS;
}


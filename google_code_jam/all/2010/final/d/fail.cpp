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
const int MAX_N=15;

int n;
vector<ll> m;
ll f;
vi state;

int used[MAX_N];

ll checkit(){
	int i, j, k;

	/*
	   0=> go through
	   1=>>>>>>>>>>>> X
	   <<<<<<<<<<<<<<<X
	   2 X<<<<<<<<<<<
	   	 X>>>>>>>>>>>
		3 => start planet, decide according to its position
	   */


	ll r=0;

	//if (!(state[0]==3 && state[1]==0 && state[2]==0 && state[3]==1 && state[4]==0))return 0;
	memset(used, 0, sizeof(used));
	i=0;
	if (state[i]!=2)return 0;
	while(1){


		assert(state[i]!=0);
		if (state[i]==1){
			REPV(j, i){
				if (used[j])continue;
				if (state[j]==0)
					used[j]=1;
				else if (state[j]==2){
					used[j]=1;
					break;
				}
			}
			if (j==-1)
				return 0;

		}else if (state[i]==2){
			FOR(j, i+1, n-1){
				if (used[j])continue;
				if (state[j]==0)
					used[j]=1;
				else if (state[j]==1){
					used[j]=1;
					break;
				}
			}
			if (j==n)
				return 0;
		}
		
		r+=m[max(i, j)]-m[min(i, j)];
		i=j;
		if (i==0)break;

	}
	//r+=m[max(i, j)]-m[min(i, j)];
	REP(i, n)
		if (!used[i])return 0;
	
	return (r>f)?0:r;
	
}


ll rec(int s){
	if (s==n){
		return checkit();
	}

	ll r=0;
	int i;
	if (m[s]==0){
		if (s==0)
			state.pb(2);
		else if (s==n-1)
			state.pb(1);
		else
			state.pb(0);
		r=rec(s+1);
		state.pop_back();
	}else{
		REP(i, 3){
			state.pb(i);
			r=max(r, rec(s+1));
			state.pop_back();
		}
	}
	return r;
}

int main(){
	int tn, t;
	int i, j;
	ll ta;

	cin>>tn;
	FOR(t, 1, tn){
		cin>>n;
		CLR(m);
		CLR(state);

		REP(i, n){ cin>>ta; m.pb(ta); }
		sort(ALL(m));

		cin>>f;
		ta=rec(0);
		if (ta==0)
			printf("Case #%d: NO SOLUTION\n", t);
		else
			printf("Case #%d: %Ld\n", t, ta);
	}


	return EXIT_SUCCESS;
}


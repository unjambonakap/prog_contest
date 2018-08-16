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

int next[2][MAX_L];


int solve(const vi &s){
	int i, j, k, l;
	vi stk;


	memset(next, -1, sizeof(next));

	REP(i, SZ(s))
		FOR(j, i+1, SZ(s)-1)
			if (s[j]!=s[j-1]){
				if (next[0][i]!=-1)next[0][i]=s[j];
				else{ next[1][i]=s[j]; break; }
			}

	l=0;

	int n;
	REP(i, SZ(s)){
		n=SZ(stk);
		++l;
		if (n==0){
			stk.pb(s[i]); l++;
		}else{
			if (s[i]==stk[n-1]);
			else if (n==1)stk.pb(s[i]), ++l;
			else if (s[i]==stk[n-2])stk.pop_back(), ++l;
			else if (n==2)stk.pb(s[i]), ++l;
			else{
				assert(n>=3);
				assert(stk[n-3]==s[i]);
				if (next[0][i]==-1)stk.pop_back(), stk.pop_back(), l+=2;
				else if (next[0][i]==stk[n-2]){
					stk.pop_back(), stk.pop_back();
					++l;
				}else if (n>=4){
					assert(stk[n-4]==next[0][i]);
					assert(stk[n-1]==next[0][i]);
					stk.pop_back(), stk.pop_back();
					l+=2;
				}else{
					assert(stk[n-1]==next[0][i]);
					stk.push_back(s[i]);
					++l;
				}
			}

			assert(stk.back()==s[i]);
			assert(SZ(stk)<3 || stk.back()!=stk[SZ(stk)-3]);


		}


	}


	return l+SZ(stk);
}

int main(){
	int t, tn, i;
	string s;

	scanf("%d\n", &tn);
	FOR(t, 1, tn){
		cin>>s;
		vi ns;
		REP(i, s.length())
			if (s[i]>='A')
				ns.pb(s[i]-'A');
		printf("Case #%d: %d\n", t, solve(ns));
	}


	return EXIT_SUCCESS;
}


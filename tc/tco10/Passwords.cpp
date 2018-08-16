// BEGIN CUT HERE

// END CUT HERE
#line 5 "Passwords.cpp"

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
#include <sstream>
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



#define REP(i,n) for(int i = 0; i < int(n); ++i)

#define REPV(i, n) for (int i = (n) - 1; (int)i >= 0; --i)
#define FOR(i, a, b) for(int i = (int)(a); i <= (int)(b); ++i)
#define FORV(i, a, b) for(int i = (int)(a); i >= (int)(b); --i)

#define FE(i,t) for (typeof((t).begin())i=(t).begin();i!=(t).end();++i)
#define FEV(i,t) for (typeof((t).rbegin())i=(t).rbegin();i!=(t).rend();++i)

#define SZ(a) (int((a).size()))
#define two(x) (1 << (x))
#define twoll(x) (1LL << (x))
#define ALL(a) (a).begin(), (a).end()
#define CLR(a) (a).clear()


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

template<class T> void checkmin(T &a, T b){if (b<a)a=b;}
template<class T> void checkmax(T &a, T b){if (b>a)a=b;}
template<class T> void out(T t[], int n){REP(i, n)cout<<t[i]<<" "; cout<<endl;}
template<class T> void out(vector<T> t, int n=-1){for (int i=0; i<(n==-1?t.size():n); ++i) cout<<t[i]<<" "; cout<<endl;}
inline int count_bit(int n){return (n == 0)?0:1+count_bit(n&(n-1));}
inline bool bit_set(int a, int b){return (a&two(b));}
inline int low_bit(int n){return (n^n-1)&n;}
inline int ctz(int n){return (n==0?-1:(n==1?0:ctz(n>>1)+1));}
int toInt(string s){int a; istringstream(s)>>a; return a;}
string toStr(int a){ostringstream os; os<<a; return os.str();}

const int maxn=200010;
const int mod=1e9+9;
ll fact[maxn];
ll ifact[maxn];

ll mul(ll a, ll b){ return (a*b)%mod; }

pii bezout(ll a, ll ua, ll va, ll b, ll ub, ll vb){
	if (b==0) return MP(ua, va);
	return bezout(b, ub, vb, a-(a/b)*b, ua-ub*(a/b), va-vb*(a/b));
}

int procinv(int a){ return (mod+bezout(mod, 1, 0, a, 0, 1).ND%mod)%mod; }


ll fastexp(ll a, ll b){
	ll res=1;
	while(b!=0){
		if (b&1) res=(a*res)%mod;
		b>>=1; a=(a*a)%mod;
	}
	return res;
}

ll cnk(ll n, ll k){ return mul(mul(fact[n], ifact[k]), ifact[n-k]); }


class Passwords {
	public:
	int countValid(int N, int L, int U, int D) {
		ll res=0;
		ifact[0]=1;
		fact[0]=1; FOR(i, 1, N) fact[i]=(fact[i-1]*i)%mod, ifact[i]=procinv(fact[i]);;
		ll store[N];

		store[0]=(L+U==0);
		FOR(i, 1, N-D){
			store[i]=0;
			if (L+U<=i) store[i]=(2*store[i-1]+(U>0?cnk(i-1, U-1):0)+(L>0?cnk(i-1, L-1):0))%mod;
		}

		FOR(d, D, N){
			int nl=N-d;
			if (U+L>nl)continue;
			ll cnt=fastexp(10, d);
			cnt=mul(cnt, cnk(N, nl));
			cnt=mul(cnt, fastexp(26, nl));
			cnt=mul(cnt, store[nl]);
			//cnt=mul(cnt, fastexp(2, nl));
			res=(res+cnt)%mod;
		}
		return res;
		
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	//void test_case_0() { int Arg0 = 2; int Arg1 = 0; int Arg2 = 0; int Arg3 = 2; int Arg4 = 100; verify_case(0, Arg4, countValid(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_0() { int Arg0 = 200000; int Arg1 = 11; int Arg2 = 111; int Arg3 = 1111; int Arg4 = 100; verify_case(0, Arg4, countValid(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_1() { int Arg0 = 3; int Arg1 = 1; int Arg2 = 1; int Arg3 = 1; int Arg4 = 40560; verify_case(1, Arg4, countValid(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_2() { int Arg0 = 4; int Arg1 = 1; int Arg2 = 1; int Arg3 = 1; int Arg4 = 5029440; verify_case(2, Arg4, countValid(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_3() { int Arg0 = 10; int Arg1 = 1; int Arg2 = 3; int Arg3 = 3; int Arg4 = 818019214; verify_case(3, Arg4, countValid(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_4() { int Arg0 = 5; int Arg1 = 2; int Arg2 = 2; int Arg3 = 2; int Arg4 = 0; verify_case(4, Arg4, countValid(Arg0, Arg1, Arg2, Arg3)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  Passwords ___test; 
        ___test.run_test(-1); 
        } 
// END CUT HERE

// BEGIN CUT HERE

// END CUT HERE
#line 5 "ShrooksOnTheBoard.cpp"

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

const int mod=1e5+3;
const int maxn=101;

ll fact[mod], ifact[mod];
int n;

ll _cnk(int n, int k){ return k>n?0:fact[n]*ifact[k]*ifact[n-k]%mod; }
ll cnk(int n, int k){ return n<mod?_cnk(n, k):_cnk(n%mod, k%mod)*_cnk(n/mod, k/mod); }


ll fast_exp(ll a, int p){
    ll r=1;
    while(p){
        if (p&1) r=r*a%mod;
        p>>=1;
        a=a*a%mod;
    }
    return r;
}

void mul(ll a[][maxn], ll b[][maxn], ll r[][maxn]){
    ll c[maxn][maxn];
    memset(c, 0, sizeof(c));
    REP(i, n) REP(j, n) REP(k, n) c[i][j]=(c[i][j]+a[i][k]*b[k][j])%mod;
    memcpy(r, c, sizeof(c));

}
void fast_exp(ll a[][maxn], int p, ll r[][maxn]){
    REP(i, n) REP(j, n) r[i][j]=i==j;
    while(p){
        if (p&1) mul(r, a, r);
        p>>=1;
        mul(a, a, a);
    }
}

ll doita(int w, int k){
    ll a[maxn][maxn], r[maxn][maxn];
    n=k+1;
    memset(a, 0, sizeof(a));
    a[0][0]=a[0][k]=1;
    REP(i, k) a[i+1][i]=1;
    fast_exp(a, w+k, r);
    return r[0][0];
}

ll doitb(int w, ll k){
    ll res=1;
    int b=(w+k)/(k+1);
    for (int i=1; i<=b; ++i) res+=cnk(w-(i-1)*k, i);
    return res%mod;
}


class ShrooksOnTheBoard {
	public:
	int count(int K, int H, int W) {
        fact[0]=ifact[0]=1;
        REP(i, mod) fact[i+1]=fact[i]*(i+1)%mod, ifact[i+1]=fast_exp(fact[i+1], mod-2);
        ll res=K<=100?doita(W, K):doitb(W, K);
        return (mod+fast_exp(res, H)-1)%mod;
		
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 109; int Arg1 = 45811459; int Arg2 = 997358662; int Arg3 = 4; verify_case(0, Arg3, count(Arg0, Arg1, Arg2)); }
	//void test_case_0() { int Arg0 = 1; int Arg1 = 1; int Arg2 = 3; int Arg3 = 4; verify_case(0, Arg3, count(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arg0 = 1; int Arg1 = 2; int Arg2 = 2; int Arg3 = 8; verify_case(1, Arg3, count(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arg0 = 3; int Arg1 = 4; int Arg2 = 9; int Arg3 = 56963; verify_case(2, Arg3, count(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  ShrooksOnTheBoard ___test; 
  ___test.run_test(0); 
  return 0;
}



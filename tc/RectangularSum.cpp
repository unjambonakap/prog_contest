// BEGIN CUT HERE

// END CUT HERE
#line 5 "RectangularSum.cpp"

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
#define FOR(i, a, b) for(int i = (int)(a); i < (int)(b); ++i)
#define FE(i,t) for (typeof((t).begin())i=(t).begin();i!=(t).end();++i)

#define two(x) (1LL << (x))
#define ALL(a) (a).begin(), (a).end()


#define pb push_back
#define ST first
#define ND second
#define MP(x,y) make_pair(x, y)

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef vector<int> vi;

template<class T> void checkmin(T &a, T b){if (b<a)a=b;}
template<class T> void checkmax(T &a, T b){if (b>a)a=b;}
template<class T> void out(T t[], int n){REP(i, n)cout<<t[i]<<" "; cout<<endl;}
template<class T> void out(vector<T> t, int n=-1){for (int i=0; i<(n==-1?t.size():n); ++i) cout<<t[i]<<" "; cout<<endl;}
inline int count_bit(int n){return (n==0)?0:1+count_bit(n&(n-1));}
inline bool bit_set(int a, int b){return (a&two(b));}
inline int low_bit(int n){return (n^n-1)&n;}
inline int ctz(int n){return (n==0?-1:ctz(n>>1)+1);}
int toInt(string s){int a; istringstream(s)>>a; return a;}
string toStr(int a){ostringstream os; os<<a; return os.str();}

ll res;
int H, W;

void go2(ll S, ll a, ll b){
    if (a*b>=res) return;
    S-=(a-1)+W*(b-1);
    if (S<0) return;
    if (S%2) return;
    S/=2;
    if (S<0 || S>=1ll*W*H) return;
    if (a+S%W>W) return;
    if (b+S/W>H) return;
    res=min(res,a*b);

}

void go(ll S, ll b){
    int ub=min(W,int(sqrt(S)+1));
    FOR(i,1,ub+1){
        if (i*b>=res) return;
        if (!(S%i)) go2(i,S/i,b), go2(S/i,i,b);
    }
    
}

class RectangularSum {
	public:
	long long minimalArea(int _H, int _W, long long S) {
        W=_W; H=_H;
        S*=2;
        res=1e18;
        int ub=min(int(sqrt(S)+1),H);
        FOR(i,1,ub+1) if (!(S%i)) go(i,S/i), go(S/i,i);
        return res==1e18?-1:res;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 2; int Arg1 = 3; long long Arg2 = 8LL; long long Arg3 = 4LL; verify_case(0, Arg3, minimalArea(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arg0 = 3; int Arg1 = 3; long long Arg2 = 10LL; long long Arg3 = -1LL; verify_case(1, Arg3, minimalArea(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arg0 = 3; int Arg1 = 3; long long Arg2 = 36LL; long long Arg3 = 9LL; verify_case(2, Arg3, minimalArea(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arg0 = 25; int Arg1 = 25; long long Arg2 = 16000LL; long long Arg3 = 32LL; verify_case(3, Arg3, minimalArea(Arg0, Arg1, Arg2)); }
	void test_case_4() { int Arg0 = 1000000; int Arg1 = 1000000; long long Arg2 = 963761198400LL; long long Arg3 = 2LL; verify_case(4, Arg3, minimalArea(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){ 
  RectangularSum ___test; 
        ___test.run_test(4); 
        } 
// END CUT HERE

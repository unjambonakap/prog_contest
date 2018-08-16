// BEGIN CUT HERE

// END CUT HERE
#line 5 "CheckerExpansion.cpp"

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

ll go(ll a){
    ll v=0;
    for (ll x=2; x<=a; x<<=1) v+=a/x;
    return v;
}

class CheckerExpansion {
	public:
	vector <string> resultAfter(long long t, long long x0, long long y0, int w, int h) {
        vector<string> res(h,string(w,'.'));
        REP(i,h) REP(j,w){
            ll x=x0+j, y=y0+h-1-i;
            if (x+y&1) continue;
            ll r=(x+y)/2;
            if (x<r) continue;
            if (r+1>t) continue;

            if (!(go(r)-go(y)-go(r-y))) res[i][j]=(r&1)+'A';
        }
        return res;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <string> &Expected, const vector <string> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { long long Arg0 = 10000000000000LL; long long Arg1 = 0LL; long long Arg2 = 0LL; int Arg3 = 50; int Arg4 = 50; string Arr5[] = {"....", "....", "....", "A..." }; vector <string> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); verify_case(0, Arg5, resultAfter(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	//void test_case_0() { long long Arg0 = 1LL; long long Arg1 = 0LL; long long Arg2 = 0LL; int Arg3 = 4; int Arg4 = 4; string Arr5[] = {"....", "....", "....", "A..." }; vector <string> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); verify_case(0, Arg5, resultAfter(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_1() { long long Arg0 = 5LL; long long Arg1 = 4LL; long long Arg2 = 1LL; int Arg3 = 3; int Arg4 = 4; string Arr5[] = {"A..", "...", "B..", ".B." }; vector <string> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); verify_case(1, Arg5, resultAfter(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_2() { long long Arg0 = 1024LL; long long Arg1 = 1525LL; long long Arg2 = 512LL; int Arg3 = 20; int Arg4 = 2; string Arr5[] = {"B...B...B...........", ".B.A.B.A.B.........." }; vector <string> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); verify_case(2, Arg5, resultAfter(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_3() { long long Arg0 = 53LL; long long Arg1 = 85LL; long long Arg2 = 6LL; int Arg3 = 5; int Arg4 = 14; string Arr5[] = {".....", ".....", "B....", ".B.A.", ".....", ".....", ".....", ".....", ".....", ".....", "B....", ".B...", "..B..", ".A.B." }; vector <string> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); verify_case(3, Arg5, resultAfter(Arg0, Arg1, Arg2, Arg3, Arg4)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){ 
  CheckerExpansion ___test; 
        ___test.run_test(-1);
        } 
// END CUT HERE

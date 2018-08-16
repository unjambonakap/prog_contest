// BEGIN CUT HERE

// END CUT HERE
#line 5 "ThreePoints.cpp"

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

const int maxn=333333;
int x[maxn], y[maxn];


class ThreePoints {
	public:
	long long countColoring(int N, int xzero, int xmul, int xadd, int xmod, int yzero, int ymul, int yadd, int ymod) {
        x[0]=xzero; y[0]=yzero;
        FOR(i,1,N) x[i]=(1ll*x[i-1]*xmul+xadd)%xmod;
        FOR(i,1,N) y[i]=(1ll*y[i-1]*ymul+yadd)%ymod;
		
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 9; int Arg1 = 3; int Arg2 = 8; int Arg3 = 6; int Arg4 = 11; int Arg5 = 5; int Arg6 = 7; int Arg7 = 8; int Arg8 = 11; long long Arg9 = 8LL; verify_case(0, Arg9, countColoring(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8)); }
	void test_case_1() { int Arg0 = 4; int Arg1 = 9; int Arg2 = 6; int Arg3 = 8; int Arg4 = 10; int Arg5 = 4; int Arg6 = 8; int Arg7 = 5; int Arg8 = 10; long long Arg9 = 2LL; verify_case(1, Arg9, countColoring(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8)); }
	void test_case_2() { int Arg0 = 20; int Arg1 = 30; int Arg2 = 3; int Arg3 = 71; int Arg4 = 100; int Arg5 = 78; int Arg6 = 12; int Arg7 = 50; int Arg8 = 100; long long Arg9 = 263LL; verify_case(2, Arg9, countColoring(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8)); }
	void test_case_3() { int Arg0 = 300000; int Arg1 = 99097861; int Arg2 = 102766912; int Arg3 = 95284952; int Arg4 = 123456789; int Arg5 = 443104491; int Arg6 = 971853214; int Arg7 = 569775557; int Arg8 = 987654321; long long Arg9 = 749410681185726LL; verify_case(3, Arg9, countColoring(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){ 
  ThreePoints ___test; 
        ___test.run_test(-1); 
        } 
// END CUT HERE

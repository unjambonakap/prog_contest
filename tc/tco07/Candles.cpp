// BEGIN CUT HERE

// END CUT HERE
#line 5 "Candles.cpp"

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


int _gcd(int a, int b){return (b==0?a:_gcd(b, a-(a/b)*b));}
int gcd(int a, int b){ return _gcd(max(a, b), min(a, b)); }

class Candles {
	public:
	int ceremonies(int n, int na, int ra, int nb, int rb) {
		int d=gcd(ra, rb);
		ll ppm=ra*rb/d;
		int va=ppm/ra;
		int vb=ppm/rb;
		
		int tmp=gcd(va*na+vb*nb, n);
		ppm=ll(va*na+vb*nb)*n/tmp;

		int nt=ppm/n;
		int ma=min(n, nb), mb=min(n, na);
		int k=ppm/ll(va*na+vb*nb);

		if (vb*nb*k>nt*ma)return -1;
		if (va*na*k>nt*mb)return -1;
		return nt;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	//void test_case_0() { int Arg0 = 5; int Arg1 = 6; int Arg2 = 5; int Arg3 = 4; int Arg4 = 5; int Arg5 = 2; verify_case(0, Arg5, ceremonies(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_0() { int Arg0 = 5; int Arg1 = 1; int Arg2 = 3; int Arg3 = 5; int Arg4 = 2; int Arg5 = 17; verify_case(0, Arg5, ceremonies(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_1() { int Arg0 = 3; int Arg1 = 12; int Arg2 = 4; int Arg3 = 6; int Arg4 = 2; int Arg5 = 8; verify_case(1, Arg5, ceremonies(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_2() { int Arg0 = 19; int Arg1 = 10; int Arg2 = 1; int Arg3 = 10; int Arg4 = 10; int Arg5 = -1; verify_case(2, Arg5, ceremonies(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_3() { int Arg0 = 56; int Arg1 = 50; int Arg2 = 20; int Arg3 = 60; int Arg4 = 16; int Arg5 = 125; verify_case(3, Arg5, ceremonies(Arg0, Arg1, Arg2, Arg3, Arg4)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  Candles ___test; 
        ___test.run_test(-1);
        } 
// END CUT HERE

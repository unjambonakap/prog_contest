// BEGIN CUT HERE

// END CUT HERE
#line 5 "NumericalIntegral.cpp"

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

const int n=1e6;
double tb[n+1];
double f(double x){ return exp(-x*x); }

class NumericalIntegral {
	public:
	string integrate(double x1, double x2) {
        REP(i, n+1) tb[i]=f(x1+(x2-x1)*i/n);
        double res=0.;
        double x=(x2-x1)/n/3;
        REP(i, n/2) res+=x*(tb[2*i]+4*tb[2*i+1]+tb[2*i+2]);
        char buf[15];
        sprintf(buf, "%.5lf", res);
        return string(buf);
        
		
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { double Arg0 = -0.5; double Arg1 = 0.5; string Arg2 = "0.92256"; verify_case(0, Arg2, integrate(Arg0, Arg1)); }
	void test_case_1() { double Arg0 = 0.0; double Arg1 = 0.1; string Arg2 = "0.09967"; verify_case(1, Arg2, integrate(Arg0, Arg1)); }
	void test_case_2() { double Arg0 = -9.0001; double Arg1 = -9.0; string Arg2 = "0.00000"; verify_case(2, Arg2, integrate(Arg0, Arg1)); }
	void test_case_3() { double Arg0 = 2.71828183; double Arg1 = 3.14159265; string Arg2 = "0.00010"; verify_case(3, Arg2, integrate(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){ 
  NumericalIntegral ___test; 
        ___test.run_test(-1); 
        } 
// END CUT HERE
